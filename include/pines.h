// Pines de Cono. Fuente de verdad: docs/PINOUT.md.
// No repetir estos numeros en ningun otro archivo.
#pragma once

// --- I2C: MPU6050 (0x69, AD0 a 3.3V) + DS3231 (0x68) ---
#define PIN_I2C_SDA    21
#define PIN_I2C_SCL    22

// --- ultrasonido #1 (frontal, dispara chiste) ---
#define PIN_SR04_1_TRIG  17
#define PIN_SR04_1_ECHO  35   // solo entrada. OJO: va con divisor 1k/2k

// --- ultrasonido #2 ---
#define PIN_SR04_2_TRIG  5
#define PIN_SR04_2_ECHO  34   // solo entrada. OJO: va con divisor 1k/2k

// --- mic GY-MAX9814 ---
#define PIN_MIC_OUT      36   // ADC1_CH0, solo entrada

// --- pulsador de saludo ---
#define PIN_BOTON        39   // solo entrada, necesita pull-up externo

// --- DFPlayer Mini (Serial2 con pines custom) ---
#define PIN_DFPLAYER_RX  27   // <- TX del DFPlayer
#define PIN_DFPLAYER_TX  26   // -> RX del DFPlayer

// --- displays de 7 segmentos (x2, multiplexados) ---
#define PIN_SEG_A   4
#define PIN_SEG_B   13
#define PIN_SEG_C   14
#define PIN_SEG_D   16
#define PIN_SEG_E   18
#define PIN_SEG_F   19
#define PIN_SEG_G   23
#define PIN_SEG_DP  25

#define PIN_DIGITO_1  32   // via transistor NPN
#define PIN_DIGITO_2  33   // via transistor NPN

// --- LED de estado (opcional) ---
#define PIN_LED_STATUS  2   // pin de strapping, cuidado si se agrega mas hardware
