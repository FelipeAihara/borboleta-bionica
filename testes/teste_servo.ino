/*
 * Borboleta Biônica - Teste de Servos
 * ------------------------------------------------------------
 * Sketch isolado para validar a instalação e o sentido de giro
 * dos dois servos (esquerdo e direito) antes de rodar o firmware
 * principal. Não depende do receptor.
 *
 * Ligações:
 *   Servo esquerdo -> pino 4
 *   Servo direito  -> pino 5
 * ------------------------------------------------------------
 */

#include <Servo.h>

const byte pinServoLeft = 4;
const byte pinServoRight = 5;

const int centerAngle = 90;
const int flapAmplitude = 65;
const int sweepStepDelay = 15; // ms entre passos do movimento

Servo servoLeft, servoRight;

void setup() {
  Serial.begin(115200);
  servoLeft.attach(pinServoLeft, 500, 2500);
  servoRight.attach(pinServoRight, 500, 2500);
  servoLeft.write(centerAngle);
  servoRight.write(centerAngle);
  Serial.println("--- TESTE DE SERVOS: BORBOLETA BIONICA ---");
  Serial.println("Movendo os servos de forma espelhada (asas abrindo/fechando)...");
  delay(1000);
}

void loop() {
  // Asas abrindo (sobe esquerda, desce direita) até o limite
  sweepTo(centerAngle + flapAmplitude, centerAngle - flapAmplitude);
  delay(300);

  // Asas fechando (volta ao centro)
  sweepTo(centerAngle, centerAngle);
  delay(300);

  // Asas no sentido contrário
  sweepTo(centerAngle - flapAmplitude, centerAngle + flapAmplitude);
  delay(300);

  // Volta ao centro
  sweepTo(centerAngle, centerAngle);
  delay(800);
}

void sweepTo(int targetL, int targetR) {
  int currentL = servoLeft.read();
  int currentR = servoRight.read();
  int steps = max(abs(targetL - currentL), abs(targetR - currentR));

  for (int i = 1; i <= steps; i++) {
    servoLeft.write(map(i, 0, steps, currentL, targetL));
    servoRight.write(map(i, 0, steps, currentR, targetR));
    delay(sweepStepDelay);
  }

  Serial.print("Servo esquerdo: "); Serial.print(targetL);
  Serial.print(" | Servo direito: "); Serial.println(targetR);
}
