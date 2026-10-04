#include "Eventos.h"

const char *nombre_evento(Evento e) {
  switch (e) {
    case EV_NINGUNO:  return "ninguno";
    case EV_SALUDO:   return "saludo";
    case EV_SACUDIDA: return "sacudida";
    case EV_CHISTE:   return "chiste";
    case EV_HORA_9:   return "hora_9";
    case EV_HORA_13:  return "hora_13";
    case EV_HORA_18:  return "hora_18";
    default:          return "?";
  }
}
