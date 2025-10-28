/*--------------------------------------------------------------------------------------------------
 * Zaratustra: Garra Robótica - Thales Martins
 * 
 * Código Fonte da Zaratustra, controlando 3 Nema17 em uma RAMPS 1.6 
 * 
 * 26/09/2024
 *--------------------------------------------------------------------------------------------------*/

/*------------------------------------- Definições e Declarações -------------------------------------*/

// Chama o Arquivo de Inclusao de Bibliotecas e Declaração de Pinos
#include "configuracoes.h"

// Criação dos objetos AccelStepper
AccelStepper stepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperY(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperZ(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);

/*--------------------------------------- Inicialização ---------------------------------------*/

void setup() {
  Serial.begin(9600);
  
  inicializarBotoes();
  habilitarMotores();
  configurarMotores();
  definirPosicoesIniciais();
  moveSimultaneamente(stepperY, 3300, stepperZ, 1000);
  moveAtePosicaoEsperando(stepperX, 3000);
}

/*------------------------------------- Loop Principal -------------------------------------*/

void loop() {
  //executarMovimentos();
}

/** @brief Executa os movimentos programados da garra. 
*/
void executarMovimentos() {
  
  // Move até a posição Inicial.
  moveAtePosicaoEsperando(stepperX, 1000);
  moveAtePosicaoEsperando(stepperX, 0);

  // Gira a Base
  moveSimultaneamente(stepperX, 2500, stepperY, 4000);
  
  // Desce a Garra
  moveSimultaneamente(stepperX, 0, stepperY, 6000);

  // Volta a garra
  moveAtePosicaoEsperando(stepperY, 0);
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

  while (!home) {

    // Mover o motor enquanto o endstop não estiver pressionado
    while (!tempDebouncer.pressed()) {  
      tempDebouncer.update();
      tempStepper.setSpeed(-500); // Velocidade negativa para mover na direção do endstop
      tempStepper.runSpeed();     
    }

    // Quando o endstop for pressionado
    Serial.println("Botão pressionado - Home Set");
    home = true;
    tempStepper.stop();                 
    tempStepper.setCurrentPosition(0);  
  }
}

/** @brief Verifica e executa o movimento de um motor se necessário.
 */
void verificaSeDeveMover(AccelStepper &tempStepper) {
  if (tempStepper.distanceToGo() != 0) {
    tempStepper.run();
  }
}

/*------------------------------------ Funções Auxiliares ------------------------------------*/

/** @brief Inicializa os botões com debounce.
*/
void inicializarBotoes() {
  for (int i = 0; i < N_BUTTON; i++) {
    debouncers[i].attach(buttonPins[i], INPUT_PULLUP);
    debouncers[i].interval(DEBOUNCE_TIME);
    debouncers[i].setPressedState(LOW); 
  }
}

/** @brief Habilita os motores configurando os pinos de enable.
 */
void habilitarMotores() {
  habilitarMotor(stepperX, X_ENABLE_PIN);
  habilitarMotor(stepperY, Y_ENABLE_PIN);
  habilitarMotor(stepperZ, Z_ENABLE_PIN);
}

/** @brief Configura a velocidade e aceleração dos motores.
 */
void configurarMotores() {
  definirVelocidade(stepperX, 10000, 1000);
  definirVelocidade(stepperY, 500, 500);
  definirVelocidade(stepperZ, 800, 800);
}

/** @brief Define as posições iniciais dos motores e realiza o homing.
 */
void definirPosicoesIniciais() {
  stepperX.moveTo(1600); // 100 * 16 passos
  stepperY.moveTo(1600);
  stepperZ.moveTo(1600);
  
  // Realiza o homing nos motores
  executarHoming(stepperY, debouncers[1]); // Y_MIN
  executarHoming(stepperZ, debouncers[2]); // Z_MIN
  executarHoming(stepperX, debouncers[0]); // X_MIN

}