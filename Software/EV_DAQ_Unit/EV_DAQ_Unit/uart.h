/** @file serial.h
*
* @brief Serial (STDIO over UART) driver for ATMEGA328PB
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef _SERIAL_H
#define _SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

void uart0_stdio_init(uint32_t cpu_freq, uint32_t uart_baud);
static int uart0_stdio_write_byte(uint8_t ch, FILE *stream);
static int uart0_stdio_read_byte(FILE *stream);
static FILE Avr_StdOut = FDEV_SETUP_STREAM(uart0_stdio_write_byte, uart0_stdio_read_byte, _FDEV_SETUP_RW);

#ifdef __cplusplus
}
#endif

#endif /* _SERIAL_H */