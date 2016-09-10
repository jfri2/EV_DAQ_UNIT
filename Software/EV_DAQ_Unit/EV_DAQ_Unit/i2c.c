/** @file i2c.c
*
* @brief I2C (master) driver for ATMEGA328PB
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved.
*/

#include "i2c.h"

/*!
* @brief Calculate 8-bit baud rate division factor.
* @param[in] cpu_freq   CPU frequency (usually F_CPU) in Hz
* @param[in] i2c_freq   desired I2C frequency in Hz
* @return uint8_t   Division factor
*/
uint8_t i2c_calc_br_div(uint32_t cpu_freq, uint32_t i2c_freq) {
    return(uint8_t(((cpu_freq/i2c_freq) - 16)>>1));
}

/*!
* @brief Initialize I2C 1 service
* @param[in] i2c_freq   Desired I2C scl frequency
* @return void
*/
void i2c1_init(uint32_t i2c_freq) {
	i2c1_stop();    // Terminate any ongoing I2C transmissions
    i2c1_start();   // Start new I2C service
    TWBR1 = i2c_calc_br_div(F_CPU, i2c_freq);   // Set I2C SCL to correct value
    
}