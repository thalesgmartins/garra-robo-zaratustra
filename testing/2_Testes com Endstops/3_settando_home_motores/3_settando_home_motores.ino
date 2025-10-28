/*--------------------------------------------------------------------------------------------------
Garra Robótica: Settando Home nos Motores - Thales Martins

O código abaixo faz a leitura de um endstop da RAMPS 1.6 e move motor de passo X até que o endstop esteja pressionado.

18/09/2024
--------------------------------------------------------------------------------------------------*/

#include <Bounce2.h>
#include <AccelStepper.h>

// Variáveis do Endstop
#define debounceTime 25
const int buttonPin = 3; // Conectado ao Endstop X
Bounce debouncer = Bounce();

// Definir as constantes do motor e do driver
#define X_DIR_PIN 55 
#define X_STEP_PIN 54
#define X_ENABLE_PIN 38

AccelStepper stepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);

bool home = false;

void setup() {
  Serial.begin(9600);

  // Configurações do Botão
  pinMode(buttonPin, INPUT_PULLUP);
  debouncer.attach(buttonPin);
  debouncer.interval(debounceTime);

  // Configurações do Motor
  habilitarMotor(stepper, X_ENABLE_PIN);
  definirVelocidade(stepper, 10000, 1000);
  stepper.moveTo(100 * 16);

}

void loop() {
  setHome();
  //moverMotor(stepper);
}

void setHome() {
  while (!home) {
    debouncer.update();

    // Mover o motor enquanto o botão não estiver pressionado
    if (!debouncer.rose()) { // Enquanto o endstop não estiver pressionado
      stepper.setSpeed(-500); // Velocidade negativa para mover na direção do endstop
      stepper.runSpeed();     // Executa o movimento em velocidade constante
    }

    // Quando o endstop for pressionado
    if (debouncer.fell()) {
      Serial.println("Botão pressionado - Home Set");
      home = true;
      stepper.stop(); // Para o motor
      stepper.setCurrentPosition(0); // Define a posição atual como "home"
    }
  }
}

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
  if (tempStepper.distanceToGo() == 0) tempStepper.moveTo(-tempStepper.currentPosition());
  tempStepper.run();
}
  

