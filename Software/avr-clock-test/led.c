
#include <stddef.h>
#include <avr/io.h>
#include "i2c.h"
#include "led.h"

void init_led() {
  // just set default values for now
  set_dac( 0);
  set_mux( 0, 0);
}

void set_dac( uint16_t v) {
  i2c_wdata[0] = 0x30;		/* command to update DAC and enable */
  i2c_wdata[1] = v>>4;		/* upper 8 bits */
  i2c_wdata[2] = v<<4;		/* lower 4 bits */
  rc = i2c_io( DAC_I2C_ADR, NULL, 0, i2c_wdata, 3, NULL, 0);
  chk_err( rc);
}

void set_mux( uint8_t en, uint8_t ch) {
  i2c_wdata[0] = ((en & 1) << 3) | (ch & 7);
  rc = i2c_io( MUX_I2C_ADR, NULL, 0, i2c_wdata, 1, NULL, 0);
  chk_err( rc);
}

