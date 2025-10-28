/*--------------------------------------------------------------------------------------------------
Garra Robótica: Lendo os pinos Endstop da Ramps com Biblioteca - Thales Martins

O código abaixo faz a leitura de todos os pinos Endstop da Ramps 1.6 usando a bilbioteca Bounce2.

Você deve conectar um dos pinos do botão no negativo e o outro na porta digital. (Não precisa conectar todos os botões).

18/09/2024
--------------------------------------------------------------------------------------------------*/

#include <Bounce2.h>

// Endstops do Eixos X
#define ENDSTOP_X_MIN 3  //D3
#define ENDSTOP_X_MAX 2  //D2

// Endstops do Eixos Y
#define ENDSTOP_Y_MIN 14 //D14
#define ENDSTOP_Y_MAX 15 //D15

// Endstops do Eixos Z 
#define ENDSTOP_Z_MIN 18 //D18
#define ENDSTOP_Z_MAX 19 //D19

//Variáveis dos Botões
const int N_BUTTON = 6; // Numero de botoes
byte buttonPins[N_BUTTON] = { ENDSTOP_X_MIN, ENDSTOP_X_MAX, ENDSTOP_Y_MIN, ENDSTOP_Y_MAX, ENDSTOP_Z_MIN, ENDSTOP_Z_MAX};
Bounce debouncers[N_BUTTON];
#define debounceTime 25 // Tempo de debounce em ms

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < N_BUTTON; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    debouncers[i].attach(buttonPins[i]);
    debouncers[i].interval(debounceTime); // Tempo de debounce em ms
  }
}

void loop() {
  buttons();
}

void buttons() {
  for (int i = 0; i < N_BUTTON; i++) {
    debouncers[i].update();

    // Botão pressionado
    if (debouncers[i].fell()) { 
      Serial.print("Botão ");
      Serial.print(i);
      Serial.println(" pressionado");
    }
    
    // Botão Solto
    if (debouncers[i].rose()) {
      Serial.print("Botão ");
      Serial.print(i);
      Serial.println(" solto");
    }
  }
}
  

