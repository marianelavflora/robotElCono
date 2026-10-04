// GY-MAX9814. Por ahora solo lectura de nivel de sonido (util para calibrar
// y para test/troubleshooting); no dispara ningun evento todavia. El
// reconocimiento real de voz ("hola cono") es fase 2, ver docs/EVENTOS.md.
#pragma once

#include <stdint.h>

class Mic {
 public:
  void begin();
  uint16_t nivel();     // amplitud pico-a-pico en una ventana corta
};
