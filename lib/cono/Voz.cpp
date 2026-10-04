#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include "pines.h"
#include "Voz.h"

static DFRobotDFPlayerMini _df;

// ------------------------------------------------------------- las pistas
//
// Numero de archivo en la microSD (ej. PISTAS_CHISTES[0]=4 -> 0004.mp3).
// Son placeholders: acomodar a medida que se graban/consiguen los audios
// reales y se numeran los mp3 en la tarjeta.

static const uint16_t PISTAS_SALUDO[]  = {1, 2};
static const uint16_t PISTAS_GRITO[]   = {3};
static const uint16_t PISTAS_CHISTES[] = {4, 5, 6, 7, 8};
static const uint16_t PISTAS_HORA_9[]  = {9};
static const uint16_t PISTAS_HORA_13[] = {10};
static const uint16_t PISTAS_HORA_18[] = {11};

struct BancoPistas {
  const uint16_t *pistas;
  uint8_t n;
};

#define PISTAS(a) { a, (uint8_t)(sizeof(a) / sizeof((a)[0])) }

static const BancoPistas TABLA[BANCO_TOTAL] = {
  { nullptr, 0 },       // BANCO_NINGUNO
  PISTAS(PISTAS_SALUDO),
  PISTAS(PISTAS_GRITO),
  PISTAS(PISTAS_CHISTES),
  PISTAS(PISTAS_HORA_9),
  PISTAS(PISTAS_HORA_13),
  PISTAS(PISTAS_HORA_18),
};

const char *nombre_banco(Banco b) {
  switch (b) {
    case BANCO_NINGUNO:  return "ninguno";
    case BANCO_SALUDO:   return "saludo";
    case BANCO_GRITO:    return "grito";
    case BANCO_CHISTES:  return "chistes";
    case BANCO_HORA_9:   return "hora_9";
    case BANCO_HORA_13:  return "hora_13";
    case BANCO_HORA_18:  return "hora_18";
    default:             return "?";
  }
}

bool Voz::begin() {
  Serial2.begin(9600, SERIAL_8N1, PIN_DFPLAYER_RX, PIN_DFPLAYER_TX);

  if (!_df.begin(Serial2, /*isACK=*/true, /*doReset=*/true)) {
    Serial.println("cono: NO encuentro el DFPlayer Mini - revisa cableado/microSD");
    _hay = false;
    return false;
  }

  _df.volume(20);   // 0-30, arrancar moderado y ajustar en la mesa
  _hay = true;
  Serial.println("cono: DFPlayer Mini ok");
  return true;
}

void Voz::volumen(uint8_t v) {
  if (_hay) _df.volume(v);
}

void Voz::sonar(Banco b) {
  if (!_hay || b >= BANCO_TOTAL) return;

  const BancoPistas &banco = TABLA[b];
  if (banco.n == 0) return;

  uint8_t indice = random(banco.n);
  if (banco.n > 1 && indice == _ultimo[b]) indice = (indice + 1) % banco.n;
  _ultimo[b] = indice;

  _df.play(banco.pistas[indice]);
  _sonando = true;
}

void Voz::loop() {
  if (!_hay) return;

  if (_df.available()) {
    const uint8_t tipo = _df.readType();
    if (tipo == DFPlayerPlayFinished) _sonando = false;
  }
}
