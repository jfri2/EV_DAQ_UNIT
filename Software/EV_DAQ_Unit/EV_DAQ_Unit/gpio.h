/** @file gpio.h
*
* @brief General Purpose Input Output (GPIO) driver for ATMEGA328PB
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef gpio_h__
#define gpio_h__

#include "EV_DAQ_Unit.h"

/*!
* @brief Set bit in register
* @param[in] reg        Register to modify
* @param[in] bit        Bit position to set
* @return void
*/
#define sbit(reg, bit) ( reg |= (1<<bit) )

/*!
* @brief Set bits in register
* @param[in] reg        Register to modify
* @param[in] bm         Bitmask for register
* @return void
*/
#define sbits(reg, bm) ( reg |= bm )

/*!
* @brief Clear bit in register
* @param[in] reg        Register to modify
* @param[in] bit        Bit position to clear
* @return void
*/
#define clrbit(reg, bit) ( reg &= ~(1<<bit) )

/*!
* @brief Clear bits in register
* @param[in] reg        Register to modify
* @param[in] bm         Bitmask for register
* @return void
*/
#define clrbits(reg, bm) ( reg &= ~bm )

/*!
* @brief Toggle bit in register
* @param[in] reg        Register to modify
* @param[in] bit        Bit to toggle
* @return void
*/
#define tbit(reg, bit) ( reg ^= (1<<bit) )

/*!
* @brief Toggle bits in register
* @param[in] reg        Register to modify
* @param[in] bm         Bitmask for register
* @return void
*/
#define tbits(reg, bm) ( reg ^= bm )

/*!
* @brief Check bit in register
* @param[in] reg        Register to check
* @param[in] bit        Bit position to check
* @return uint8_t       Return 0x00 if bit is not set, others if set
*/
#define chkbit(reg, bit) ( reg & (1<<bit) )

void gpio_init(void);

#endif // gpio_h__