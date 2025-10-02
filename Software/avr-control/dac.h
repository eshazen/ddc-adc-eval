#include "i2c.h"
#include <stdint.h>

// registers on LT2631
#define DAC_WINPUT 0
#define DAC_UPDATE 1
#define DAC_WR_AND_UPDATE 3
#define DAC_PWR_DOWN 4
#define DAC_SEL_INT_REF 6
#define DAC_SEL_EXT_REF 7

uint8_t set_dac( uint16_t v);
