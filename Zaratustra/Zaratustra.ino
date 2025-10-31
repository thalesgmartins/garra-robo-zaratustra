/** --------------------------------------------------------------------------------------------------
 * @file Zaratustra.ino
 * @brief Faz o controle da garra, fazendo a leitura de utilizando Classes para cada Motor e Botão.
 * @author Thales Martins
 * @version Beta 0.3.0
/** --------------------------------------------------------------------------------------------------*/

#include <AccelStepper.h>
#include <Bounce2.h>

#include "Pins.h"

// --------------------------------------------------------------------------------------------------
// DECLARAÇÃO DO SENSOR DE LASER
// --------------------------------------------------------------------------------------------------
Bounce2::Button sensorLaser = Bounce2::Button();


// --------------------------------------------------------------------------------------------------
// DECLARAÇÃO DO BOTÃO DE TROCA DE ESTADOS
// --------------------------------------------------------------------------------------------------
Bounce2::Button buttonTrocarModo = Bounce2::Button();


// --------------------------------------------------------------------------------------------------
// DECLARAÇÃO DOS ENDSTOPS
// --------------------------------------------------------------------------------------------------
Bounce2::Button endstopBase  = Bounce2::Button();
Bounce2::Button endstopCorpo = Bounce2::Button();
Bounce2::Button endstopBraco = Bounce2::Button();


