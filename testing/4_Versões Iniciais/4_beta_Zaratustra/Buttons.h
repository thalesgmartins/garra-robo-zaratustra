/** --------------------------------------------------------------------------------------------------
 * @file Buttons.h
 * @brief Define quais são as funções da Classe MotorController.
 * @author Thales Martins
 * @version Beta 2.0
 * @date 04/10/2024
/** --------------------------------------------------------------------------------------------------*/

#ifndef BUTTONS_H
  #define BUTTONS_H

  #include <Bounce2.h>

  class ButtonManager {
    public:
      ButtonManager(int pin);
      void atualizar();
      bool foiPressionado();
      bool estaPressionado();
      bool fell();
      bool rose();
      Bounce2::Button& getButton();
    private:
      Bounce2::Button button;
  };

  #endif