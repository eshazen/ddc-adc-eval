/*
 * AVR clocking tests for DDC ADC
 */

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "parse.h"
#include "timer.h"
#include "ddc.h"

// create a file pointer for read/write to USART0
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);

// serial command processing buffers
#define MAXARG 6
static char buff[80];
static char* argv[MAXARG];
static int iargv[MAXARG];

// temp variables
uint8_t v;
uint16_t adc;
uint32_t iv;
uint32_t tv = 0xdeadbeefL;

void error() {
  puts_P( PSTR("Error"));
}

int main (void)
{
  unsigned char c = ' ';

  USART0Init();			/* initialize non-interrupt UART */
  stdout = &usart0_str;		/* connect UART to stdout */
  stdin = &usart0_str;		/* connect UART to stdin */

  DDRC |= _BV(PC3);		/* set spare I/O PC3 as output */
  PORTC |= _BV(PC3);		/* set spare I/O PC3 high */

  ddc_init();

  SPCR &= ~_BV(SPE);		/* make sure SPI is disabled */

  puts_P( PSTR("Clock test 0.1"));

  while(1) {
    fputs(">", stdout);
    USART0GetString( buff, sizeof(buff));
    int argc = parse( buff, argv, iargv, sizeof(argv)/sizeof(argv[0]));

    char cmd_c = toupper( *argv[0]);
    char cmd_2 = toupper( argv[0][1]);

    switch( cmd_c) {
    case 'H':
      puts_P( PSTR("L d   - set LEDs"));
      puts_P( PSTR("T n   - start timers with CONV period=n"));
      puts_P( PSTR("V     - read timer1 value"));
      puts_P( PSTR("X     - reset timers"));
      puts_P( PSTR("G n   - set integrator range 0-7"));
      puts_P( PSTR("R     - readout ADC"));
      puts_P( PSTR("RR    - repeated readout for scope test"));
      puts_P( PSTR("RV    - read with wait for data valid"));
      break;

    case 'G':
      if( argc < 2) {
	error();
      } else {
	ddc_range( iargv[1]);
      }
      break;

    case 'R':
      switch( cmd_2) {
      case 'R':
	while( !USART0CharacterAvailable()) {
	  while( TCNT1 < 4208)
	    ;
	  iv = read_ddc();
	}
	break;
      case 'V':
	wait_for_dvalid();

      default:
	iv = read_ddc();
	printf("%ld (0x%lx)\n", iv, iv);
	break;
      }
      break;
      
    case 'V':
      iv = TCNT1;
      printf("%d\n", iv);
      break;

    case 'L':
      if( argc < 2) {
	error();
      } else {
	ddc_leds( iargv[1]);
      }
      break;

    case 'T':
      init_timers( iargv[1]);
      break;

    case 'X':
      reset_timers();
      break;

    default:
      error();
    }    
  }
}


