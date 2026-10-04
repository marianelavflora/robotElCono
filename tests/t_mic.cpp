// Test aislado del GY-MAX9814. `pio run -e mic -t upload -t monitor`
//
// Que ver: un numero que sube con ruido ambiente y baja en silencio. Sirve
// para calibrar MIC_UMBRAL_RUIDO (include/ajustes.h) para cuando se use en
// fase 2. Probar hablando/aplaudiendo cerca del mic y ver cuanto sube.
#include <Arduino.h>
#include "Mic.h"

Mic mic;

void setup() {
  Serial.begin(115200);
  delay(200);
  mic.begin();
  Serial.println("t_mic: listo");
}

void loop() {
  const uint16_t nivel = mic.nivel();
  Serial.printf("nivel: %u\n", nivel);
  delay(100);
}
