#include "timer.h"

//
// Initialize timer 0 for an 8MHz square wave (50% duty cycle)
// Initialize timer 1 for a programmable period, 50% duty cycle
//   Force timer 1 value to be odd so there are an even number of cycles
//   Timer 1 changes on rising edge of timer 0
//

//
// Warning!  Rough road ahead!
// We want to reset the timers, including their "output compare" toggles,
// to a known state so the relative output phase is always the same
// between the two timers.
//
void reset_timers() {
  uint8_t sr;

  // save interrupt status and disable interrupts, just in case
  sr = SREG;
  cli();
  // the next is technically not needed with prescale = 1, but just to be safe
  GTCCR |= _BV(TSM) | _BV(PSRSYNC) | _BV(PSRASY);	/* clear timer prescalers */

  // set the actual counter values for the phase we want
  TCNT0 = 0;			/* clear counter 0 */
  TCNT1 = 1;			/* offset timer 1 by 1 count for phase */

  // reset the output compare toggles.  
  // temporarily change OC1 and OC2 to "clear on compare match
  // Timer 0:  A1 = 1  A0 = 0
  TCCR0A &= ~_BV(COM0A0);
  TCCR0A |= _BV(COM0A1);
  // Timer 1:  A1 = 1  A0 = 0
  TCCR1A &= ~_BV(COM1A0);
  TCCR1A |= _BV(COM1A1);

  // force a compare match to clear the compare toggles
  TCCR1C |= _BV(FOC1A) | _BV(FOC1B);
  TCCR0B |= _BV(FOC0A) | _BV(FOC0B);

  // reset to normal values
  // A1 = 0  A0 = 1
  TCCR0A |= _BV(COM0A0);      /* toggle OC0A on compare match */      
  TCCR0A &= ~_BV(COM0A1);

  TCCR1A |= _BV(COM1A0);	/* toggle OC1A on compare match */
  TCCR1A &= ~_BV(COM1A1);
  
  SREG = sr;			/* restore interrupt enable */
  GTCCR = 0;			/* release timer clear */
}

void init_timers( uint16_t conv_period) {
  conv_period |= 1;		/* force to be an odd number */

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
  
  reset_timers();
}
