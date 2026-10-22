#include <ESP32Servo.h>
Servo servo;

void setup() {
  servo.attach(4, 1000, 2000);
}

void loop() {
  for (int angulo = 0; angulo <= 180; angulo++) {
    servoAsa.write(angulo);
    delay(10);
  }
  for (int angulo = 180; angulo >= 0; angulo--) {
    servoAsa.write(angulo);
    delay(10);
  }
}
