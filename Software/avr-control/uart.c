//
// UART Functions
// Rx is polled
// Tx is interrupt-driven
//

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

// Circular buffer for transmit
#define TX_BUFFER_SIZE 64
volatile char tx_buffer[TX_BUFFER_SIZE];
volatile uint8_t tx_head = 0;
volatile uint8_t tx_tail = 0;

// initialize the UART.  Baud rate set in uart.h
void USART0Init(void)
{
  // Set baud rate
  UBRR0H = (uint8_t)(UBRR_VALUE>>8);
  UBRR0L = (uint8_t)UBRR_VALUE;
  // Set frame format to 8 data bits, no parity, 1 stop bit
  UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
  //enable transmission and reception
  UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
  //  UCSR0B |= (1 << RXCIE0); // Enable receive complete interrupt
  sei(); // Enable global interrupts
}



// send a byte.  stream is provided for stdio compatibility
// and may be NULL
int USART0SendByte(char c, FILE *stream) {
    if (c == '\n') {
        USART0SendByte('\r', stream); // Add carriage return for newlines
    }

    // Wait if buffer is full
    while (((tx_head + 1) % TX_BUFFER_SIZE) == tx_tail);

    tx_buffer[tx_head] = c;
    tx_head = (tx_head + 1) % TX_BUFFER_SIZE;

    UCSR0B |= (1 << UDRIE0); // Enable UDRE interrupt to start transmission

    return 0;
//   if(u8Data == '\n')
//     {
//       USART0SendByte('\r', stream);
//     }
//   //wait while previous byte is completed
//   while(!(UCSR0A&(1<<UDRE0))){};
//   // Transmit data
//   UDR0 = u8Data;
//   return 0;
}


// Transmit Data Register Empty Interrupt Service Routine
ISR(USART_UDRE_vect) {
    if (tx_head != tx_tail) { // If there's data to send
        UDR0 = tx_buffer[tx_tail];
        tx_tail = (tx_tail + 1) % TX_BUFFER_SIZE;
    } else {
        UCSR0B &= ~(1 << UDRIE0); // Disable UDRE interrupt if buffer is empty
    }
}



// return true if a character is available for input
int USART0CharacterAvailable()
{
  return (UCSR0A&(1<<RXC0));
}

// receive a byte, block in none available
// argument is ignored
// echo character
// convert <CR> to <LF>
int USART0ReceiveByte( FILE *stream)
{
  unsigned char c;
  // Wait for byte to be received
  while(!(UCSR0A&(1<<RXC0))){};
//  // Return received data
  c = UDR0;
//  USART0SendByte( c, NULL);
  if(c == '\r') {
    c = '\n';
//    USART0SendByte( c, NULL);
  }
  return c;
}



void USART0GetString( char *buffer, int max)
{
  int n = 0;
  char *p = buffer;
  uint8_t c;

  while( 1) {
    c = USART0ReceiveByte( NULL);
    if( c == '\n') {
      putchar( c);
      *p++ = '\0';
      return;
    }
    if( c == '\b' && p > buffer) {
      putchar('\b');
      --p;
    } else {
      putchar( c);
      *p++ = c;
    }
    
  }
  
}
