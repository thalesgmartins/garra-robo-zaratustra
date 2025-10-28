/*--------------------------------------------------------------------------------------------------
Garra Robótica: Controlando Dois Nema 17 com RAMPS AccelStepper - Thales Martins

O código abaixo usa um shield RAMPS 1.6 para controlar um motor de passo Nema 17 usando drivers A4988/DRV8825/TMC, usando a biblioteca AccelStepper.

13/09/2024
--------------------------------------------------------------------------------------------------*/

#include <AccelStepper.h>

// Definir as constantes do motor e do driver
#define X_DIR_PIN 55 
#define X_STEP_PIN 54
#define X_ENABLE_PIN 38

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

// Criar um objeto AccelStepper
AccelStepper stepper1(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper stepper3(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);

void setup() {

  //Setta o enable
  stepper1.setEnablePin(X_ENABLE_PIN);
  stepper1.setPinsInverted(false, false, true);
  stepper1.enableOutputs();

  stepper2.setEnablePin(Z_ENABLE_PIN);
  stepper2.setPinsInverted(false, false, true);
  stepper2.enableOutputs();

  stepper3.setEnablePin(Y_ENABLE_PIN);
  stepper3.setPinsInverted(false, false, true);
  stepper3.enableOutputs();

  //Define a velocidade e aceleração do motor
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(1000.0);

  stepper2.setMaxSpeed(800);
  stepper2.setAcceleration(800);

  stepper3.setMaxSpeed(500);
  stepper3.setAcceleration(500);
  
  // Move o motor.
  stepper1.moveTo(100 * 16);
  stepper2.moveTo(100 * 16);
  stepper3.moveTo(100 * 16);
}

void loop() {
    // Muda a direção do motor quando chegar no limite
    if (stepper1.distanceToGo() == 0)
      stepper1.moveTo(-stepper1.currentPosition());
    stepper1.run();

    if (stepper2.distanceToGo() == 0)
      stepper2.moveTo(-stepper2.currentPosition());
    stepper2.run();

    if (stepper3.distanceToGo() == 0)
      stepper3.moveTo(-stepper3.currentPosition());
    stepper3.run();
}