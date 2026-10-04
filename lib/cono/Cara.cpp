#include <Arduino.h>
#include "pines.h"
#include "ajustes.h"
#include "Cara.h"

// bit0=a bit1=b bit2=c bit3=d bit4=e bit5=f bit6=g bit7=dp
static const uint8_t PATRON_NEUTRAL  = 0b01000000;   // "-"
static const uint8_t PATRON_ABIERTO  = 0b00111111;   // "0"
static const uint8_t PATRON_CERRADO  = 0b00000000;   // apagado
static const uint8_t PATRON_CONTENTO = 0b01001111;   // forma de "3", sonrisa aprox.
                                                       // (ajustar a gusto viendolo prendido)

static const uint8_t PINES_SEG[8] = {
  PIN_SEG_A, PIN_SEG_B, PIN_SEG_C, PIN_SEG_D,
  PIN_SEG_E, PIN_SEG_F, PIN_SEG_G, PIN_SEG_DP,
};

static const uint8_t PINES_DIGITO[2] = { PIN_DIGITO_1, PIN_DIGITO_2 };

static uint8_t patron_de(Expresion e) {
  switch (e) {
    case EXPR_NEUTRAL:  return PATRON_NEUTRAL;
    case EXPR_ABIERTO:  return PATRON_ABIERTO;
    case EXPR_CERRADO:  return PATRON_CERRADO;
    case EXPR_CONTENTO: return PATRON_CONTENTO;
    default:             return PATRON_NEUTRAL;
  }
}

void Cara::begin() {
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(PINES_SEG[i], OUTPUT);
    digitalWrite(PINES_SEG[i], LOW);
  }
  for (uint8_t i = 0; i < 2; i++) {
    pinMode(PINES_DIGITO[i], OUTPUT);
    digitalWrite(PINES_DIGITO[i], LOW);
  }
}

void Cara::expresion(Expresion e) {
  _expresion = e;
  _parpadeando = false;
}

void Cara::parpadear() {
  _parpadeando = true;
  _parpadeo_hasta = millis() + 150;   // ojos cerrados un toque, como un tilde
}

void Cara::refrescar_digito(uint8_t digito, uint8_t patron) {
  // apaga los dos antes de prender el que corresponde, para no ensuciar
  // el digito anterior mientras cambian los segmentos (fantasma/ghosting).
  digitalWrite(PINES_DIGITO[0], LOW);
  digitalWrite(PINES_DIGITO[1], LOW);

  for (uint8_t i = 0; i < 8; i++)
    digitalWrite(PINES_SEG[i], (patron >> i) & 1 ? HIGH : LOW);

  digitalWrite(PINES_DIGITO[digito], HIGH);
}

void Cara::tick() {
  const uint32_t ahora_us = micros();
  if (ahora_us - _ultimo_frame_us < MUX_FRAME_US) return;
  _ultimo_frame_us = ahora_us;

  if (_parpadeando && millis() >= _parpadeo_hasta) _parpadeando = false;

  const uint8_t patron = _parpadeando ? PATRON_CERRADO : patron_de(_expresion);

  refrescar_digito(_digito_activo, patron);
  _digito_activo = 1 - _digito_activo;
}
