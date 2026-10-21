/*
 * Borboleta Biônica - Teste do Receptor em modo PPM
 * ------------------------------------------------------------
 * Sketch isolado para validar a recepção do receptor configurado
 * em modo PPM (todos os canais combinados em um único pino de
 * sinal), antes de rodar o firmware principal. Lê os canais via
 * biblioteca PPMReader e imprime os valores e o status do link
 * no Monitor Serial.
 *
 * Ligações:
 *   Sinal PPM do receptor -> pino 2 (interrupção)
 *
 * Biblioteca necessária: PPMReader
 * ------------------------------------------------------------
 */

#include <PPMReader.h>

const byte interruptPin = 2;
const byte channelAmount = 8;
PPMReader ppm(interruptPin, channelAmount);

unsigned long lastPrintTime = 0;
const int printInterval = 200; // ms

void setup() {
  Serial.begin(115200);
  Serial.println("--- TESTE DO RECEPTOR EM MODO PPM ---");
}

void loop() {
  if (millis() - lastPrintTime >= printInterval) {
    lastPrintTime = millis();

    unsigned long ch3Raw = ppm.latestValidChannelValue(3, 0);
    if (ch3Raw == 0) {
      Serial.println("[!] SEM SINAL PPM DETECTADO");
      return;
    }

    Serial.print("LINK OK | ");
    for (byte ch = 1; ch <= channelAmount; ch++) {
      Serial.print("CH"); Serial.print(ch); Serial.print(": ");
      Serial.print(ppm.latestValidChannelValue(ch, 1500));
      Serial.print("  ");
    }
    Serial.println();
  }
}
