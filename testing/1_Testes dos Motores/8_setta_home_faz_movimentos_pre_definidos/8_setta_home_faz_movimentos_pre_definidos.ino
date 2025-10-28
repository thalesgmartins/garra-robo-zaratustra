/*--------------------------------------------------------------------------------------------------
Garra Robótica: Settando Home nos Motores de forma modular - Thales Martins

O código abaixo faz a leitura de vários endstops da RAMPS 1.6 e move os motores de passo até que o endstop esteja pressionado.

18/09/2024
--------------------------------------------------------------------------------------------------*/

#include <Bounce2.h>
#include <AccelStepper.h>

//Variáveis dos Botões
#define ENDSTOP_X_MIN 3  
#define ENDSTOP_X_MAX 2  
#define ENDSTOP_Y_MIN 14 

const int N_BUTTON = 3; // Numero de botoes
byte buttonPins[N_BUTTON] = { ENDSTOP_X_MIN, ENDSTOP_X_MAX, ENDSTOP_Y_MIN};
Bounce debouncers[N_BUTTON];
#define debounceTime 25

// Definir as constantes do motor e do driver
#define X_DIR_PIN          55 
#define X_STEP_PIN         54
#define X_ENABLE_PIN       38

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

// Criar um objeto AccelStepper
AccelStepper stepper1(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepper3(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < N_BUTTON; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    debouncers[i].attach(buttonPins[i]);
    debouncers[i].interval(debounceTime); // Tempo de debounce em ms
  }

  // Habilita os motores
  habilitarMotor(stepper1, X_ENABLE_PIN);
  habilitarMotor(stepper2, Z_ENABLE_PIN);
  habilitarMotor(stepper3, Y_ENABLE_PIN);

  // Define a velocidade e Aceleração
  definirVelocidade(stepper1, 10000, 1000);
  definirVelocidade(stepper2, 800, 800);
  definirVelocidade(stepper3, 500, 500);
  
  // Move o motor.
  stepper1.moveTo(100 * 16);
  stepper2.moveTo(100 * 16);
  stepper3.moveTo(100 * 16);

  // Pega home nos 3 motores
  definirHome(stepper2, debouncers[1]);
  definirHome(stepper1, debouncers[0]);
}

void loop() {
  moveAtePosicaoEsperando(stepper1, 1000);
  moveAtePosicaoEsperando(stepper1, 0);

  moveSimultaneamente(stepper1, 2500, stepper2, 4000);
  moveSimultaneamente(stepper1, 0, stepper2, 6000);

  moveAtePosicaoEsperando(stepper2, 0);
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

void definirHome(AccelStepper &tempStepper, Bounce &tempDebouncer) {
  bool home = false;

  while (!home) {
    tempDebouncer.update();

    // Mover o motor enquanto o botão não estiver pressionado
    if (!tempDebouncer.rose()) {  // Enquanto o endstop não estiver pressionado
      tempStepper.setSpeed(-500); // Velocidade negativa para mover na direção do endstop
      tempStepper.runSpeed();     // Executa o movimento em velocidade constante
    }

    // Quando o endstop for pressionado
    if (tempDebouncer.fell()) {
      Serial.println("Botão pressionado - Home Set");
      home = true;
      tempStepper.stop();                 // Para o motor
      tempStepper.setCurrentPosition(0);  // Define a posição atual como "home"
    }
  }
}

void verificaSeDeveMover(AccelStepper &tempStepper) {
  if (tempStepper.distanceToGo() != 0) {
    tempStepper.run();
  }
}

void moveAtePosicaoEsperando(AccelStepper &tempStepper, const int pos) {
  tempStepper.moveTo(pos);
  tempStepper.runToPosition(); // O programa espera até que o motor alcance a posição
}

void moveSimultaneamente(AccelStepper &tempStepper1, const int pos1, AccelStepper &tempStepper2, const int pos2) {
  while (tempStepper1.currentPosition() != pos1 && tempStepper2.currentPosition() != pos2) {
    tempStepper1.moveTo(pos1);
    tempStepper2.moveTo(pos2);

    verificaSeDeveMover(tempStepper1);
    verificaSeDeveMover(tempStepper2);
  }
}

  

