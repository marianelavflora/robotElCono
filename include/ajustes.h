// Todos los numeros que hay que calibrar con el hardware en la mano.
// Si estas tocando un umbral y no esta aca, esta mal puesto.
#pragma once

// ---------------------------------------------------------------- generales

// Cuanto dura una reaccion (cara + audio) antes de volver a neutral.
static const uint32_t HOLD_MS = 800;

// -------------------------------------------------------------- movimiento

// Sacudida: cuantas veces cruza el umbral dentro de la ventana.
// Puntos de partida iguales a Dou, recalibrar con el MPU6050 puesto en Cono.
static const float    SACUDIDA_G          = 2.0f;   // sobre |a| - 1g
static const uint32_t SACUDIDA_VENTANA_MS = 400;
static const uint8_t  SACUDIDA_CRUCES     = 4;
static const uint32_t SACUDIDA_COOLDOWN_MS = 1500;

// --------------------------------------------------------------- distancia

// Chiste: alguien pasando en frente del HC-SR04 #1.
static const float    CHISTE_CM           = 60.0f;  // recalibrar segun ubicacion del escritorio
static const uint32_t CHISTE_COOLDOWN_MS  = 20000;  // no contar chistes en rafaga

// -------------------------------------------------------------- pulsador

static const uint32_t BOTON_DEBOUNCE_MS   = 50;

// ------------------------------------------------------------------- mic

// Nivel de sonido considerado "ruido fuerte" (fase 2 / saludo por sonido).
// Placeholder: calibrar con el GY-MAX9814 en la mesa antes de usar.
static const uint16_t MIC_UMBRAL_RUIDO    = 2500;

// -------------------------------------------------------------------- idle

// Parpadeo espontaneo de los displays de 7 segmentos, para que no se sienta
// apagado entre interacciones.
static const uint32_t IDLE_MIN_MS = 3000;
static const uint32_t IDLE_MAX_MS = 6000;

// Multiplexado de los displays: cada cuanto se alterna el digito activo.
// Muy lento y se ve titilar, muy rapido y no hace falta mas.
static const uint32_t MUX_FRAME_US = 4000;

// ------------------------------------------------------------------- reloj

// Ventana de tolerancia para disparar un evento horario (para no perderlo
// si el loop justo esta ocupado el segundo exacto).
static const uint8_t HORA_TOLERANCIA_MIN = 1;
