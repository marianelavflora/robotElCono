// DS3231 (0x68) - dispara EV_HORA_9 / EV_HORA_13 / EV_HORA_18 una vez por
// dia cada uno. Comparte bus I2C con el MPU6050 (que esta en 0x69).
#pragma once

#include <stdint.h>
#include "Eventos.h"

class Reloj {
 public:
  bool begin();          // false si no encuentra el DS3231
  Evento leer();

  uint8_t hora() const { return _ultima_hora; }
  uint8_t minuto() const { return _ultimo_minuto; }

 private:
  bool  _hay = false;
  uint8_t _ultima_hora = 0, _ultimo_minuto = 0;

  // ultimo dia (1-31) en que disparo cada evento, para no repetir en la
  // ventana de tolerancia del mismo dia.
  int8_t _dia_disparo_9  = -1;
  int8_t _dia_disparo_13 = -1;
  int8_t _dia_disparo_18 = -1;
};
