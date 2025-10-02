#ifndef DDC_H_INCLUDED
#define DDC_H_INCLUDED

#define DCLK_PORT PORTB
#define DCLK_DDR DDRB
#define DCLK_PIN PINB

#define DCLK_BIT PB5
#define DIN_BIT PB3
#define DOUT_BIT PB4
#define DXMIT_BIT PB0
#define CONV_BIT PB1

#define DVALID_PORT PORTD
#define DVALID_DDR DDRD
#define DVALID_PIN PIND
#define DVALID_BIT PD7

#define TEST_PORT PORTD
#define TEST_DDR DDRD
#define TEST_PIN PIND
#define TEST_BIT PD5
#define TEST_MASK _BV(TEST_BIT)

#define RANGE_PORT PORTC
#define RANGE_DDR DDRC
#define RANGE_MASK 7

#ifdef UNO_TARGET
#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_BIT PB5
#define LED_MASK _BV(LED_BIT)
#endif

#ifdef AVR_TARGET
#define LED_PORT PORTD
#define LED_DDR DDRD
#define LED_MASK (_BV(PD2)|_BV(PD3))
#define LED_BIT PD2
#define LED2_BIT PD3
#endif

void ddc_init();
void ddc_range(uint8_t r);
void ddc_leds(uint8_t v);
int wait_for_dvalid();
int wait_for_dvalid_conv();
uint32_t* read_ddc();

#endif
