/*--------------------------------------------------------------------------------------------------
Garra Robótica: Controlando Nema 17 sem Biblioteca - Thales Martins

O código abaixo usa um driver A4988/DRV8825 para fazer o controle de um motor Nema 17 sem nenhuma biblioteca.

Para mais informações, acesse: https://capsistema.com.br/index.php/2022/05/31/como-controlar-um-motor-de-passo-com-driver-drv8825-e-arduino/
13/09/2024
--------------------------------------------------------------------------------------------------*/

// Define os pinos do motor e os passos por volta.
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

void setup() {
  // Declara os pinos do motor como saída
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  // Define a direção de giro como horária
  digitalWrite(dirPin, HIGH);
  
  // Gira uma volta, devagar:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // Essas 4 linhas resultam em 1 passo
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(1000);

  // Define a diração de giro como anti-horária:
  digitalWrite(dirPin, LOW);

  // Gira uma volta, rápido:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // Essas 4 linhas resultam em 1 passo
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  delay(1000);

  // Define a direção de giro como horária:
  digitalWrite(dirPin, HIGH);

  // Gira o motor 5 vezes, rápido:
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // Essas 4 linhas resultam em 1 passo
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(1000);

  // Define o giro como anti-horário
  digitalWrite(dirPin, LOW);
  
  //Gira o motor 5 vezes, rápido:
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // Essas 4 linhas resultam em 1 passo
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(1000);
}