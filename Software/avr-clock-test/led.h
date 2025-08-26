#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

#include <stdint.h>

void init_led();
void set_dac( uint16_t v);
void set_mux( uint8_t en, uint8_t ch);

#endif
