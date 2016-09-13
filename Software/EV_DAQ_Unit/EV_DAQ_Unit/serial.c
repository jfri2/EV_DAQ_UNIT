/** @file serial.c
*
* @brief Serial (STDIO over UART) driver for ATMEGA328PB
*
* @par
* COPYRIGHT NOTICS: (c) 2016 John Fritz
* All rights reserved.
*/

#include "serial.h"

/*!
* @brief Initialize uart0
* @param[in] uint32_t cpu_freq      Frequency of CPU in Hz
* @param[in] uint32_t uart_baud     Desired UART baud rate
* @return void
*/
void uart0_stdio_init(uint32_t cpu_freq, uint32_t uart_baud) {    
    // Set UART0 to no parity, 8 data bits, 1 stop bit
    // Enable Tx & Rx UART
    UCSR0A = 0x00;
    UCSR0B = 0x18;
    UCSR0C = 0x06;
    
    // Set UART0 Baud Rate
    UBRR0H = (((cpu_freq/uart_baud)/32)-1)>>8;  // Set baud rate div (upper register)
    UBRR0L = (((cpu_freq/uart_baud)/32)-1);     // Set baud rate div (lower register)
    
    // Define STDIO Streams
    stdout = &Avr_StdOut;   // Define output stream
    stdin = &Avr_StdOut;    // Define input stream
}

/*!
* @brief Write data over UART0
* @param[in] uint8_t ch      Character to write
* @param[in] FILE *stream   Pointer to stream location for stdio
* @return int    
*/
uint8_t uart0_stdio_write_byte(uint8_t ch, FILE *steam) {
    while((UCSR0A & (1<<UDRE0)) == 0x00);    // Wait until tx buffer is empty
    UDR0 = ch;      // Load tx buffer with character to send    
    return(0);
}

/*!
* @brief Read data over UART0
* @param[in] FILE *stream   Pointer to stream location for stdio
* @return int
*/
uint8_t uart0_stdio_read_byte(FILE *stream) {
    while((UCSR0A & (1<<RXC0)) == 0x00);    // Wait until rx char flag is set
    return(UDR0);
}