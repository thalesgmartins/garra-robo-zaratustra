/** --------------------------------------------------------------------------------------------------
 * @file Zaratustra.ino
 * @brief Faz o controle cíclico dos motores da garra, adicionando um botão que deve ser acionado antes do desligamento.
 * @author Thales Martins
 * @version Alpha 1.3
/** --------------------------------------------------------------------------------------------------*/

/*------------------------------------- Definições e Declarações -------------------------------------*/

// Inclusão de Bibliotecas
#include "Pins.h"
#include "Motors.h"

// Declara os botões usando a AccelStepper
AccelStepper stepperBase(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperCorpo(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperBraco(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);

// Declara os Endstops listas.
const int N_BUTTON = 3;
byte buttonPins[N_BUTTON] = { ENDSTOP_X_MIN, ENDSTOP_Y_MIN, ENDSTOP_Z_MIN};

const int DEBOUNCE_TIME = 25;
Bounce2::Button debouncers[N_BUTTON] = { Bounce2::Button() };

// Declara o botão de descanso da garra.
Bounce2::Button buttonDescansar = Bounce2::Button();

bool mode = false;

/*--------------------------------------- Inicialização ---------------------------------------*/

void setup() {
  Serial.begin(9600);
  
  // Inicializando os Botões pela Biblioteca Bounce2
  inicializarBotoes();

  // Inicializando os Motores
  habilitarMotores();
  configurarMotores();
  definirHome();

  // Move os motores para a posição padrão.
  moverPosicaoIncial();
}

/*------------------------------------- Loop Principal -------------------------------------*/

void loop() {
  switchModes();

  if (!mode) {
    executarMovimentos();
  }
}

void switchModes() {
  buttonDescansar.update();

  if (buttonDescansar.pressed()) {
    mode = !mode;

    if (mode) {
      moveTresSimultaneamente(stepperCorpo, 0, stepperBraco, 0, stepperBase, 2700);
      desabilitarMotores();
    } else {
      habilitarMotores();
    }
  }
}

/** @brief Executa os movimentos programados da garra. */
void executarMovimentos() {
  
  // Move até a posição Inicial.
  moveDoisSimultaneamente(stepperCorpo, 8000, stepperBraco, 4000);
  moverPosicaoIncial();
  moveTresSimultaneamente(stepperCorpo, 8000, stepperBraco, 4000, stepperBase, 5700);
  moverPosicaoIncial();
}

/** @brief Move para a posição inicial da garra, após pegar home. */
void moverPosicaoIncial() {
  moveTresSimultaneamente(stepperCorpo, 3100, stepperBraco, 1000, stepperBase, 2700);
}

/*------------------------------------ Funções Auxiliares ------------------------------------*/

/** @brief Inicializa os botões pela lib debounce2 */
void inicializarBotoes() {
  for (int i = 0; i < N_BUTTON; i++) {
    debouncers[i].attach(buttonPins[i], INPUT_PULLUP);
    debouncers[i].interval(DEBOUNCE_TIME);
    debouncers[i].setPressedState(LOW); 
  }

  buttonDescansar.attach(descansarButtonPin, INPUT_PULLUP);
  buttonDescansar.interval(DEBOUNCE_TIME);
  buttonDescansar.setPressedState(LOW); 
}

/** @brief Habilita os motores configurando os pinos de enable. */
void habilitarMotores() {
  habilitarMotor(stepperBase, X_ENABLE_PIN);
  habilitarMotor(stepperCorpo, Y_ENABLE_PIN);
  habilitarMotor(stepperBraco, Z_ENABLE_PIN);
}

/** @brief Habilita os motores configurando os pinos de enable. */
void desabilitarMotores() {
  desabilitarMotor(stepperBase, X_ENABLE_PIN);
  desabilitarMotor(stepperCorpo, Y_ENABLE_PIN);
  desabilitarMotor(stepperBraco, Z_ENABLE_PIN);
}

/** @brief Configura a velocidade e aceleração dos motores.
 */
void configurarMotores() {
  definirVelocidade(stepperBase, 7000, 1000);
  definirVelocidade(stepperCorpo, 4000, 1000);
  definirVelocidade(stepperBraco, 4000, 1000);
}

/** @brief Define as posições iniciais dos motores e realiza o homing.
 */
void definirHome() {
  stepperBase.moveTo(1600);
  stepperCorpo.moveTo(1600);
  stepperBraco.moveTo(1600);
  
  // Realiza o homing nos motores
  executarHoming(stepperCorpo, debouncers[1]); // Y_MIN
  executarHoming(stepperBraco, debouncers[2]); // Z_MIN
  executarHoming(stepperBase, debouncers[0]);  // X_MIN
}