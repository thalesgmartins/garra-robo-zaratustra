/** --------------------------------------------------------------------------------------------------
 * @file Pins.h
 * @brief Define quais são os pinos da RAMPS usados pela Garra.
 * @author Thales Martins
 * @version Beta 2.0
 * @date 04/10/2024
/** --------------------------------------------------------------------------------------------------*/

#ifndef PINS_H
  #define PINS_H

  // Endstops da RAMPS
  #define ENDSTOP_X_MIN    3
  #define ENDSTOP_Y_MIN    14
  #define ENDSTOP_Z_MIN    18

  // Botão de Troca de Modos
  #define BUTTON_MODOS_PIN 19

  // Motores X
  #define X_DIR_PIN        55
  #define X_STEP_PIN       54
  #define X_ENABLE_PIN     38

  // Motores Y
  #define Y_DIR_PIN        61
  #define Y_STEP_PIN       60
  #define Y_ENABLE_PIN     56

  // Motores Z
  #define Z_DIR_PIN        48
  #define Z_STEP_PIN       46
  #define Z_ENABLE_PIN     62

  #endif