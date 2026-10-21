/*
 * Borboleta Biônica - Teste do Receptor ELRS (CRSF)
 * ------------------------------------------------------------
 * Sketch isolado para validar a recepção do receptor ELRS antes
 * de rodar o firmware principal. Lê o link via protocolo nativo
 * CRSF (porta serial de hardware) e imprime os 8 primeiros canais
 * e o status do link no Monitor Serial.
 *
 * Ligações (Arduino Pro Micro):
 *   Receptor ELRS TX -> Arduino RX1 (pino 0)
 *   Receptor ELRS RX -> Arduino TX1 (pino 1)   [opcional, telemetria]
 *   Atenção: receptores ELRS operam em 3.3V. Confira a
 *   compatibilidade de nível lógico do seu Pro Micro (3.3V/8MHz
 *   ou 5V/16MHz) antes de ligar.
 *
 * Biblioteca necessária: AlfredoCRSF
 *   https://github.com/AlfredoSystems/AlfredoCRSF
 * ------------------------------------------------------------
 */

#include <AlfredoCRSF.h>

AlfredoCRSF crsf;

const byte channelAmount = 8;
unsigned long lastPrintTime = 0;
const int printInterval = 200; // ms

void setup() {
  Serial.begin(115200);
  Serial1.begin(CRSF_BAUDRATE);
  crsf.begin(Serial1);
  Serial.println("--- TESTE DO RECEPTOR ELRS (CRSF) ---");
}

void loop() {
  crsf.update();

  if (millis() - lastPrintTime >= printInterval) {
    lastPrintTime = millis();

    if (!crsf.isLinkUp()) {
      Serial.println("[!] SEM SINAL DO RECEPTOR (link down / failsafe)");
      return;
    }

    Serial.print("LINK OK | ");
    for (byte ch = 1; ch <= channelAmount; ch++) {
      Serial.print("CH"); Serial.print(ch); Serial.print(": ");
      Serial.print(crsf.getChannel(ch));
      Serial.print("  ");
    }
    Serial.println();
  }
}
