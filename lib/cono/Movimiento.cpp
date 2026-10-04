#include <Arduino.h>
#include <Wire.h>
#include "ajustes.h"
#include "Bus.h"
#include "Movimiento.h"

#define MPU_ADDR         0x69   // AD0 a 3.3V (0x68 lo usa el DS3231)
#define REG_PWR_MGMT_1   0x6B
#define REG_ACCEL_CONFIG 0x1C
#define REG_ACCEL_XOUT_H 0x3B

// Rango +-16g. El default de +-2g satura con un golpe fuerte.
#define ACCEL_FS_16G     0x18
#define LSB_POR_G        2048.0f

static void mpu_escribir(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

bool Movimiento::begin() {
  i2c_begin();

  Wire.beginTransmission(MPU_ADDR);
  if (Wire.endTransmission() != 0) {
    Serial.println("cono: NO encuentro el MPU6050 en 0x69 - revisa AD0 y el cableado");
    _hay = false;
    return false;
  }

  mpu_escribir(REG_PWR_MGMT_1, 0x00);            // despertarlo
  mpu_escribir(REG_ACCEL_CONFIG, ACCEL_FS_16G);
  delay(100);

  _hay = true;
  Serial.println("cono: MPU6050 ok en 0x69 (+-16g)");
  return true;
}

void Movimiento::muestrear() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(REG_ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6);
  if (Wire.available() < 6) return;

  int16_t ax = (Wire.read() << 8) | Wire.read();
  int16_t ay = (Wire.read() << 8) | Wire.read();
  int16_t az = (Wire.read() << 8) | Wire.read();

  const float x = ax / LSB_POR_G;
  const float y = ay / LSB_POR_G;
  const float z = az / LSB_POR_G;

  _g = sqrtf(x * x + y * y + z * z);
}

Evento Movimiento::leer() {
  if (!_hay) return EV_NINGUNO;

  muestrear();
  const uint32_t ahora = millis();

  // Cuantos cruces del umbral dentro de una ventana deslizante. Un golpe
  // seco a la mesa da un cruce; sacudirlo de verdad da varios.
  if (ahora - _ventana_desde > SACUDIDA_VENTANA_MS) {
    _ventana_desde = ahora;
    _cruces = 0;
  }

  const bool sobre = (_g - 1.0f) > SACUDIDA_G;
  if (sobre && !_sobre_umbral) _cruces++;         // solo el flanco de subida
  _sobre_umbral = sobre;

  if (_cruces >= SACUDIDA_CRUCES &&
      ahora - _ultima_sacudida > SACUDIDA_COOLDOWN_MS) {
    _ultima_sacudida = ahora;
    _cruces = 0;
    return EV_SACUDIDA;
  }

  return EV_NINGUNO;
}
