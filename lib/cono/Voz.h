// DFPlayer Mini por Serial2. Cada banco es una lista de numeros de pista
// (archivos en la microSD, ej. 0001.mp3, 0002.mp3, ...) y se elige uno al
// azar por disparo para no repetir siempre lo mismo.
//
// A diferencia de Dou (que decodificaba MP3 en el propio ESP32 via I2S), el
// DFPlayer decodifica y amplifica solo: el HC-SR04 no le corta el audio, asi
// que Comportamiento no necesita frenar sensores mientras suena algo.
#pragma once

#include <stdint.h>

enum Banco {
  BANCO_NINGUNO = 0,
  BANCO_SALUDO,     // pulsador / "hola cono" (fase 2)
  BANCO_GRITO,      // sacudida
  BANCO_CHISTES,    // alguien pasa en frente
  BANCO_HORA_9,     // "fah, un suenio"
  BANCO_HORA_13,    // "A COMEEER"
  BANCO_HORA_18,    // "GET ORTEEED"
  BANCO_TOTAL
};

const char *nombre_banco(Banco b);

class Voz {
 public:
  bool begin();               // arranca Serial2 y el DFPlayer
  void sonar(Banco b);        // corta lo que este sonando y arranca otro
  void loop();                // hay que llamarla seguido: procesa mensajes del DFPlayer
  bool sonando() const { return _sonando; }

  void volumen(uint8_t v);    // 0-30

 private:
  bool _hay = false;
  bool _sonando = false;
  int8_t _ultimo[BANCO_TOTAL] = {0};   // para no repetir la misma pista
};
