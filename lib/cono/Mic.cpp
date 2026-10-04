#include <Arduino.h>
#include "pines.h"
#include "Mic.h"

void Mic::begin() {
  pinMode(PIN_MIC_OUT, INPUT);
}

uint16_t Mic::nivel() {
  // Ventana corta de muestreo: la diferencia entre el pico maximo y minimo
  // es una medida simple de "cuanto ruido hay ahora".
  uint16_t maximo = 0, minimo = 4095;
  const uint32_t hasta = millis() + 20;

  while (millis() < hasta) {
    const uint16_t v = analogRead(PIN_MIC_OUT);
    if (v > maximo) maximo = v;
    if (v < minimo) minimo = v;
  }

  return maximo - minimo;
}
