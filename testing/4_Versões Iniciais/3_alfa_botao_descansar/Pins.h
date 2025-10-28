/** --------------------------------------------------------------------------------------------------
 * @file Pins.h
 * @brief Define quais são os pinos em que estão conetados os sensores/motores da Garra.
 * @author Thales Martins
 * @version Alpha 1.3
/** --------------------------------------------------------------------------------------------------*/

#ifndef PINS_H
#define PINS_H

// Pinos dos Endstops
#define ENDSTOP_X_MIN     3
#define ENDSTOP_Y_MIN     14
#define ENDSTOP_Z_MIN     18

// Botão para Entrar no Modo de Descanso
#define ENDSTOP_Z_MAX 19
const int descansarButtonPin = ENDSTOP_Z_MAX;

// Pinos dos Motores
#define X_DIR_PIN          55 
#define X_STEP_PIN         54
#define X_ENABLE_PIN       38

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#endif