#include <stdint.h>
#include "ddc.h"
#include <avr/io.h>

// initialize pin direction and initial state
void ddc_init() {
  // set DCLK, DIN, BV as outputs
  DCLK_DDR |= _BV(DCLK_BIT) | _BV(DIN_BIT) | _BV(DXMIT_BIT);

  // set nDVALID as input
  DVALID_DDR &= ~_BV(DVALID_BIT);

  // set nDXMIT = 1, DCLK = 0, DIN = 0
  DCLK_PORT |= _BV(DXMIT_BIT);
  DCLK_PORT &= ~_BV(DCLK_BIT);
  DCLK_PORT &= ~_BV(DIN_BIT);

  // set range as outputs, set to 0
  RANGE_DDR |= RANGE_MASK;
  ddc_range(0);

  LED_DDR |= _BV(LED_BIT);	/* set LED direction */
  LED_PORT &= ~(_BV(LED_BIT));
}

// read DDC 20 bit data (don't wait for DVALID)
uint32_t read_ddc() {
  uint32_t v = 0;
  uint32_t p = 1LL << 19;
  DCLK_PORT &= ~_BV(DXMIT_BIT);	/* set nDXMIT=0 */
  for( int i=0; i<20; i++, p >>= 1) {
    if( DCLK_PIN & _BV(DOUT_BIT))
      v |= p;
    else
      v &= ~p;
    // toggle DCLK
    DCLK_PORT |= _BV(DCLK_BIT);
    DCLK_PORT &= ~_BV(DCLK_BIT);
    PORTC ^= _BV(PC3);		/* toggle test bit */
  }
  DCLK_PORT |= _BV(DXMIT_BIT);
  return v;
}

// set range
void ddc_range(uint8_t r) {
  RANGE_PORT &= ~RANGE_MASK;
  RANGE_PORT |= RANGE_MASK & r;
}


// set LED(s)
void ddc_leds(uint8_t v) {
  LED_PORT &= ~LED_MASK;
  LED_PORT |= v & LED_MASK;
}
