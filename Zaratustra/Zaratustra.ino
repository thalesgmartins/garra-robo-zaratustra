/** --------------------------------------------------------------------------------------------------
 * @file Zaratustra.ino
 * @brief Faz o controle da garra, utilizando Classes para cada Motor e Botão.
 * @author Thales Martins
 * @version Beta 2.1
 * @date 14/10/2024
/** --------------------------------------------------------------------------------------------------*/

#include "Pins.h"
#include "Motors.h"
#include "Buttons.h"

// Gerenciamento de botões
ButtonManager buttonTrocarModo(ENDSTOP_Z_MAX);

ButtonManager endstopBase(ENDSTOP_X_MIN);
ButtonManager endstopCorpo(ENDSTOP_Y_MIN);
ButtonManager endstopBraco(ENDSTOP_Z_MIN);

// Declaração dos motores
AccelStepper stepperBase(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperCorpo(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperBraco(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);

// Controladores de motores
MotorController motorBase(stepperBase, X_ENABLE_PIN, endstopBase);
MotorController motorCorpo(stepperCorpo, Y_ENABLE_PIN, endstopCorpo);
MotorController motorBraco(stepperBraco, Z_ENABLE_PIN, endstopBraco);

bool movimentoConcluido = true;
byte estagioDosMovimentos = 0;

//================================================================================
// Estado do botão
bool mode = true;
bool Pmode = false;
//=================================================================================


void setup() {
  Serial.begin(9600);

  motorBase.habilitar();
  motorCorpo.habilitar();
  motorBraco.habilitar();

  motorBase.configurar(600, 500);
  motorCorpo.configurar(600, 500);
  motorBraco.configurar(600, 500);

  motorCorpo.executarHoming();
  motorBraco.executarHoming();
  motorBase.executarHoming();

}

void loop() {
  buttonTrocarModo.atualizar();

  executarMovimentos();


  if (!movimentoConcluido) {
    executarMovimentos();
  }

  // Atualiza movimentos continuamente, sem travar o código
  motorBase.executarMovimento();
  motorCorpo.executarMovimento();
  motorBraco.executarMovimento();

  if (movimentoConcluido) {
    estagioDosMovimentos++;
    movimentoConcluido = false;
  }

  // Verifica se todos os motores chegaram à posição alvo
  if (  motorBase.getPosicaoAtual() == motorBase.getPosicaoAlvo() && 
      motorCorpo.getPosicaoAtual() == motorCorpo.getPosicaoAlvo() &&
      motorBraco.getPosicaoAtual() == motorBraco.getPosicaoAlvo()) {
    movimentoConcluido = true;
  }
}

void executarMovimentos() {
  long posInicialCorpo = 2500, posInicialBraco = 2600, posInicialBase = 4100;
  long posFinalCorpo = 2500, posFinalBraco = 2600, posFinalBase = 10000;

  switch (estagioDosMovimentos) {
    case 0:
      moverPosicaoInicial();
      break;
    case 1:
      moverSimultaneamente(posInicialCorpo, posInicialBraco, posInicialBase);
      break;
    case 2:
      moverPosicaoInicial();
      break;
    case 3:
      moverMotor(motorBase, posFinalBase);  // Move o motor base individualmente
      break;
    case 4:
      moverSimultaneamente(posFinalCorpo, posFinalBraco, posFinalBase);  // Move para a posição final
      break;
    case 5:
      moverPosicaoInicial();
      break;
    case 6:
      moverPosicaoInicial();
      break;
    case 7:
      moverMotor(motorBase, posFinalBase);
      break;
    case 8:
      moverSimultaneamente(posFinalCorpo, posFinalBraco, posFinalBase);
      break;
    case 9:
      moverPosicaoInicial();
      break;
    default:
      estagioDosMovimentos = 0;
      break;
  }
}

//
// Funções de Movimento dos Motores
//
void moverPosicaoInicial() {
  long posCorpo = 1200, posBraco = 1400, posBase = 4100;
  moverSimultaneamente(posCorpo, posBraco, posBase);
}

void moverMotor(MotorController &motor, long pos) {
  motor.definirPosicao(pos);
}

void moverSimultaneamente(long posCorpo, long posBraco, long posBase) {
  motorCorpo.definirPosicao(posCorpo);
  motorBraco.definirPosicao(posBraco);
  motorBase.definirPosicao(posBase);
}