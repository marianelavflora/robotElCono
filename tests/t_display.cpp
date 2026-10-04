// Test aislado de los 2 displays de 7 segmentos multiplexados.
// `pio run -e display -t upload -t monitor`
//
// Que ver: los displays van rotando entre las expresiones cada 1.5s, con un
// parpadeo entre cada una. Si se ve un digito mucho mas tenue que el otro,
// o "fantasmas" de un digito en el otro, revisar los transistores de
// seleccion y las resistencias de segmento (ver docs/PINOUT.md). Si la
// imagen sale invertida (segmentos prenden al reves), los displays son de
// anodo comun, no catodo comun - avisar para ajustar Cara.cpp.
#include <Arduino.h>
#include "Cara.h"

Cara cara;

void setup() {
  Serial.begin(115200);
  delay(200);
  cara.begin();
  Serial.println("t_display: listo");
}

void loop() {
  static const Expresion SECUENCIA[] = {
    EXPR_NEUTRAL, EXPR_ABIERTO, EXPR_CONTENTO, EXPR_CERRADO,
  };
  static uint8_t i = 0;
  static uint32_t proximo = 0;

  if (millis() > proximo) {
    proximo = millis() + 1500;
    cara.expresion(SECUENCIA[i]);
    Serial.printf("expresion %u\n", i);
    i = (i + 1) % 4;
  }

  cara.tick();
}
