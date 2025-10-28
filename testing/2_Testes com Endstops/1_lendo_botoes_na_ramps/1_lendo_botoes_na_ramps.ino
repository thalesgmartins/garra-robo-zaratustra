/*--------------------------------------------------------------------------------------------------
Garra Robótica: Lendo os pinos Endstop da Ramps - Thales Martins

O código abaixo faz a leitura de todos os pinos Endstop da Ramps 1.6, sem nenhuma biblioteca.

Você deve conectar um dos pinos do botão no negativo e o outro na porta digital. (Não precisa conectar todos os botões)

18/09/2024
--------------------------------------------------------------------------------------------------*/

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
byte buttonPin[N_BUTTON] = { ENDSTOP_X_MIN, ENDSTOP_X_MAX, ENDSTOP_Y_MIN, ENDSTOP_Y_MAX, ENDSTOP_Z_MIN, ENDSTOP_Z_MAX}; // lista com porta de cada botao
byte buttonState[N_BUTTON] = { 0 };              // Lista com estado de cada botao
byte buttonPState[N_BUTTON] = { 0 };             // Lista com estado prévio de cada botao
unsigned long lastBounce[N_BUTTON] = { 0 };      // reseta o relogio
unsigned long buttonTimer[N_BUTTON] = { 0 };     // timer do botao
int buttonTimeOut = 15;

//------------------------------
void setup() {
  Serial.begin(9600);

  for (int i = 0; i < N_BUTTON; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
}

//------------------------------
void loop() {
  buttons();
}

//------------------------------
void buttons() {
  for (int i = 0; i < N_BUTTON; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);

    buttonTimer[i] = millis() - lastBounce[i]; // corre o timer

    if (buttonTimer[i] > buttonTimeOut) {

      if (buttonState[i] != buttonPState[i]) {

        lastBounce[i] = millis();

        if (buttonState[i] == 0) {
          Serial.print("Botao ");
          Serial.print(i);
          Serial.println(" on");
        } 
        
        else {
          Serial.print("Botao ");
          Serial.print(i);
          Serial.println(" off");
        }
      
        buttonPState[i] = buttonState[i];
      }
    }  
  } 
}
  

