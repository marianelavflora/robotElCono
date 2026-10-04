// HC-SR04 del sensor frontal. Detecta a alguien pasando en frente -> chiste.
// El segundo HC-SR04 del pinout queda cableado pero sin usar hasta que se
// defina que evento dispara (ver docs/EVENTOS.md, "fase 2").
#pragma once

#include <stdint.h>
#include "Eventos.h"

class Proximidad {
 public:
  void begin(uint8_t pin_trig, uint8_t pin_echo);
  float leer_cm();      // -1 si no hubo eco (fuera de rango)
  Evento leer();         // aplica umbral + cooldown -> EV_CHISTE

 private:
  uint8_t _trig = 0, _echo = 0;
  uint32_t _ultimo_disparo = 0;
};
