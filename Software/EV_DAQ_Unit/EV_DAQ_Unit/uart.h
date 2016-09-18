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
#include "data_types.h"
#include "gpio.h"

// UART & FTDI Definitions
#define UART_BAUD       115200
#define UART_DDR        DDRD
#define UART_PORT       PORTD
#define UART_PIN        PIND
#define UART_RTS        (1<<PORTD2)
#define UART_CTS        (1<<PORTD3)
#define UART_TOUT_MS    5       

// Macros
#define UART_DSSRT_RTS()  ( UART_PORT |= UART_RTS )
#define UART_ASSRT_RTS()  ( UART_PORT &= UART_RTS )
#define UART_GET_CTS()    ( UART_PIN & UART_CTS )   // Return not 0 when not active, 0 when active

void uart0_init(uint32_t cpu_freq, uint32_t uart_baud, bool b_flow_ctrl);
uint8_t uart0_put(uint8_t ch, bool b_flow_ctrl);
uint8_t uart0_puts(uint8_t *ch, uint8_t ch_len, bool b_flow_ctrl);
uint8_t uart0_get(bool b_flow_ctrl);
void uart0_gets(uint8_t *ch, uint8_t ch_len, bool b_flow_ctrl);

#endif // uart_h__
