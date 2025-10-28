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

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24

// Criar um objeto AccelStepper
AccelStepper stepper1(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper stepper3(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepper4(AccelStepper::DRIVER, E0_STEP_PIN, E0_DIR_PIN);

void habilitarMotor(AccelStepper &tempStepper, const int enablePin) {
  tempStepper.setEnablePin(enablePin);
  tempStepper.setPinsInverted(false, false, true);
  tempStepper.enableOutputs();
}

void definirVelocidade(AccelStepper &tempStepper, const int velocidade, const int aceleracao) {
  tempStepper.setMaxSpeed(velocidade);
  tempStepper.setAcceleration(aceleracao);
}

void moverMotor(AccelStepper &tempStepper) {
   if (tempStepper.distanceToGo() == 0)
      tempStepper.moveTo(-tempStepper.currentPosition());
    tempStepper.run();
}

void setup() {

  // Habilita os motores
  habilitarMotor(stepper1, X_ENABLE_PIN);
  habilitarMotor(stepper2, Z_ENABLE_PIN);
  habilitarMotor(stepper3, Y_ENABLE_PIN);
  habilitarMotor(stepper4, E0_ENABLE_PIN);

  // Define a velocidade e Aceleração
  definirVelocidade(stepper1, 10000, 1000);
  definirVelocidade(stepper2, 800, 800);
  definirVelocidade(stepper3, 500, 500);
  definirVelocidade(stepper4, 250, 250);
  
  // Move o motor.
  stepper1.moveTo(100 * 16);
  stepper2.moveTo(100 * 16);
  stepper3.moveTo(100 * 16);
  stepper4.moveTo(100 * 16);
}

void loop() {
  moverMotor(stepper1);
  moverMotor(stepper2);
  moverMotor(stepper3);
  moverMotor(stepper4);
}