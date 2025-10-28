/*--------------------------------------------------------------------------------------------------
Garra Robótica: Controlando Nema 17 com AccelStepper - Thales Martins

O código abaixo usa um driver A4988/DRV8825 para fazer o controle de um motor Nema 17 usando a biblioteca AccelStepper.

13/09/2024
--------------------------------------------------------------------------------------------------*/

#include <AccelStepper.h>

// Definir as constantes do motor e do driver
#define DIR_PIN 2
#define STEP_PIN 3

// Criar um objeto AccelStepper
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  //Define a velocidade e aceleração do motor
  stepper.setMaxSpeed(200.0);
  stepper.setAcceleration(200.0);
  
  // Move o motor.
  stepper.moveTo(100 * 32);
}

void loop() {
    // Muda a direção do motor quando chegar no limite
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());
    stepper.run();
}