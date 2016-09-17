/** @file print.c
*
* @brief A description of the module's purpose.
*
* @par
* COPYRIGHT NOTICE (c) 2016 John Fritz
* All rights reserved.
*/

#include "print.h"

/*!
* @brief Write data over UART0 (stdio)
* @param[in] uint8_t ch     Character to write
* @param[in] FILE *stream   Pointer to stream location for stdio
* @return uint8_t
*/
uint8_t stdio_uart_put(uint8_t ch, FILE *stream) {
    uart0_put(ch);
    return(0);
}

/*!
* @brief Read data over UART0 (stdio)
* @param[in] FILE *stream   Pointer to stream location for stdio
* @return uint8_t
*/
uint8_t stdio_uart_get(FILE *stream) {
    uint8_t ch = uart0_get();
    return(ch);
}

/*!
* @brief Write data to LCD (stdio)
* @param[in] uint8_t ch     Character to write
* @param[in] FILE *stream   Pointer to stream location for stdio
* @return uint8_t
*/
uint8_t stdio_lcd_put(uint8_t ch, FILE *stream) {
    // TODO
    return(0);
}

// TODO update this module to work with FTDI rather than direct UART