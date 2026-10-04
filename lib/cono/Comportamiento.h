// El cerebro. Tabla data-driven Evento -> Reaccion (ver docs/EVENTOS.md).
// A diferencia de Dou, aca la variedad de audio la resuelve Voz eligiendo
// pista al azar dentro del banco, asi que cada evento tiene una unica
// reaccion (no hace falta elegir entre "filas" a nivel Comportamiento).
#pragma once

#include "Eventos.h"
#include "Reaccion.h"
#include "Cara.h"
#include "Voz.h"

class Comportamiento {
 public:
  Comportamiento(Cara &cara, Voz &voz) : _cara(cara), _voz(voz) {}

  void begin();
  void procesar(Evento e);
  void tick();       // cara.tick() + voz.loop() + parpadeo idle

 private:
  void programar_idle();

  Cara &_cara;
  Voz &_voz;

  uint32_t _hold_hasta = 0;
  uint32_t _proximo_idle = 0;
};
