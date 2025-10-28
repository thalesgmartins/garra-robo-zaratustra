/** --------------------------------------------------------------------------------------------------
 * @file Zaratustra.ino
 * @brief Faz o controle da garra, utilizando Classes para cada Motor e Botão.
 * @author Thales Martins
 * @version Beta 2.0
 * @date 11/10/2024
/** --------------------------------------------------------------------------------------------------*/

#include "Pins.h"
#include "Motors.h"
#include "Buttons.h"

// Gerenciamento de botões
ButtonManager buttonDescansar(BUTTON_MODOS_PIN);

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

bool mode = true;
bool Pmode = false;

void setup() {
  Serial.begin(9600);

  motorBase.habilitar();
  motorCorpo.habilitar();
  motorBraco.habilitar();

  motorBase.configurar(2500, 1000);
  motorCorpo.configurar(2500, 1000);
  motorBraco.configurar(2500, 1000);

  motorCorpo.executarHoming();
  motorBraco.executarHoming();
  motorBase.executarHoming();

  moverPosicaoInicial();
}

void loop() {
  buttonDescansar.atualizar();



  if (buttonDescansar.estaPressionado()) {
    if (mode == false && mode != Pmode) {
      motorBase.habilitar();
      motorCorpo.habilitar();
      motorBraco.habilitar();

      motorCorpo.executarHoming();
      motorBraco.executarHoming();
      motorBase.executarHoming();
      mode = true;
      Pmode != mode;
    }

    executarMovimentos();

    Serial.write(1);
    delay(1500);
  } else {
    moverMotores(0, 0, 4000);

    motorBase.desabilitar();
    motorCorpo.desabilitar();
    motorBraco.desabilitar();
    mode = false;
    Pmode = !mode;
  }

  motorBase.executarMovimento();
  motorCorpo.executarMovimento();
  motorBraco.executarMovimento();
}

void executarMovimentos() {
  long posInicialCorpo = 2500, posInicialBraco = 2600, posInicialBase = 4100;
  long posFinalCorpo = 2500, posFinalBraco = 2600, posFinalBase = 10000;

  moverPosicaoInicial();

  moverSimultaneamente(posInicialCorpo, posInicialBraco, posInicialBase);

  moverPosicaoInicial();
  moverMotor(motorBase, posFinalBase);

  moverSimultaneamente(posFinalCorpo, posFinalBraco, posFinalBase);
  moverPosicaoInicial();
}

void moverPosicaoInicial() {
  long posCorpo = 1200, posBraco = 1400, posBase = 4100;
  moverSimultaneamente(posCorpo, posBraco, posBase);
}

void moverMotores(long posCorpo, long posBraco, long posBase) {
  motorBase.moverPara(posBase);
  moverSimultaneamente(posCorpo, posBraco, posBase);
}

void moverMotor(MotorController motor, long pos) {
  motor.moverSemPausar(pos);

  while (motor.getPosicaoAtual() != pos) {
    motor.executarMovimento();
  }
}

void moverSimultaneamente(long posCorpo, long posBraco, long posBase) {
  motorCorpo.moverSemPausar(posCorpo);
  motorBraco.moverSemPausar(posBraco);
  motorBase.moverSemPausar(posBase);

  while (motorCorpo.getPosicaoAtual() != posCorpo || motorBraco.getPosicaoAtual() != posBraco || motorBase.getPosicaoAtual() != posBase) {
    motorCorpo.executarMovimento();
    motorBraco.executarMovimento();
    motorBase.executarMovimento();
  }
}