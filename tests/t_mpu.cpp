// Test aislado del MPU6050. `pio run -e mpu -t upload -t monitor`
//
// Que ver: al arrancar, "MPU6050 ok en 0x69". Sacudilo con fuerza y deberia
// imprimir "SACUDIDA!". Si no aparece "ok", revisar AD0 a 3.3V (tiene que
// estar en 0x69, no en 0x68 - ese lo ocupa el DS3231) y el cableado I2C.
#include <Arduino.h>
#include "Movimiento.h"

Movimiento movimiento;

void setup() {
  Serial.begin(115200);
  delay(200);
  movimiento.begin();
}

void loop() {
  const Evento e = movimiento.leer();
  if (e == EV_SACUDIDA) Serial.println("SACUDIDA!");

  static uint32_t ultimo_print = 0;
  if (millis() - ultimo_print > 300) {
    ultimo_print = millis();
    Serial.printf("|a| = %.2f g\n", movimiento.magnitud_g());
  }
}
