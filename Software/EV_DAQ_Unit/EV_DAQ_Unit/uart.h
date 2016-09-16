/** @file uart.h
*
* @brief UART driver for ATMEGA328PB with stdio
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef uart_h__
#define uart_h__

#include <avr/io.h>
#include <stdio.h>

void uart0_init(uint32_t cpu_freq, uint32_t uart_baud);
void uart0_stdio_assign(void);
void uart0_put(uint8_t ch);
void uart0_puts(uint8_t *ch, uint8_t ch_len);
uint8_t uart0_stdio_put(uint8_t ch, FILE *stream);
uint8_t uart0_get(void);
void uart0_gets(uint8_t *ch, uint8_t ch_len);
uint8_t uart0_stdio_get(FILE *stream);

#endif // uart_h__