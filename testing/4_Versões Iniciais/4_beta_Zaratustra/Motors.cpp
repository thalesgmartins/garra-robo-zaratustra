/** --------------------------------------------------------------------------------------------------
 * @file Motores.cpp
 * @brief Implementação das funções da Classe MotorController.
 * @author Thales Martins
 * @version Beta 2.0
 * @date 04/10/2024
/** --------------------------------------------------------------------------------------------------*/

#include "Motors.h"

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

void MotorController::configurar(int velocidade, int aceleracao) {
  stepper.setMaxSpeed(velocidade);
  stepper.setAcceleration(aceleracao);
}

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

void MotorController::moverPara(int pos) {
  stepper.moveTo(pos);
  stepper.runToPosition();
}

void MotorController::moverSemPausar(int pos) {
  stepper.moveTo(pos);
}

void MotorController::executarMovimento() {
  if (stepper.distanceToGo() != 0) {
    stepper.run();
  }
}

void MotorController::verificaSeDeveMover() {
  if (stepper.distanceToGo() != 0) {
    stepper.run();
  }
}

long MotorController::getPosicaoAtual() {
  return stepper.currentPosition();
}