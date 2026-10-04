#include <Arduino.h>
#include <Wire.h>
#include "pines.h"
#include "Bus.h"

static bool _iniciado = false;

void i2c_begin() {
  if (_iniciado) return;
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  _iniciado = true;
}
