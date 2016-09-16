/** @file uart.c
*
* @brief Serial UART driver for ATMEGA328PB with stdio
*
* @par
* COPYRIGHT NOTICS: (c) 2016 John Fritz
* All rights reserved.
*/

#include "uart.h"

/*!
* @brief Initialize uart0
* @param[in] uint32_t cpu_freq      Frequency of CPU in Hz
* @param[in] uint32_t uart_baud     Desired UART baud rate
* @return void
*/
void uart0_init(uint32_t cpu_freq, uint32_t uart_baud) {    
    // Set UART0 to no parity, 8 data bits, 1 stop bit
    // Enable Tx & Rx UART
    UCSR0A = 0x00;
    UCSR0B = 0x18;
    UCSR0C = 0x06;
    
    // Set UART0 Baud Rate
    UBRR0H = (((cpu_freq/uart_baud)/32)-1)>>8;  // Set baud rate div (upper register)
    UBRR0L = (((cpu_freq/uart_baud)/32)-1);     // Set baud rate div (lower register)   
}

/*!
* @brief Assign STDIO streams to uart
* @return void
*/
void uart0_stdio_assign(void) {
    // Assign STDIO Streams
    static FILE uart_stdio = FDEV_SETUP_STREAM(uart0_stdio_put, uart0_stdio_get, _FDEV_SETUP_RW);
    stdout = &uart_stdio;   // Define output stream
    stdin = &uart_stdio;    // Define input stream
}

/*!
* @brief Write byte over UART0
* @param[in] uint8_t ch     Byte to write
* @return void
*/
void uart0_put(uint8_t ch) {
    while((UCSR0A & (1<<UDRE0)) == 0x00);    // Wait until tx buffer is empty
    UDR0 = ch;      // Load tx buffer with character to send
}

/*!
* @brief Send uint8_t array over UART0
* @param[in] uint8_t *ch      Pointer to array to send
* @param[in] uint8_t ch_len   Length of array
* @return void
*/
void uart0_puts(uint8_t *ch, uint8_t ch_len) {
    for(uint8_t i=0; i < ch_len; i++) {
        uart0_put(ch[i]);
    }
}

/*!
* @brief Write data over UART0 (stdio)
* @param[in] uint8_t ch      Character to write
* @param[in] FILE *stream   Pointer to stream location for stdio
* @return uint8_t
*/
uint8_t uart0_stdio_put(uint8_t ch, FILE *steam) {
    uart0_stdio_assign();
    uart0_put(ch);
    return(0);
}

/*!
* @brief Get uint8_t over UART0
* @return uint8_t   Value from UART0
*/
uint8_t uart0_get(void) {
    uart0_stdio_assign();
    while((UCSR0A & (1<<RXC0)) == 0x00);    // Wait until rx char flag is set
    return(UDR0);    
}

/*!
* @brief Get uint8_t array over UART0
* @param[in] uint8_t *ch      Pointer to array to store
* @param[in] uint8_t ch_len   Length of array
* @return uint8_t
*/
void uart0_gets(uint8_t *ch, uint8_t ch_len) {
    for(uint8_t i=0; i < ch_len; i++) {
        ch[i] = uart0_get();
    }
}

/*!
* @brief Read data over UART0 (stdio)
* @param[in] FILE *stream   Pointer to stream location for stdio
* @return uint8_t
*/
uint8_t uart0_stdio_get(FILE *stream) {
    uint8_t ch = uart0_get();
    return(ch);
}