#include "timer.h"

void init_timers( uint16_t conv_period) {

  // Initialize timer 0 to generate 8MHz square wave
  DDRD |= _BV(6);	      /* enable OC0A output */
  TCCR0A |= _BV(WGM01);	      /* set CTC mode */
  TCCR0A |= _BV(COM0A0);      /* toggle OC0A on compare match */      
  TCCR0B |= _BV(CS00);	      /* no prescaler */
  OCR0A = 0;		      /* max value (zero = 8MHz) */

  // Initialize time 1 to generate CONV signal at specified period
  DDRB |= _BV(1);		/* enable OC1A output */
  TCCR1B |= _BV(WGM12);		/* set CTC mode */
  TCCR1B |= _BV(CS10);		/* no prescaler */
  TCCR1A |= _BV(COM1A0);	/* toggle OC1A on compare match */
  OCR1A = conv_period;
}
