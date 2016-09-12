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

// I2C Tx Definitions
#define I2C_START   0x00
#define I2C_DATA    0x01
#define I2C_STOP    0x02

// R/W Definitions
#define I2C_WRITE   0x00
#define I2C_READ    0x01

// I2C Status Codes
#define I2C_STATUS_START        0x08    // START condition has been transmitted
#define I2C_STATUS_RSTART       0x10    // REPEATED START condition has been transmitted
#define I2C_STATUS_SLAW_ACK     0x18    // SLA+W has been transmitted; ACK received
#define I2C_STATUS_SLAW_NACK    0x20    // SLA+W has been transmitted; NOT ACK received
#define I2C_STATUS_DATA_ACK     0x28    // Data byte has been transmitted; ACK received
#define I2C_STATUS_DATA_NACK    0x30    // Data byte has been transmitted; NOT ACK received
#define I2C_STATUS_ARBLOST      0x38    // Arbitration lost in SLA+W or data bytes

uint8_t i2c_calc_br_div(uint32_t cpu_freq, uint32_t i2c_freq);
uint8_t i2c1_tx(uint8_t i2c_event);
void i2c1_init(uint32_t i2c_freq);
uint8_t i2c1_write(uint8_t i2c_device_addr, uint8_t *p_i2c_data, uint32_t num_i2c_bytes);
uint8_t i2c1_read(uint8_t i2c_device_addr, uint8_t *p_i2c_data_in, uint8_t *p_i2c_data_out, uint32_t num_i2c_bytes);

#ifdef __cplusplus
}
#endif

#endif /* _I2C_H */