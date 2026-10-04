// MPU6050 a 0x69 (AD0 a 3.3V - el 0x68 lo ocupa el DS3231 en el mismo bus).
// Solo detecta sacudida; Cono no necesita "dar vuelta" como Dou.
#pragma once

#include <stdint.h>
#include "Eventos.h"

class Movimiento {
 public:
  bool begin();               // false si no aparece en 0x69
  bool hay_mpu() const { return _hay; }
  Evento leer();

  float magnitud_g() const { return _g; }   // |a|, ~1g en reposo

 private:
  void muestrear();

  bool _hay = false;
  float _g = 1.0f;

  uint8_t  _cruces = 0;
  bool     _sobre_umbral = false;
  uint32_t _ventana_desde = 0;
  uint32_t _ultima_sacudida = 0;
};
