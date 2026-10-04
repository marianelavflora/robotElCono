// Test aislado del HC-SR04 frontal (el del "chiste"). `pio run -e sr04 -t upload -t monitor`
//
// Que ver: la distancia en cm actualizandose. Al acercarte a menos de
// CHISTE_CM (ver include/ajustes.h) deberia imprimir "CHISTE!" (respetando
// el cooldown para no spamear).
#include <Arduino.h>
#include "pines.h"
#include "Proximidad.h"

Proximidad sensor;

void setup() {
  Serial.begin(115200);
  delay(200);
  sensor.begin(PIN_SR04_1_TRIG, PIN_SR04_1_ECHO);
  Serial.println("t_sr04: listo");
}

void loop() {
  const float cm = sensor.leer_cm();
  Serial.printf("distancia: %.1f cm\n", cm);

  const Evento e = sensor.leer();
  if (e == EV_CHISTE) Serial.println("CHISTE!");

  delay(150);
}
