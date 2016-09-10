/** @file i2c.h
* @brief I2C (master) driver for ATMEGA328PB
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef _I2C_H
#define _I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
* @brief Starts I2C 1 service
* @return void
*/
extern inline void i2c1_start(void) {
    TWCR1 |= (1<<TWEN);
}

/*!
* @brief Stops I2C 1 service
* @return void
*/
extern inline void i2c1_stop(void) {
    TWCR1 &= ~(1<<TWEN);
}

uint8_t i2c_calc_br_div(uint32_t cpu_freq, uint32_t i2c_freq);
void i2c1_init(uint32_t i2c_freq);
void i2c1_send_byte(uint8_t i2c_device_addr);
uint8_t i2c1_read_byte(void);

#ifdef __cplusplus
}
#endif

#endif /* _I2C_H */