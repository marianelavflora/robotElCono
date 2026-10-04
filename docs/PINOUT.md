# Pinout de Cono (ESP32 DevKit v1 / WROOM-32)

Fuente de verdad para el cableado. Estos mismos números van en
`include/pines.h` — si cambian acá, cambian ahí, no al revés (nunca hardcodear
un GPIO distinto directo en un `.cpp`).

## Pines reservados, no tocar

| GPIO | Motivo |
|:---:|:---:|
| 0 | strapping (boot mode) — debe estar alto al bootear |
| 1 (TX0) / 3 (RX0) | Serial USB, se usa para debug por monitor serie |
| 2 | strapping — debe estar bajo/flotante al bootear |
| 12 (MTDI) | strapping — selecciona voltaje de flash, si queda alto al bootear puede tirar el chip |
| 15 | strapping — debe estar bajo al bootear para que no salga log de boot por UART |
| 6-11 | conectados a la flash SPI interna, no están ni disponibles en el DevKit |

## Asignación

### I2C (bus compartido: DS3231 + MPU6050)

| Señal | GPIO |
|:---:|:---:|
| SDA | 21 |
| SCL | 22 |

⚠️ **Conflicto de direcciones I2C**: el DS3231 usa la dirección fija `0x68`,
que es la misma que trae el MPU6050 por defecto. Solución: conectar el pin
**AD0 del MPU6050 a 3.3V** para correrlo a `0x69`. Sin este cambio los dos
dispositivos chocan en el bus y ninguno responde bien.

### HC-SR04 (×2)

Ambos con divisor de tensión 1kΩ/2kΩ en ECHO (el sensor trabaja a 5V, el
ESP32 no tolera 5V en sus entradas).

| Sensor | TRIG | ECHO |
|:---:|:---:|:---:|
| #1 (frontal — dispara "chiste") | 17 | 35 *(input-only)* |
| #2 (secundario) | 5 | 34 *(input-only)* |

### MPU6050

Comparte el bus I2C (ver arriba). `AD0 → 3.3V` (dirección `0x69`).

### DS3231 (RTC)

Comparte el bus I2C (ver arriba). Dirección `0x68`. Verificar que traiga la
pila CR2032 colocada.

### GY-MAX9814 (mic)

| Señal | GPIO |
|:---:|:---:|
| OUT (analógico) | 36 *(ADC1_CH0, input-only)* |

`GAIN` y `A/R` del módulo se pueden dejar flotando (ganancia media, ataque/
release por defecto) para la primera prueba.

### Pulsador (saludo)

| Señal | GPIO |
|:---:|:---:|
| Señal | 39 *(input-only — no tiene pull-up interno)* |

Necesita resistencia pull-up externa (~10kΓÇë a 3.3V) entre la señal y VCC;
el pulsador cierra a GND. Hay resistencias sueltas en el kit para esto.

### DFPlayer Mini (audio)

UART por software vía `Serial2` con pines custom (no usar los pines por
defecto de `Serial2` para no pisar otras asignaciones).

| Señal DFPlayer | GPIO ESP32 |
|:---:|:---:|
| TX (del DFPlayer) | 27 *(RX2 del ESP32)* |
| RX (del DFPlayer) | 26 *(TX2 del ESP32)* |
| VCC | 5V |
| GND | GND |
| SPK_1 / SPK_2 | directo a los dos cables del parlante |

El DFPlayer necesita la microSD con los mp3 cargados (nombrar los archivos
según la convención de la librería que se use, típicamente `0001.mp3`,
`0002.mp3`, ... en la raíz o en carpeta `/mp3`).

### Displays de 7 segmentos (×2, multiplexados)

Displays crudos sin driver — se multiplexan: los segmentos iguales de ambos
dígitos van atados al mismo pin, y un transistor NPN por dígito (ej.
2N2222, con resistencia de base ~1kΩ) habilita un dígito a la vez,
alternando rápido para que el ojo los vea prendidos juntos.

| Segmento | GPIO |
|:---:|:---:|
| A | 4 |
| B | 13 |
| C | 14 |
| D | 16 |
| E | 18 |
| F | 19 |
| G | 23 |
| DP | 25 |

| Selección de dígito | GPIO | Vía |
|:---:|:---:|:---:|
| Dígito 1 | 32 | transistor NPN (base con resistencia) |
| Dígito 2 | 33 | transistor NPN (base con resistencia) |

Cada segmento lleva su resistencia limitadora de corriente (las del kit
sirven, calcular según el color/Vf de los LEDs de los displays — con 3.3V y
LEDs rojos, algo en el orden de 220-330Ω por segmento es un buen punto de
partida, ajustar a ojo según brillo).

### LED de estado (opcional)

| Señal | GPIO |
|:---:|:---:|
| LED status | 2 *(compartido con el LED onboard de muchos DevKit; cuidado, es pin de strapping — no debería tener nada más tirando de él al bootear)* |

## Resumen de rieles de alimentación

- **3.3V**: ESP32, MPU6050, DS3231, GY-MAX9814, lógica de los displays.
- **5V**: DFPlayer Mini, parlante.
- Confirmar que la fuente entregue corriente suficiente para el parlante a
  volumen alto + todo lo demás simultáneo — si hay parpadeos raros del
  ESP32 al subir el volumen, es la fuente quedándose corta, no un bug de
  software.

## Pendiente de confirmar en la mesa de trabajo

- Verificar en la placa DS3231 si además trae EEPROM AT24C32 (dirección
  `0x57`, no choca con nada, no requiere acción).
- Confirmar polaridad (cátodo común / ánodo común) de los displays de 7
  segmentos antes de cablear los transistores — cambia si el multiplexado
  va por transistor NPN a GND o PNP a VCC.
