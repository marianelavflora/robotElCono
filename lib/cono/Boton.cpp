#include <Arduino.h>
#include "ajustes.h"
#include "pines.h"
#include "Boton.h"

void Boton::begin() {
  pinMode(PIN_BOTON, INPUT);   // pull-up externo, ver docs/PINOUT.md
}

Evento Boton::leer() {
  const bool actual = digitalRead(PIN_BOTON) == HIGH;
  const uint32_t ahora = millis();

  if (actual != _anterior && ahora - _ultimo_cambio > BOTON_DEBOUNCE_MS) {
    _ultimo_cambio = ahora;
    const bool flanco_bajada = _anterior && !actual;
    _anterior = actual;
    if (flanco_bajada) return EV_SALUDO;
  }

  return EV_NINGUNO;
}