// --------------------------------------------------------------------------------------------------
// DECLARAÇÃO DOS MOTORES
// --------------------------------------------------------------------------------------------------
AccelStepper  stepperBase(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperCorpo(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperBraco(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);


// --------------------------------------------------------------------------------------------------
// CONTROLE DE ESTADOS
// --------------------------------------------------------------------------------------------------
typedef enum {          // Um ENUM para armazenar os estados da garra:
  HOME,                 //  - Quando estiver fazendo Homing,
  PARADO,               //  - Quando estiver travada,
  MOVENDO,              //  - Quando estiver fazendo o looping de movimentos
  UNKNOWN               //  - Quando não consegue ler - Ao Inicializar
} Estado;

Estado actualState = UNKNOWN;
Estado previousState = UNKNOWN;

byte estagioDosMovimentos = 0;
bool ultimoMovimentoConcluido = false;

//bool movimentoConcluido = true;

// --------------------------------------------------------------------------------------------------
// SETUP DOS ENDSTOPS, MOTORES, BOTÃO E SENSOR
// --------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando Setup da Garra.");

  setupButtons();
  setupMotors();
  executarHoming();
  Serial.println("Setup Concluído.");
}

void setupButtons() {
  Serial.println("Iniciando Configuração da lib Bounce2:");

  // Configuração do Sensor de Laser
  Serial.println("  Configurando Sensor de Laser");
  sensorLaser.attach(SENSOR_LASER_PIN, INPUT_PULLUP);
  sensorLaser.setPressedState(LOW);
  sensorLaser.interval(25);

  // Configuração do Botão que faz a troca de modos
  Serial.println("  Configurando Botão de Troca de Estados");
  buttonTrocarModo.attach(ENDSTOP_Z_MAX, INPUT_PULLUP);
  buttonTrocarModo.setPressedState(LOW);
  buttonTrocarModo.interval(25);

  // Configuração do Endstop da Base
  Serial.println("  Configurando Endstops");
  endstopBase.attach(ENDSTOP_X_MIN, INPUT_PULLUP);
  endstopBase.setPressedState(LOW);
  endstopBase.interval(25);
  
  // Configuração do Endstop do Corpo
  endstopCorpo.attach(ENDSTOP_Y_MIN, INPUT_PULLUP);
  endstopCorpo.setPressedState(LOW);
  endstopCorpo.interval(25);
  
  // Configuração do Endstop do Braço
  endstopBraco.attach(ENDSTOP_Z_MIN, INPUT_PULLUP);
  endstopBraco.setPressedState(LOW);
  endstopBraco.interval(25);

  Serial.println("Configuração da lib Bounce2 Concluída");
}

void setupMotors() {

  // --------------------------------------------------------
  // HABILITA MOTORES
  // --------------------------------------------------------

  // Habilita o motor da Base
  stepperBase.setEnablePin(X_ENABLE_PIN);
  stepperBase.setPinsInverted(false, false, true);
  stepperBase.enableOutputs();

  // Habilita o motor do Corpo
  stepperCorpo.setEnablePin(Y_ENABLE_PIN);
  stepperCorpo.setPinsInverted(false, false, true);
  stepperCorpo.enableOutputs();

  // Habilita o motor do Braço
  stepperBraco.setEnablePin(Z_ENABLE_PIN);
  stepperBraco.setPinsInverted(false, false, true);
  stepperBraco.enableOutputs();

  // --------------------------------------------------------
  // Configura velocidade e aceleração dos motores
  // --------------------------------------------------------

  // Configura Motor da Base
  stepperBase.setMaxSpeed(700);
  stepperBase.setAcceleration(500);

  // Configura Motor do Corpo
  stepperCorpo.setMaxSpeed(700);
  stepperCorpo.setAcceleration(500);

  // Configura Motor do Braço
  stepperBraco.setMaxSpeed(700);
  stepperBraco.setAcceleration(500);
}

void executarHoming() {
  Serial.println("Fazendo Homing dos Motores");
  homeMotor(stepperCorpo, endstopCorpo);           // Home do Corpo
  homeMotor(stepperBraco, endstopBraco);           // Home do Braço
  homeMotor(stepperBase, endstopBase);             // Home da Base
}

void homeMotor(AccelStepper &stepper, Bounce2::Button &endstop) {
  endstop.update();

  if (!endstop.isPressed()) {
    while (!endstop.pressed()) {
      endstop.update();
      stepper.setSpeed(-800);
      stepper.runSpeed();
    }
  }

  stepper.stop();
  stepper.setCurrentPosition(0);
}

// --------------------------------------------------------------------------------------------------
// CONTROLE DA GARRA: Leitura do sensor, botões e controle de estados.
// --------------------------------------------------------------------------------------------------
void loop() {

  // Atualiza o estado do sensor e botão de modos
  sensorLaser.update();
  buttonTrocarModo.update();

  // Baseado na leitura, pega o estado Atual
  actualState = getActualState();

  // Se deve parar, para suavemente.
  if (shouldStop()) {
    stepperBase.stop();
    stepperBraco.stop();
    stepperCorpo.stop();
    return;
  }

  // Se estiver no modo Home, vai para a Home.
  if (shouldHome()) {
    executarHoming();
    return;
  }

  //
  if (shouldMove()) {
    if (movimentoConcluido()) {
      executarMovimentos();
    }

    else {
      stepperBase.run();
      stepperBraco.run();
      stepperCorpo.run();
    }
  }

  previousState = actualState;
}

// --------------------------------------------------------------------------------------------------
//  
// --------------------------------------------------------------------------------------------------

Estado getActualState() {
  if (sensorLaser.isPressed()) return PARADO;
  if (buttonTrocarModo.isPressed()) return HOME;

  return MOVENDO;
}

bool shouldStop() {
  return actualState == PARADO;
}

bool shouldHome() {
  return actualState == HOME && actualState != previousState;
}

bool shouldMove() {
  return actualState == MOVENDO;
}

void executarMovimentos() {
  static byte estagioDosMovimentos = 0;


  switch (estagioDosMovimentos) {
    case 0:
      Serial.println("Indo para Estágio 0");
      stepperBase.moveTo(200);
      stepperBraco.moveTo(200);
      stepperCorpo.moveTo(200);
      break;
    case 1:
      Serial.println("Indo para Estágio 1");
      stepperBase.moveTo(400);
      break;
    case 2:
      Serial.println("Indo para Estágio 2");
      stepperBraco.moveTo(600);
      stepperCorpo.moveTo(600);
      break;
    case 3:
      Serial.println("Indo para Estágio 3");
      stepperBraco.moveTo(200);
      stepperCorpo.moveTo(200);
      break;
  }

  estagioDosMovimentos++;

  if (estagioDosMovimentos > 3) {
    estagioDosMovimentos = 0;
  }
}

bool movimentoConcluido() {
  return stepperBase.distanceToGo() == 0 && 
         stepperBraco.distanceToGo() == 0 && 
         stepperCorpo.distanceToGo() == 0;
}