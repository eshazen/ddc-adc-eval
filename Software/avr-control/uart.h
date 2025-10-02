#include <stdio.h>
#include <avr/io.h>

#define USART_BAUDRATE 9600
// #define USART_BAUDRATE 57600


#ifdef AVR_TARGET
// set fixed value for 16MHz AVR @ 19200
#define UBRR_VALUE 51
#else
// otherwise use calculation for Arduino at 16MHz
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#endif

//
// calculation above is wrong for some values
//
// use this table 8MHz clock (16MHz values not checked!)
// 16MHz    8MHz
// 19200    9600     = 51
// 38400    19200    = 25
// 115200   57600    = 8
// 250000   125000   = 3    (OK for 115.2k at 8MHz with 8.5% err)
// 500000   250000   = 1

void USART0Init(void);
void USART0SendString( char* str, FILE *stream);
int USART0SendByte(char u8Data, FILE *stream);
int USART0CharacterAvailable();
int USART0ReceiveByte( FILE *stream);
#ifdef UART_GET_STRING_USED
void USART0GetString( char *buffer, int max);
#endif
