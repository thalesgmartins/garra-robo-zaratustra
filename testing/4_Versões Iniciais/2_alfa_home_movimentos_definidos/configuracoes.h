#ifndef CONFIGURACOES_H
#define CONFIGURACOES_H

/*--------------------------------------- Inclusão de Bibliotecas ---------------------------------------*/
#include <Bounce2.h>
#include <AccelStepper.h>

/*--------------------------------------- Definição de Pinos ---------------------------------------*/

// Pinos dos Endstops
#define ENDSTOP_X_MIN     3
#define ENDSTOP_Y_MIN     14
#define ENDSTOP_Z_MIN     18

const int N_BUTTON = 3;
byte buttonPins[N_BUTTON] = { ENDSTOP_X_MIN, ENDSTOP_Y_MIN, ENDSTOP_Z_MIN};

Bounce2::Button debouncers[N_BUTTON] = { Bounce2::Button() };
const int DEBOUNCE_TIME = 25;

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