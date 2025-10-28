/** --------------------------------------------------------------------------------------------------
 * @file Buttons.h
 * @brief Define quais são as funções da Classe ButtonManager
 * @author Thales Martins
 * @version Beta 2.1
 * @date 14/10/2024
/** --------------------------------------------------------------------------------------------------*/

#pragma once

#include <Bounce2.h>

class ButtonManager {
  public:
    ButtonManager(int pin);
    void atualizar();
    bool foiPressionado();
    bool estaPressionado();
  private:
    Bounce2::Button button;
};
