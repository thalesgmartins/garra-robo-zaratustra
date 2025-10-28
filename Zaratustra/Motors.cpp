/** --------------------------------------------------------------------------------------------------
 * @file Motores.cpp
 * @brief Implementação das funções da Classe MotorController.
 * @author Thales Martins
 * @version Beta 2.1
 * @date 14/10/2024
/** --------------------------------------------------------------------------------------------------*/

#include "Motors.h"

/**
 * Instancia o objeto da Classe
 * @attention Se não for fornecido o pino Enable correto, os motores não irão se mover
 * @note Os endstops estão ligados a Classe do motor, para que não haja erros ao executar o homing.
**/
MotorController::MotorController(AccelStepper &stepper, int enablePin, ButtonManager &endstop)
    : stepper(stepper), enablePin(enablePin), endstop(endstop) {}

void MotorController::habilitar() {
  stepper.setEnablePin(enablePin);
  stepper.setPinsInverted(false, false, true);
  stepper.enableOutputs();
}

void MotorController::desabilitar() {
  stepper.disableOutputs();
}

/**
 * Geralmente, a velocidade máxima de um motor é 1000RPM. 
 * A Aceleração é importante quando estamos lidando com carga. Para torques mais altos, 
 * é recomendado usar acelerações menores.
**/
void MotorController::configurar(int velocidade, int aceleracao) {
  stepper.setMaxSpeed(velocidade);
  stepper.setAcceleration(aceleracao);
}

/**
 * @attention Essa função trava o código enquanto o Home do motor não for concluido.
**/
void MotorController::executarHoming() {
  bool home = false;
  endstop.atualizar();

  if (endstop.estaPressionado()) {
    home = true;
  }

  while (!home) {
    while (!endstop.foiPressionado()) {  
      endstop.atualizar();
      stepper.setSpeed(-800);
      stepper.runSpeed();     
    }

    home = true;
    stepper.stop();                 
    stepper.setCurrentPosition(0);  
  }
}

/**
 * @attention Move o motor para a posição definida, porém TRAVA O CÓDIGO.
**/
void MotorController::moverPara(long pos) {
  stepper.moveTo(pos);
  stepper.runToPosition();
}

/**
 * Define qual é a posição alvo, mas SEM MOVER O MOTOR
**/
void MotorController::definirPosicao(long pos) {
  stepper.moveTo(pos);
}

/**
 * Move o motor, caso seja necessário ele se mover.
 * 
 * @note Essa função não trava o código, e é interessante usa-la junto com a função definirPosicao();
**/
void MotorController::executarMovimento() {
  if (stepper.distanceToGo() != 0) {
    stepper.run();
  }
}

long MotorController::getPosicaoAtual() {
  return stepper.currentPosition();
}

long MotorController::getPosicaoAlvo() {
  return stepper.distanceToGo();
}