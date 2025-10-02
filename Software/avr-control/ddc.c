#include <stdint.h>
#include "ddc.h"
#include <avr/io.h>
#include <util/delay.h>

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

  // set test as output, set low
  TEST_DDR |= TEST_MASK;
  TEST_PORT &= ~TEST_MASK;

  // set range as outputs, set to 0
  RANGE_DDR |= RANGE_MASK;
  ddc_range(0);

  LED_DDR |= LED_MASK;	/* set LED direction */
  LED_PORT &= ~LED_MASK;
}

// read DDC 20 bit data (don't wait for DVALID)
uint32_t* read_ddc() {
  static uint32_t res[2];
  uint32_t v = 0;
  uint32_t p = 1LL << 19;
  DCLK_PORT &= ~_BV(DXMIT_BIT);	/* set nDXMIT=0 */
  // read channel 1
  for( int i=0; i<20; i++, p >>= 1) {
    if( DCLK_PIN & _BV(DOUT_BIT))
      v |= p;
    // toggle DCLK
    DCLK_PORT |= _BV(DCLK_BIT);
    DCLK_PORT &= ~_BV(DCLK_BIT);
  }
  res[0] = v;
  // read channel 2
  v = 0;
  p = 1LL << 19;
  for( int i=0; i<20; i++, p >>= 1) {
    if( DCLK_PIN & _BV(DOUT_BIT))
      v |= p;
    // toggle DCLK
    DCLK_PORT |= _BV(DCLK_BIT);
    DCLK_PORT &= ~_BV(DCLK_BIT);
  }
  res[1] = v;
  DCLK_PORT |= _BV(DXMIT_BIT);	/* set nDXMIT=1 */
  return res;
}

// set range
void ddc_range(uint8_t r) {
  RANGE_PORT &= ~RANGE_MASK;
  RANGE_PORT |= RANGE_MASK & r;
}


// set LED(s)
void ddc_leds(uint8_t v) {
  LED_PORT &= ~LED_MASK;	/* LEDs off */
  LED_PORT |= (v << LED_BIT) & LED_MASK;
}

// wait for nDVALID, count wait time
int wait_for_dvalid() {
  int wtime = 0;
  while((DVALID_PIN&_BV(DVALID_BIT))) {
    ++wtime;
  }
  return wtime;
}

// wait for nDVALID && CONV == 0, count wait time
int wait_for_dvalid_conv() {
  int wt;
  wt = wait_for_dvalid();
  if ( DCLK_PIN & _BV(CONV_BIT)) {
    // pulse DXMIT to reset
    DCLK_PORT &= ~_BV(DXMIT_BIT);	/* set nDXMIT=0 */
    DCLK_PORT |= _BV(DXMIT_BIT);	/* set nDXMIT=1 */
    _delay_us(1);
    wt = wait_for_dvalid();
  }
  return wt;
}
