/** @file uart.c
*
* @brief Serial UART driver for ATMEGA328PB with stdio
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
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
* @brief Get uint8_t over UART0
* @return uint8_t   Value from UART0
*/
uint8_t uart0_get(void) {
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
