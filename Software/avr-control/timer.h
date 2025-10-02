#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void init_timers( uint16_t conv_rate);
void reset_timers();

#endif
