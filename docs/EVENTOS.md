# Eventos y reacciones de Cono

Igual que en Dou: cada fila acá es una entrada en la tabla de
`Comportamiento`. Si se edita esta tabla, es lo único que hay que tocar en
`lib/cono/Comportamiento.cpp` después.

## v1 (definido)

| Evento | Disparador | Reacción |
|:---:|:---:|:---:|
| `EV_SALUDO` | pulsador | saludo — reproduce un audio de saludo (banco `SALUDO`) |
| `EV_SACUDIDA` | MPU6050 detecta sacudida (misma lógica que Dou: cruces de umbral en ventana deslizante) | grita — banco `GRITO` |
| `EV_CHISTE` | HC-SR04 #1 detecta a alguien pasando en frente | cuenta un chiste — banco `CHISTES`, uno al azar por disparo |
| `EV_HORA_9` | DS3231 marca 9:00, una vez por día | "fah, un sueño" |
| `EV_HORA_13` | DS3231 marca 13:00, una vez por día | "A COMEEER" |
| `EV_HORA_18` | DS3231 marca 18:00, una vez por día | "GET ORTEEED" |
| — (idle) | sin eventos | parpadeo de los displays de 7 segmentos (ojos), sin sonido |

### Notas de implementación

- Los eventos por hora necesitan una guarda de "ya disparé hoy a esta hora"
  (comparar contra la fecha/hora del último disparo, no solo la hora:minuto)
  para no repetirse durante todo el minuto en que se cumple la condición.
- `EV_CHISTE` necesita cooldown (como el `GOLPE_COOLDOWN_MS` de Dou) para no
  disparar en ráfaga si alguien se queda parado cerca del sensor.
- Prioridad entre eventos concurrentes: a definir cuando haya más de un
  evento simultáneo real (por ejemplo sacudida + alguien pasando en frente al
  mismo tiempo). Por ahora, tentativo: sacudida > saludo > chiste > horarios
  (los horarios pueden esperar un ciclo de loop si hay algo más "vivo"
  pasando, ya que igual se disparan una sola vez en la ventana del minuto).

## Fase 2 (pendiente, no bloquea v1)

- **Reconocimiento real de voz** ("¡Hola, Cono!"): reemplazar/complementar
  el pulsador como disparador de `EV_SALUDO` con un wake-word engine sobre
  el GY-MAX9814 (ej. ESP-SR/WakeNet o modelo TinyML entrenado en Edge
  Impulse). Es un subproyecto en sí mismo, se aborda aparte.
- Uso del nivel de sonido ambiente del mic para algo más que el saludo
  (ej. reaccionar a silencio prolongado o volumen alto en la oficina) —
  todavía sin definir.
- Motores/ruedas: quedan sin cablear ni programar en v1 (Cono fijo en el
  escritorio). Eventual v2 móvil.

## Bancos de audio necesarios (a grabar/conseguir y cargar en la microSD)

- `SALUDO` — uno o varios saludos
- `GRITO` — grito al sacudirlo
- `CHISTES` — banco con varios chistes (cuantos más, menos se repite)
- audio único para "fah, un sueño"
- audio único para "A COMEEER"
- audio único para "GET ORTEEED"
