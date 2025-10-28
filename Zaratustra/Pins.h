/** --------------------------------------------------------------------------------------------------
 * @file Pins.h
 * @brief Define quais são os pinos da RAMPS usados pela Garra.
 * @author Thales Martins
 * @version Beta 2.1
 * @date 14/10/2024
/** --------------------------------------------------------------------------------------------------*/

#pragma once

/**
 * Declarações de pinos feitas com base em um Arduino Mega conectado a RAMPS v1.6 (ou v1.4).
 *
 * Para a substituição de pinos (em caso de danos na placa, ou se necessário adicionar um novo componente), consulte:
 * @link https://reprap.org/wiki/RAMPS_1.4#Pins
**/

//
// Limit Switches
// 
#define ENDSTOP_X_MIN     3          // Base
#define ENDSTOP_Y_MIN    14          // Corpo
#define ENDSTOP_Z_MIN    18          // Braço
#define ENDSTOP_Z_MAX    19          // Mudar o Estado

//
// Steppers
//
#define X_DIR_PIN        55
#define X_STEP_PIN       54
#define X_ENABLE_PIN     38

#define Y_DIR_PIN        61
#define Y_STEP_PIN       60
#define Y_ENABLE_PIN     56

#define Z_DIR_PIN        48
#define Z_STEP_PIN       46
#define Z_ENABLE_PIN     62
