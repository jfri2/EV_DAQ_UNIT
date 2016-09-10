/** @file gpio.h
* @brief General Purpose Input Output (GPIO) driver for ATMEGA328PB
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef _GPIO_H
#define _GPIO_H

#include <avr/io.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(PULLUP_ENABLE) || defined(PULLUP_DISABLE)
#warning "PULLUP_ENABLE and PULLUP_DISABLE redefined"
#endif

#define PULLUP_DISABLE   0
#define PULLUP_ENABLE    1

/*!
* @brief Set bits in a Data Direction Register (DDR) to output
* @param[in] reg_ddr   Data Direction Register to modify.
* @param[in] bm_ddr    Bits to set as output in DDR (as a bitmask).
* @return void
*/
extern inline void ddr_output(uint8_t reg_ddr, uint8_t bm_ddr) {
    reg_ddr |= bm_ddr;
}

/*!
* @brief Set bits in a Data Direction Register (DDR) to input
* @param[in] reg_ddr            Data Direction Register to modify.
* @param[in] reg_port           Port for pullup resistors
* @param[in] bm_ddr             Bits to set as input in DDR (as a bitmask).
* @param[in] b_PullupEnable     Enables or disables pullups on input pin
* @return void
*/
extern inline void ddr_input(uint8_t reg_ddr, uint8_t reg_port, uint8_t bm_ddr, uint8_t b_PullupEnable) {
    reg_ddr &= ~bm_ddr;
    if (b_PullupEnable != PULLUP_DISABLE) {
        reg_port |= bm_ddr;
        } else {
        reg_port &= ~bm_ddr;
    }
}

/*!
* @brief Set bits in a port to one (1)
* @param[in] reg_port  Port to modify
* @param[in] bm_set    Bits to set in port (as a bitmask).
* @return void
*/
extern inline void set_bits(uint8_t reg_port, uint8_t bm_set) {
    reg_port |= bm_set;
}

/*!
* @brief Clear bits in a port to one (1)
* @param[in] reg_port  Port to modify
* @param[in] bm_set    Bits to clear in port (as a bitmask).
* @return void
*/
extern inline void clear_bits(uint8_t reg_port, uint8_t bm_clear) {
    reg_port &= ~bm_clear;
}

/*!
* @brief Read PORTB pins
* @return portValue Value of port read
*/
extern inline uint8_t read_port_b(void) {
    return(PINB);
}

/*!
* @brief Read PORTC pins
* @return uint8_t Value of PORTC
*/
extern inline uint8_t read_port_c(void) {
    return(PINC);
}

/*!
* @brief Read PORTD pins
* @return uint8_t Value of PORTD
*/
extern inline uint8_t read_port_d(void) {
    return(PIND);
}

#ifdef __cplusplus
}
#endif

#endif /* _GPIO_H */