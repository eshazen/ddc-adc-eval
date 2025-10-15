//
// Read the built-in ADC on an AVR chip (known to work for Atmega328)
// Use 128x prescaler and VCC as Vref
//

#include "avr_adc.h"

void InitADC()
{
  // Select Vref=AVcc
  ADMUX |= (1<<REFS0);
  //set prescaller to 128 and enable ADC 
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);    
}

uint16_t ReadADC(uint8_t ADCchannel)
{
  //select ADC channel with safety mask
  ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
  //single conversion mode
  ADCSRA |= (1<<ADSC);
  // wait until ADC conversion is complete
  while( ADCSRA & (1<<ADSC) );
  return ADC;
}

