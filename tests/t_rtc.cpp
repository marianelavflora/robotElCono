// Test aislado del DS3231. `pio run -e rtc -t upload -t monitor`
//
// Que ver: la hora actual, una vez por segundo. Si dice "sin hora valida,
// seteo con hora de compilacion" es porque la pila del modulo esta agotada
// o es la primera vez que se lo alimenta - revisar la pila CR2032.
#include <Arduino.h>
#include "Reloj.h"

Reloj reloj;

void setup() {
  Serial.begin(115200);
  delay(200);
  reloj.begin();
}

void loop() {
  const Evento e = reloj.leer();
  Serial.printf("hora: %02u:%02u  ", reloj.hora(), reloj.minuto());
  Serial.println(nombre_evento(e));
  delay(1000);
}
