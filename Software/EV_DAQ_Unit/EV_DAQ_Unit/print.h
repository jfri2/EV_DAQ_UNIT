/** @file print.h
* @brief Print routines for LCD and UART over stdio
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef print_h__
#define print_h__

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include "EV_DAQ_Unit.h"

// Function Prototypes
uint8_t stdio_uart_put(uint8_t ch, FILE *stream);
uint8_t stdio_uart_get(FILE *stream);
uint8_t stdio_lcd_put(uint8_t ch, FILE *stream);

// FILE declarations
static FILE stdio_uart = FDEV_SETUP_STREAM(stdio_uart_put, stdio_uart_get, _FDEV_SETUP_RW);
static FILE stdio_lcd = FDEV_SETUP_STREAM(stdio_lcd_put, NULL, _FDEV_SETUP_WRITE);

// External definitions
#define STDIO_UART  (&stdio_uart)
#define STDIO_LCD   (&stdio_lcd)

#endif // print_h__