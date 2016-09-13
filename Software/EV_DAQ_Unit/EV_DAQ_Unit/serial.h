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
uint8_t uart0_stdio_write_byte(uint8_t ch, FILE *stream);
uint8_t uart0_stdio_read_byte(FILE *stream);
static FILE Avr_StdOut = FDEV_SETUP_STREAM(uart0_stdio_write_byte, uart0_stdio_read_byte, _FDEV_SETUP_RW);

#endif // serial_h__