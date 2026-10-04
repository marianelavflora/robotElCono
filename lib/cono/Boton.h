// Pulsador de saludo. GPIO39 es solo-entrada y no tiene pull-up interno:
// necesita resistencia pull-up externa (ver docs/PINOUT.md). El boton cierra
// a GND, entonces en reposo lee HIGH y presionado lee LOW.
#pragma once

#include "Eventos.h"

class Boton {
 public:
  void begin();
  Evento leer();      // EV_SALUDO en el flanco de bajada, con antirrebote

 private:
  bool _anterior = true;   // true = suelto (HIGH)
  uint32_t _ultimo_cambio = 0;
};
