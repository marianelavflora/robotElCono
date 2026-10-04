// Test aislado del pulsador. `pio run -e boton -t upload -t monitor`
//
// Que ver: "SALUDO!" cada vez que se aprieta y suelta el boton. Si tira
// varios seguidos con un solo apriete, es rebote -> revisar la resistencia
// pull-up externa en GPIO39 (ver docs/PINOUT.md) o subir BOTON_DEBOUNCE_MS.
#include <Arduino.h>
#include "pines.h"
#include "Boton.h"

Boton boton;

void setup() {
  Serial.begin(115200);
  delay(200);
  boton.begin();
  Serial.println("t_boton: listo, apreta el boton");
}

void loop() {
  const Evento e = boton.leer();
  if (e == EV_SALUDO) Serial.println("SALUDO!");
}
