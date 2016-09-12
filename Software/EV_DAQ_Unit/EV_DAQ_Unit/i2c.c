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
    return((uint8_t)(((cpu_freq/i2c_freq) - 16)>>1));
}

/*!
* @brief Initialize I2C 1 service
* @param[in] i2c_freq   Desired I2C scl frequency
* @return void
*/
void i2c1_init(uint32_t i2c_freq) {
    TWBR1 = i2c_calc_br_div(F_CPU, i2c_freq);   // Set I2C SCL to correct value
    TWCR1 |= (1<<TWIE); // Enable TWI interrupt
}

/*!
* @brief Start I2C master tx event
* @param[in] i2c_event   Type of I2C event
* @return uint8_t I2C status register
*/
uint8_t i2c1_tx(uint8_t i2c_event) {
    switch(i2c_event) {
        case I2C_START:
            TWCR1 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);    // Tx start condition
            break;
        case I2C_DATA:
            TWCR1 = (1<<TWINT) | (1<<TWEN);                 // Tx data
            break;
        case I2C_STOP:
            TWCR1 = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);    // Tx stop condition
            break;
    }
    while (!(TWCR1 & (1 << TWINT))); // Wait for current request to process
    return(TWSR1 & I2C_STATUS_REG_MASK);     // Return only status bits in status reg
}

/*!
* @brief Write data to an I2C slave device
* @param[in] i2c_device_addr  I2C Device Address (7-bit, right justified)
* @param[in] p_i2c_data       Pointer to I2C message to write
* @param[in] num_i2c_bytes    Number of data bytes to write to I2C device (not counting I2C device address)
* @return uint8_t I2C status. 0x00 if write was successful, others=I2C Status register value on failure
*/
uint8_t i2c1_write(uint8_t i2c_device_addr, uint8_t *p_i2c_data, uint32_t num_i2c_bytes) {
    uint8_t i2c_status = 0;
    
    // I2C Start
    i2c_status = i2c1_tx(I2C_START);  // Start I2C Event
    if(i2c_status != I2C_STATUS_START) {
        return(i2c_status | I2C_STATUS_FAIL_MASK);    // Break from function if I2C start condition isn't reflected in status reg
    }   
     
    // I2C SLA+R/W
    TWDR1 = ((i2c_device_addr<<1) | I2C_WRITE);    // Set destination addr to device addr (7-bit, left justified), set I2C write condition
    i2c_status = i2c1_tx(I2C_DATA);
    if(i2c_status != I2C_STATUS_DATA_ACK) {
        return(i2c_status | I2C_STATUS_FAIL_MASK);    // Break from function if I2C data ack isn't reflected in status reg
    }
    
    // I2C Data Transfer
    for(uint32_t i = 0; i < num_i2c_bytes; i++) {
        TWDR1 = p_i2c_data[i];    // Load I2C data into register
        i2c_status = i2c1_tx(I2C_DATA);
        if(i2c_status != I2C_STATUS_DATA_ACK) {
            return(i2c_status | I2C_STATUS_FAIL_MASK);    // Break from function if I2C data ack isn't reflected in status reg
        }
    }    
    
    // I2C Stop Condition
    i2c_status = i2c1_tx(I2C_STOP);
        return(0);  // Return 0 if write operation was successful
    }
}

/*!
* @brief Write data to an I2C slave device
* @param[in] i2c_device_addr   I2C Device Address (7-bit, right justified)
* @param[in] p_i2c_data_in     Pointer to bytes to send over I2C
* @param[in] p_i2c_data_out    Pointer to location to store read I2C data
* @param[in] num_i2c_bytes     Number of data bytes to read from I2C device; length(p_i2c_data_in)=length(p_i2c_data_out)
* @return uint8_t I2C status. 0x00 if write was successful, others=I2C Status register value on failure
*/
uint8_t i2c1_read(uint8_t i2c_device_addr, uint8_t *p_i2c_data_in, uint8_t *p_i2c_data_out, uint32_t num_i2c_bytes) {
    uint8_t i2c_status = 0;
    
    // I2C Start
    i2c_status = i2c1_tx(I2C_START);  // Start I2C Event
    if(i2c_status != I2C_STATUS_START) {
        return(i2c_status | I2C_STATUS_FAIL_MASK);    // Break from function if I2C start condition isn't reflected in status reg
    }
    
    // I2C SLA+R/W
    TWDR1 = ((i2c_device_addr<<1) | I2C_READ);    // Set destination addr to device addr (7-bit, left justified), set I2C read condition
    i2c_status = i2c1_tx(I2C_DATA);
    if(i2c_status != I2C_STATUS_DATA_ACK) {
        return(i2c_status | I2C_STATUS_FAIL_MASK);    // Break from function if I2C data ack isn't reflected in status reg
    }
    
    // I2C Data Transfer
    for(uint32_t i = 0; i < num_i2c_bytes; i++) {
        TWDR1 = p_i2c_data_out[i];    // Load I2C data into register
        i2c_status = i2c1_tx(I2C_DATA);
        if(i2c_status != I2C_STATUS_DATA_ACK) {
            return(i2c_status | I2C_STATUS_FAIL_MASK);    // Break from function if I2C data ack isn't reflected in status reg
        }
        p_i2c_data_in[i] = TWDR1;   // Save data from I2C device
    }
    
    // I2C Stop Condition
    i2c_status = i2c1_tx(I2C_STOP);
    return(0);  // Return 0 if write operation was successful
}