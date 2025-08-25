#ifndef DDC_H_INCLUDED
#define DDC_H_INCLUDED

#define DCLK_PORT PORTB
#define DCLK_DDR DDRB
#define DCLK_PIN PINB

#define DCLK_BIT PB5
#define DIN_BIT PB3
#define DOUT_BIT PB4
#define DXMIT_BIT PB0

#define DVALID_PORT PORTD
#define DVALID_DDR DDRD
#define DVALID_PIN PIND
#define DVALID_BIT PD7

void ddc_init();

#define wait_for_dvalid() {while((DVALID_PIN&_BV(DVALID_BIT)));}

uint32_t read_ddc();

#endif
