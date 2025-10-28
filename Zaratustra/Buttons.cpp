/** --------------------------------------------------------------------------------------------------
 * @file Buttons.cpp
 * @brief Implementa das funções da Classe ButtonManager.
 * @author Thales Martins
 * @version Beta 2.1
 * @date 14/10/2024
/** --------------------------------------------------------------------------------------------------*/

#include "Buttons.h"

/**
 * Precisa definir como INPUT_PULLUP para usar a Resistência Interna do Arduino.
 * Também precisa definir que os Endstops são LOW quando pressionados.
**/
ButtonManager::ButtonManager(int pin) {
  button.attach(pin, INPUT_PULLUP);
  button.setPressedState(LOW);
  button.interval(25);
}

void ButtonManager::atualizar() {
  button.update();
}

bool ButtonManager::foiPressionado() {
  return button.pressed();
}

bool ButtonManager::estaPressionado() {
  return button.isPressed();
}