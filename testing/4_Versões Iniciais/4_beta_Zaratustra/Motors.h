/** --------------------------------------------------------------------------------------------------
 * @file Motors.h
 * @brief Define quais são as funções da Classe MotorController.
 * @author Thales Martins
 * @version Beta 2.0
 * @date 04/10/2024
/** --------------------------------------------------------------------------------------------------*/

#ifndef MOTORS_H
  #define MOTORS_H

  #include <AccelStepper.h>
  #include "Buttons.h"

  class MotorController {
  public:
    MotorController(AccelStepper &stepper, int enablePin, ButtonManager &endstop);
    void habilitar();
    void desabilitar();
    void configurar(int velocidade, int aceleracao);
    void executarHoming();
    void moverPara(int pos);
    void moverSemPausar(int pos);
    void executarMovimento();
    long getPosicaoAtual();
  private:
    AccelStepper &stepper;
    ButtonManager &endstop;
    void verificaSeDeveMover();
    int enablePin;
  };

  #endif