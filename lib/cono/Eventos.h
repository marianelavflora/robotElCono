// Lo unico que los sensores le cuentan al cerebro.
#pragma once

enum Evento {
  EV_NINGUNO = 0,
  EV_SALUDO,       // pulsador (fase 2: reconocimiento de voz real)
  EV_SACUDIDA,     // MPU6050: varios cruces de umbral en ventana
  EV_CHISTE,       // HC-SR04 #1: alguien pasando en frente
  EV_HORA_9,       // DS3231 marca 9:00
  EV_HORA_13,      // DS3231 marca 13:00
  EV_HORA_18,      // DS3231 marca 18:00
  EV_TOTAL
};

const char *nombre_evento(Evento e);
