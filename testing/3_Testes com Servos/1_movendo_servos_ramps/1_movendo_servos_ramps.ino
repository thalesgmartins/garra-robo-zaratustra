/*--------------------------------------------------------------------------------------------------
Garra Robótica: Controlando Servos de 10KGs  - Thales Martins

O código abaixo controla Servos de 10KG na Ramps 1.6 usando a bilbioteca padrão de Servos.

Todos os pinos estão definidos no código, e o pino que você quer usar tem que ser colocado em  meuServo.attach(pino);

18/09/2024
--------------------------------------------------------------------------------------------------*/
#include <Servo.h>

// Definição dos Servos
#define SERVO_1 11  // D11
#define SERVO_2 6   // D6
#define SERVO_3 5   // D5
#define SERVO_4 4   // D4


Servo meuServo;

void setup() {
  Serial.begin(9600);
  meuServo.attach(SERVO_1); // Pino PWM conectado
}

void loop() {
  Serial.println("Movendo para 10");
  meuServo.write(20);  
  delay(1000);

  Serial.println("Movendo para 30");
  meuServo.write(30);  
  delay(1000);

  Serial.println("Movendo para 45");
  meuServo.write(45);   
  delay(1000);
  
  Serial.println("Movendo para 60");
  meuServo.write(60); 
  delay(1000);
}