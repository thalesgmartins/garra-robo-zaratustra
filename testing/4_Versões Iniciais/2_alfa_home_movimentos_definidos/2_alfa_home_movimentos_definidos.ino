/*--------------------------------------------------------------------------------------------------
 * Zaratustra: Garra Robótica - Thales Martins
 * 
 * Código Fonte da Zaratustra: Usa uma placa RAMPS 1.6 para fazer o controle de motores Nema 17 e enviar dados de ciclio para o Tecminer.
 * 
 * 02/10/2024
/*--------------------------------------------------------------------------------------------------*/

/*------------------------------------- Definições e Declarações -------------------------------------*/

// Chama o Arquivo de Inclusao de Bibliotecas e Declaração de Pinos
#include "configuracoes.h"

// Criação dos objetos AccelStepper
AccelStepper stepperBase(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperCorpo(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperBraco(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);

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
  executarMovimentos();
}

/** @brief Executa os movimentos programados da garra. */
void executarMovimentos() {
  
  // Move até a posição Inicial.
  moveSimultaneamente(stepperCorpo, 3500, stepperBraco, 3000);
  delay(1000);

  moverPosicaoIncial();
  delay(1000);

  moveAtePosicaoEsperando(stepperBase, 6000);
  moveSimultaneamente(stepperCorpo, 3500, stepperBraco, 300);
  delay(1500);

  moverPosicaoIncial();
  delay(2000);
}

/** @brief Move para a posição inicial da garra, após pegar home. */
void moverPosicaoIncial() {
  moveAtePosicaoEsperando(stepperCorpo, 1500);
  moveSimultaneamente(stepperCorpo, 2000, stepperBraco, 800);
  moveAtePosicaoEsperando(stepperBase, 2700);
}
/*------------------------------------ Funções de Movimento ------------------------------------*/

/**
 * @brief Move um motor para uma posição específica e espera até alcançar.
 * 
 * @param tempStepper Referência ao objeto AccelStepper.
 * @param pos Posição alvo em passos.
 */
void moveAtePosicaoEsperando(AccelStepper &tempStepper, const int pos) {
  tempStepper.moveTo(pos);
  tempStepper.runToPosition(); // O programa espera até que o motor alcance a posição
}

/**
 * @brief Move dois motores simultaneamente para suas posições alvo.
 * 
 * @param tempStepper1 Referência ao primeiro objeto AccelStepper.
 * @param pos1 Posição alvo para o primeiro motor.
 * @param tempStepper2 Referência ao segundo objeto AccelStepper.
 * @param pos2 Posição alvo para o segundo motor.
 */
void moveSimultaneamente(AccelStepper &tempStepper1, const int pos1, AccelStepper &tempStepper2, const int pos2) {
  tempStepper1.moveTo(pos1);
  tempStepper2.moveTo(pos2);

  while (tempStepper1.currentPosition() != pos1 || tempStepper2.currentPosition() != pos2) {
    verificaSeDeveMover(tempStepper1);
    verificaSeDeveMover(tempStepper2);
  }
}

/*------------------------------------ Funções Accel Stepper ------------------------------------*/

/** @brief Habilita um motor configurando seu pino de enable.
 */
void habilitarMotor(AccelStepper &tempStepper, const int enablePin) {
  tempStepper.setEnablePin(enablePin);
  tempStepper.setPinsInverted(false, false, true);
  tempStepper.enableOutputs();
}

/** @brief Define a velocidade máxima e a aceleração de um motor.
 */
void definirVelocidade(AccelStepper &tempStepper, const int velocidade, const int aceleracao) {
  tempStepper.setMaxSpeed(velocidade);
  tempStepper.setAcceleration(aceleracao);
}

/** @brief Realiza o processo de homing para um motor utilizando um endstop.
 */
void executarHoming(AccelStepper &tempStepper, Bounce2::Button &tempDebouncer) {
  bool home = false;
  tempDebouncer.update();

  if (tempDebouncer.isPressed()) {
    home = true;
  }

  while (!home) {

    // Mover o motor enquanto o endstop não estiver pressionado
    while (!tempDebouncer.pressed()) {  
      tempDebouncer.update();
      tempStepper.setSpeed(-800); // Velocidade negativa para mover na direção do endstop
      tempStepper.runSpeed();     
    }

    // Quando o endstop for pressionado
    Serial.println("Botão pressionado - Home Set");
    home = true;
    tempStepper.stop();                 
    tempStepper.setCurrentPosition(0);  
  }

  //moveAtePosicaoEsperando(tempStepper, 500);
}

/** @brief Verifica e executa o movimento de um motor se necessário.
 */
void verificaSeDeveMover(AccelStepper &tempStepper) {
  if (tempStepper.distanceToGo() != 0) {
    tempStepper.run();
  }
}

/*------------------------------------ Funções Auxiliares ------------------------------------*/

/** @brief Inicializa os botões pela lib debounce2 */
void inicializarBotoes() {
  for (int i = 0; i < N_BUTTON; i++) {
    debouncers[i].attach(buttonPins[i], INPUT_PULLUP);
    debouncers[i].interval(DEBOUNCE_TIME);
    debouncers[i].setPressedState(LOW); 
  }
}

/** @brief Habilita os motores configurando os pinos de enable. */
void habilitarMotores() {
  habilitarMotor(stepperBase, X_ENABLE_PIN);
  habilitarMotor(stepperCorpo, Y_ENABLE_PIN);
  habilitarMotor(stepperBraco, Z_ENABLE_PIN);
}

/** @brief Configura a velocidade e aceleração dos motores.
 */
void configurarMotores() {
  definirVelocidade(stepperBase, 7000, 1000);
  definirVelocidade(stepperCorpo, 1000, 1000);
  definirVelocidade(stepperBraco, 4000, 1000);
}

/** @brief Define as posições iniciais dos motores e realiza o homing.
 */
void definirHome() {
  stepperBase.moveTo(1600); // 100 * 16 passos
  stepperCorpo.moveTo(1600);
  stepperBraco.moveTo(1600);
  
  // Realiza o homing nos motores
  executarHoming(stepperCorpo, debouncers[1]); // Y_MIN
  executarHoming(stepperBraco, debouncers[2]); // Z_MIN
  executarHoming(stepperBase, debouncers[0]); // X_MIN

}