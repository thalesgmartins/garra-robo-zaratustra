/** --------------------------------------------------------------------------------------------------
 * @file Buttons.cpp
 * @brief Implementa das funções da Classe ButtonManager.
 * @author Thales Martins
 * @version Beta 2.0
 * @date 04/10/2024
/** --------------------------------------------------------------------------------------------------*/

#include "Buttons.h"

ButtonManager::ButtonManager(int pin) {
  button.attach(pin, INPUT_PULLUP);
  button.interval(25);
  button.setPressedState(LOW);
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

bool ButtonManager::fell() {
  return button.fell();
}

bool ButtonManager::rose() {
  return button.rose();
}

Bounce2::Button& ButtonManager::getButton() {
  return button;
}