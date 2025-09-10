#include <avr/io.h>
#include <stdlib.h>

#include "dac.h"

//
// set value on LTC2631 and update
//
uint8_t set_dac( uint16_t v) {
  uint8_t rc;
  // 12-bit write:
  // 1st byte:  c3 c2 c1 c0 x x x x
  // 2nd byte:  d11..d4
  // 3rd byte:  d3 d2 d1 d0 x x x x
  i2c_adr = DAC_WR_AND_UPDATE;
  i2c_wdata[0] = v >> 4;
  i2c_wdata[1] = v << 4;
  rc = i2c_io( DAC_I2C_ADR, &i2c_adr, 1, i2c_wdata, 2, NULL, 0);
  return rc;
}
