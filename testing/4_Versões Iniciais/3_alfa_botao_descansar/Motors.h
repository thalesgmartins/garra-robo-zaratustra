/** --------------------------------------------------------------------------------------------------
 * @file Motores.h
 * @brief Define funções base que serão usadas para o funcionamento dos motores.
 * @author Thales Martins
 * @version Alpha 1.3
/** --------------------------------------------------------------------------------------------------*/

#ifndef MOTORS_H
#define MOTORS_H

#include <AccelStepper.h>
#include <Bounce2.h>

/**
 * @brief Habilita um motor configurando seu pino de enable.
 * 
 * @param tempStepper Referência ao objeto AccelStepper.
 * @param enablePin Pino de enable do motor.
 */
void habilitarMotor(AccelStepper &tempStepper, const int enablePin);

/**
 * @brief Habilita um motor configurando seu pino de enable.
 * 
 * @param tempStepper Referência ao objeto AccelStepper.
 * @param enablePin Pino de enable do motor.
 */
void desabilitarMotor(AccelStepper &tempStepper, const int enablePin);

/**
 * @brief Define a velocidade máxima e a aceleração de um motor.
 * 
 * @param tempStepper Referência ao objeto AccelStepper.
 * @param velocidade Velocidade máxima em passos por segundo.
 * @param aceleracao Taxa de aceleração em passos por segundo².
 */
void definirVelocidade(AccelStepper &tempStepper, const int velocidade, const int aceleracao);

/** @brief Verifica e executa o movimento de um motor se necessário.
 *
 * @param tempStepper Referência ao objeto AccelStepper.
 */
void verificaSeDeveMover(AccelStepper &tempStepper);

/** @brief Realiza o processo de homing para um motor utilizando um endstop.
 */
void executarHoming(AccelStepper &tempStepper, Bounce2::Button &tempDebouncer);

/**
 * @brief Move um motor para uma posição específica e espera até alcançar.
 * 
 * @param tempStepper Referência ao objeto AccelStepper.
 * @param pos Posição alvo em passos.
 */
void moveAtePosicaoEsperando(AccelStepper &tempStepper, const int pos);

/**
 * @brief Move dois motores simultaneamente para suas posições alvo.
 * 
 * @param tempStepper1 Referência ao primeiro objeto AccelStepper.
 * @param pos1 Posição alvo para o primeiro motor.
 * @param tempStepper2 Referência ao segundo objeto AccelStepper.
 * @param pos2 Posição alvo para o segundo motor.
 */
void moveDoisSimultaneamente(AccelStepper &tempStepper1, const int pos1, AccelStepper &tempStepper2, const int pos2);

void moveTresSimultaneamente(AccelStepper &tempStepper1, const int pos1, AccelStepper &tempStepper2, const int pos2, AccelStepper &tempStepper3, const int pos3);

#endif