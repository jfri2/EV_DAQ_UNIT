/** @file serial.h
*
* @brief Serial (STDIO over UART) driver for ATMEGA328PB
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef serial_h__
#define serial_h__

#include <avr/io.h>
#include <stdio.h>

void uart0_stdio_init(uint32_t cpu_freq, uint32_t uart_baud);
void uart0_put(uint8_t ch);
void uart0_puts(uint8_t *ch, uint8_t ch_len);
uint8_t uart0_stdio_put(uint8_t ch, FILE *stream);
uint8_t uart0_get(void);
void uart0_gets(uint8_t *ch, uint8_t ch_len);
uint8_t uart0_stdio_get(FILE *stream);

static FILE uart_stdio = FDEV_SETUP_STREAM(uart0_stdio_put, uart0_stdio_get, _FDEV_SETUP_RW);


#endif // serial_h__