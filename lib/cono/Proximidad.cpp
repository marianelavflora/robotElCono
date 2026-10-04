#include <Arduino.h>
#include "ajustes.h"
#include "Proximidad.h"

void Proximidad::begin(uint8_t pin_trig, uint8_t pin_echo) {
  _trig = pin_trig;
  _echo = pin_echo;
  pinMode(_trig, OUTPUT);
  pinMode(_echo, INPUT);
  digitalWrite(_trig, LOW);
}

float Proximidad::leer_cm() {
  digitalWrite(_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);

  // timeout ~25ms = un poco mas de 4m de alcance. Si no hay eco, pulseIn
  // devuelve 0 y lo tomamos como "nada cerca".
  const uint32_t us = pulseIn(_echo, HIGH, 25000UL);
  if (us == 0) return -1.0f;

  return us / 58.0f;   // formula estandar del HC-SR04
}

Evento Proximidad::leer() {
  const float cm = leer_cm();
  if (cm < 0 || cm > CHISTE_CM) return EV_NINGUNO;

  const uint32_t ahora = millis();
  if (ahora - _ultimo_disparo < CHISTE_COOLDOWN_MS) return EV_NINGUNO;

  _ultimo_disparo = ahora;
  return EV_CHISTE;
}
