/** --------------------------------------------------------------------------------------------------
 * @file Motores.cpp
 * @brief Implementação das funções de controle dos motores.
 * @author Thales Martins
 * @version Alpha 1.3
/** --------------------------------------------------------------------------------------------------*/

#include "Motors.h"

/** Funções para configurar os motores
*/
void habilitarMotor(AccelStepper &tempStepper, const int enablePin) {
  tempStepper.setEnablePin(enablePin);
  tempStepper.setPinsInverted(false, false, true);
  tempStepper.enableOutputs();
}

void desabilitarMotor(AccelStepper &tempStepper, const int enablePin) {
  tempStepper.setEnablePin(enablePin);
  tempStepper.setPinsInverted(false, false, true);
  tempStepper.disableOutputs();
}

void definirVelocidade(AccelStepper &tempStepper, const int velocidade, const int aceleracao) {
  tempStepper.setMaxSpeed(velocidade);
  tempStepper.setAcceleration(aceleracao);
}

void verificaSeDeveMover(AccelStepper &tempStepper) {
  if (tempStepper.distanceToGo() != 0) {
    tempStepper.run();
  }
}

/** Funções para Mover os Motores
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
}

void moveAtePosicaoEsperando(AccelStepper &tempStepper, const int pos) {
  tempStepper.moveTo(pos);
  tempStepper.runToPosition();
}

void moveDoisSimultaneamente(AccelStepper &tempStepper1, const int pos1, AccelStepper &tempStepper2, const int pos2) {
  tempStepper1.moveTo(pos1);
  tempStepper2.moveTo(pos2);

  while (tempStepper1.currentPosition() != pos1 && tempStepper2.currentPosition() != pos2) {
    verificaSeDeveMover(tempStepper1);
    verificaSeDeveMover(tempStepper2);
  }
}

void moveTresSimultaneamente(AccelStepper &tempStepper1, const int pos1, AccelStepper &tempStepper2, const int pos2, AccelStepper &tempStepper3, const int pos3) {
  tempStepper1.moveTo(pos1);
  tempStepper2.moveTo(pos2);
  tempStepper2.moveTo(pos3);

  while (tempStepper1.currentPosition() != pos1 && tempStepper2.currentPosition() != pos2 && tempStepper3.currentPosition() != pos3) {
    verificaSeDeveMover(tempStepper1);
    verificaSeDeveMover(tempStepper2);
    verificaSeDeveMover(tempStepper3);
  }
}
