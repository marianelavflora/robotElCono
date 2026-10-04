// 2 displays de 7 segmentos crudos, multiplexados (ver docs/PINOUT.md).
// Los dos digitos muestran la misma expresion en espejo (son los "dos ojos"
// de Cono). Asume catodo comun + transistor NPN por digito - si los
// displays son de anodo comun, invertir la logica de segmentos/digitos.
#pragma once

#include <stdint.h>

enum Expresion {
  EXPR_NEUTRAL,     // "-" - en reposo
  EXPR_ABIERTO,     // "0" - sorpresa / grito
  EXPR_CERRADO,     // apagado - parpadeo
  EXPR_CONTENTO,    // saludo / chiste
};

class Cara {
 public:
  void begin();
  void expresion(Expresion e);
  void parpadear();      // cierra y vuelve a abrir los ojos, sin cambiar la expresion de fondo
  void tick();            // llamar seguido: refresca el multiplexado

 private:
  void refrescar_digito(uint8_t digito, uint8_t patron);

  Expresion _expresion = EXPR_NEUTRAL;
  uint8_t _digito_activo = 0;
  uint32_t _ultimo_frame_us = 0;

  bool _parpadeando = false;
  uint32_t _parpadeo_hasta = 0;
};
