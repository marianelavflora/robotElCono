#include <Arduino.h>
#include <RTClib.h>
#include "ajustes.h"
#include "Bus.h"
#include "Reloj.h"

static RTC_DS3231 _rtc;

bool Reloj::begin() {
  i2c_begin();

  if (!_rtc.begin()) {
    Serial.println("cono: NO encuentro el DS3231 - revisa el cableado");
    _hay = false;
    return false;
  }

  if (_rtc.lostPower()) {
    // Se quedo sin pila o es la primera vez: toma la hora de compilacion
    // como punto de partida. Ajustar a mano despues si hace falta precision.
    Serial.println("cono: DS3231 sin hora valida, seteo con hora de compilacion");
    _rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  _hay = true;
  Serial.println("cono: DS3231 ok en 0x68");
  return true;
}

// Compara la hora actual contra un evento horario puntual (HH:00), con
// tolerancia de minutos y guarda de "un disparo por dia".
static bool coincide(uint8_t hora_actual, uint8_t min_actual, uint8_t dia_actual,
                      uint8_t hora_objetivo, int8_t &dia_disparo) {
  if (hora_actual != hora_objetivo) return false;
  if (min_actual > HORA_TOLERANCIA_MIN) return false;
  if (dia_disparo == (int8_t)dia_actual) return false;   // ya disparo hoy

  dia_disparo = (int8_t)dia_actual;
  return true;
}

Evento Reloj::leer() {
  if (!_hay) return EV_NINGUNO;

  const DateTime ahora = _rtc.now();
  _ultima_hora = ahora.hour();
  _ultimo_minuto = ahora.minute();
  const uint8_t dia = ahora.day();

  if (coincide(_ultima_hora, _ultimo_minuto, dia, 9, _dia_disparo_9))
    return EV_HORA_9;
  if (coincide(_ultima_hora, _ultimo_minuto, dia, 13, _dia_disparo_13))
    return EV_HORA_13;
  if (coincide(_ultima_hora, _ultimo_minuto, dia, 18, _dia_disparo_18))
    return EV_HORA_18;

  return EV_NINGUNO;
}
