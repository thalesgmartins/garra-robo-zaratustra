/** --------------------------------------------------------------------------------------------------
 * @file Motors.h
 * @brief Define quais são as funções da Classe MotorController.
 * @author Thales Martins
 * @version Beta 2.1
 * @date 14/10/2024
/** --------------------------------------------------------------------------------------------------*/

#pragma once

#include <AccelStepper.h>
#include "Buttons.h"

class MotorController {
  public:
    MotorController(AccelStepper &stepper, int enablePin, ButtonManager &endstop);
    void configurar(int velocidade, int aceleracao);
    
    /*
     * Habilitar e Desabilitar motores para evitar superaquecimento e trabalho desnecessário
     * dos drivers
    */
    void habilitar();
    void desabilitar();

    /*
     * Funções de Movimento e Posição
    */
    void moverPara(long pos);
    void definirPosicao(long pos);
    void executarMovimento();
    void executarHoming();
    long getPosicaoAtual();
    long getPosicaoAlvo();
  private:
    AccelStepper &stepper;
    ButtonManager &endstop;
    int enablePin;
};
