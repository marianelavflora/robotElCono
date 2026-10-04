#include <Arduino.h>
#include "ajustes.h"
#include "Comportamiento.h"

// ------------------------------------------------------- la tabla (docs/EVENTOS.md)
//
// Una entrada por evento. Si se edita docs/EVENTOS.md, esto es lo unico que
// hay que tocar aca.

static const Reaccion TABLA[EV_TOTAL] = {
  { EXPR_NEUTRAL,  BANCO_NINGUNO },    // EV_NINGUNO
  { EXPR_CONTENTO, BANCO_SALUDO  },    // EV_SALUDO
  { EXPR_ABIERTO,  BANCO_GRITO   },    // EV_SACUDIDA
  { EXPR_CONTENTO, BANCO_CHISTES },    // EV_CHISTE
  { EXPR_NEUTRAL,  BANCO_HORA_9  },    // EV_HORA_9
  { EXPR_CONTENTO, BANCO_HORA_13 },    // EV_HORA_13
  { EXPR_CONTENTO, BANCO_HORA_18 },    // EV_HORA_18
};

void Comportamiento::begin() {
  randomSeed(esp_random());
  _cara.expresion(EXPR_NEUTRAL);
  programar_idle();
}

void Comportamiento::programar_idle() {
  _proximo_idle = millis() + random(IDLE_MIN_MS, IDLE_MAX_MS);
}

void Comportamiento::procesar(Evento e) {
  if (e == EV_NINGUNO || e >= EV_TOTAL) return;

  const Reaccion &r = TABLA[e];

  Serial.printf("%-10s -> cara %d + %s[]\n", nombre_evento(e), r.expresion,
                nombre_banco(r.banco));

  _cara.expresion(r.expresion);
  _voz.sonar(r.banco);
  _hold_hasta = millis() + HOLD_MS;
  programar_idle();          // el idle se corre: acaba de pasar algo
}

void Comportamiento::tick() {
  const uint32_t ahora = millis();

  // Se mantiene la expresion hasta que pasa el hold; si sigue sonando el
  // audio (el DFPlayer puede tardar mas que HOLD_MS en un chiste largo),
  // que la cara lo acompane.
  if (_hold_hasta && ahora >= _hold_hasta && !_voz.sonando()) {
    _hold_hasta = 0;
    _cara.expresion(EXPR_NEUTRAL);
  }

  // Idle: parpadea solo para no sentirse apagado. Sin sonido.
  if (!_hold_hasta && ahora >= _proximo_idle) {
    _cara.parpadear();
    programar_idle();
  }

  _cara.tick();
  _voz.loop();
}
