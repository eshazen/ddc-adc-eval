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
#include "i2c.h"
#include "led.h"

// create a file pointer for read/write to USART0
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);

// serial command processing buffers
#define MAXARG 6
static char buff[80];
static char* argv[MAXARG];
static int iargv[MAXARG];

// temp variables
static uint8_t v;
static uint16_t adc;
static uint32_t iv;

void chk_err( uint8_t rc) {
  if( rc) {
    snprintf( buff, sizeof(buff), "I2C_err: 0x%02x", rc);
    puts(buff);
  }
}

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

#ifdef AVR_TARGET
  ddc_init();
#endif  
  i2c_init( BDIV);

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
      puts_P( PSTR("L d           - set LEDs"));
      puts_P( PSTR("T n           - start timers with CONV period=n"));
      puts_P( PSTR("G n           - set integrator range 0-7"));
      puts_P( PSTR("A             - readout ADC"));
      puts_P( PSTR("D n           - set DAC"));
      puts_P( PSTR("M en ch       - set mux en=0/1 ch=0..7"));
      puts_P( PSTR("---"));
      puts_P( PSTR("AV            - read without wait for data valid"));
      puts_P( PSTR("AR            - repeated readout for scope test"));
      puts_P( PSTR("W t r [d...]  - write I2C"));
      puts_P( PSTR("V             - read timer1 value"));
      puts_P( PSTR("X             - reset timers"));
      break;

    case 'D':
      set_dac( iargv[1]);
      break;

    case 'M':
      set_mux( iargv[1], iargv[2]);
      break;

    case 'W':			/* I2C write */
      // iargv[1] = I2C target address
      // iargv[2] = chip register address
      // iargv[3..n] = data
      // copy the register address
      i2c_adr = iargv[2];
      // copy the write data, including chip address if present
      for( int i=2; i<argc; i++)
	i2c_wdata[i-1] = iargv[i];
      rc = i2c_io( iargv[1], &i2c_adr, 1, i2c_wdata, argc-2, NULL, 0);
      chk_err(rc);
      break;

    case 'G':
      if( argc < 2) {
	error();
      } else {
	ddc_range( iargv[1]);
      }
      break;

    case 'A':
      if( cmd_2 == 'R') {
	while( !USART0CharacterAvailable()) {
	  while( TCNT1 < 4208)
	    ;
	  iv = read_ddc();
	}
      } else if( cmd_2 != 'V') {
	wait_for_dvalid();
      }
      iv = read_ddc();
      printf("%ld (0x%lx)\n", iv, iv);
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


