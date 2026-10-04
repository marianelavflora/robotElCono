// Test aislado del DFPlayer Mini + parlante. `pio run -e dfplayer -t upload -t monitor`
//
// Que ver: "DFPlayer Mini ok" al arrancar, y despues reproduce la pista 1
// cada 5 segundos. Si no dice "ok", revisar: microSD puesta y con mp3s
// numerados (0001.mp3, ...), RX/TX no cruzados (ver docs/PINOUT.md - el TX
// del DFPlayer va al RX del ESP32 y viceversa), y alimentacion a 5V.
#include <Arduino.h>
#include "Voz.h"

Voz voz;

void setup() {
  Serial.begin(115200);
  delay(200);
  voz.begin();
}

void loop() {
  static uint32_t proximo = 0;
  if (millis() > proximo) {
    proximo = millis() + 5000;
    Serial.println("reproduciendo banco SALUDO...");
    voz.sonar(BANCO_SALUDO);
  }
  voz.loop();
}
