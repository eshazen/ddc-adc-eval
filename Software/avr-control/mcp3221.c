
#include "mcp3221.h"

uint16_t read_3221() {
  rc = i2c_io( ADC_I2C_ADR, NULL, 0, NULL, 0, i2c_rdata, 2);
  chk_err( rc);
  return (i2c_rdata[0] << 8) | i2c_rdata[1];
}
