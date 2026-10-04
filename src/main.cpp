// cono - firmware completo.  `pio run -e cono -t upload -t monitor`
//
// Este archivo solo cablea los modulos y decide la prioridad entre eventos.
// Toda la logica vive en lib/cono/. Los umbrales, en include/ajustes.h.
#include <Arduino.h>

#include "pines.h"
#include "Movimiento.h"
#include "Proximidad.h"
#include "Boton.h"
#include "Reloj.h"
#include "Voz.h"
#include "Cara.h"
#include "Comportamiento.h"

Movimiento movimiento;
Proximidad proximidad_chiste;
Boton boton;
Reloj reloj;
Voz voz;
Cara cara;
Comportamiento cerebro(cara, voz);

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("cono: boot ok");

  cara.begin();
  boton.begin();
  proximidad_chiste.begin(PIN_SR04_1_TRIG, PIN_SR04_1_ECHO);
  movimiento.begin();
  reloj.begin();
  voz.begin();
  cerebro.begin();

  Serial.println("cono: listo. apreta el boton, sacudilo, o pasale por adelante.");
}

void loop() {
  // Prioridad: sacudida > saludo (boton) > chiste (proximidad) > horarios.
  // A diferencia de Dou, el DFPlayer decodifica el audio el solo, asi que
  // no hace falta frenar los sensores mientras suena algo.
  Evento e = movimiento.leer();
  if (e == EV_NINGUNO) e = boton.leer();
  if (e == EV_NINGUNO) e = proximidad_chiste.leer();
  if (e == EV_NINGUNO) e = reloj.leer();

  cerebro.procesar(e);
  cerebro.tick();                    // cara.tick() + voz.loop() + idle
}
