# Cono

Robot de oficina cuya única finalidad es subir la moral y romper las bolas.
Hermano de [Dou](https://github.com/memocayar/hackware-antitamagotchi) (robot
anti-tamagotchi hecho en un hackathon en Buenos Aires), del cual toma
prestada la arquitectura de software: sensores tontos que reportan un
`Evento`, un "cerebro" que decide la reacción según una tabla, y actuadores
tontos que solo ejecutan lo que se les ordena.

A diferencia de Dou, Cono vive fijo en un escritorio (no se desplaza, al
menos en esta versión) y está pensado para convivir con varias personas en
una oficina en vez de reaccionar a que una sola persona lo manosee.

## Estado del proyecto

En diseño / armado de hardware. Todavía no hay firmware funcional — este
repo por ahora tiene la documentación de arquitectura y el pinout para poder
empezar a cablear.

## Hardware

| Componente | Rol |
|:---:|:---:|
| ESP32 DevKit v1 (WROOM-32) | microcontrolador principal |
| MPU6050 (IMU, I2C) | detecta que lo sacuden |
| DS3231 (RTC, I2C) | hora real para los eventos programados (9am/13hs/18hs) |
| 2× HC-SR04 (ultrasonido) | detecta gente pasando cerca |
| GY-MAX9814 (mic con AGC) | nivel de sonido ambiente (reservado para fase 2: wake-word real) |
| Pulsador | saludo manual |
| DFPlayer Mini + microSD | reproducción de audio (bancos de sonidos/chistes), con ampli integrado para el parlante |
| 2× display 7 segmentos (crudos, multiplexados) | "cara" de Cono — parpadeo / expresiones simples |

Detalle de pines y notas de cableado en [`docs/PINOUT.md`](docs/PINOUT.md).

## Arquitectura de software

Igual que Dou: `sensor → Evento → tabla de reacción (Comportamiento) → actuador`.

- `include/pines.h` — única fuente de verdad de GPIO.
- `include/ajustes.h` — todos los umbrales/tiempos de calibración.
- `lib/cono/` — un módulo por componente de hardware (clase con `begin()` +
  método de lectura o de acción), más `Comportamiento` (el cerebro) y
  `Eventos.h` (el enum compartido).
- `src/main.cpp` — solo cablea los módulos y arbitra prioridad entre eventos
  en `loop()`. Nada de lógica de negocio ahí.

Detalle de los eventos y las reacciones planeadas, en
[`docs/EVENTOS.md`](docs/EVENTOS.md).

## Diferencias clave respecto a Dou

- Sin OLED ni servos de cejas → la expresividad facial se resuelve con 2
  displays de 7 segmentos multiplexados en vez de gráficos.
- Sin ampli I2S → audio resuelto con DFPlayer Mini (MP3 + ampli integrado,
  controlado por UART) en vez de decodificar MP3 en el propio ESP32.
- Sin reloj propio en Dou → Cono suma un DS3231 para los eventos horarios
  fijos (9am / 13hs / 18hs).
- Motores/ruedas/casters están en el inventario pero **no se usan en esta
  versión** — Cono v1 queda fijo en el escritorio. Quedan reservados para
  una eventual v2 móvil.

## Build

Proyecto PlatformIO, target `esp32dev` / framework Arduino. Ver
`platformio.ini` para los environments (firmware completo + uno de test por
módulo, mismo esquema que Dou).

```
pio run -e cono -t upload -t monitor
```

(placeholder — todavía no hay código fuente que compile)
