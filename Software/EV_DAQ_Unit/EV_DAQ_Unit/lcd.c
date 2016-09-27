/** @file lcd.c
*
* @brief Functions and definitions for the TODO LCD
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved.
*/

#include "lcd.h"
#include <util/delay.h>

/*!
* @brief Write to LCD
* @param uint8_t cmd_data       0 to send command, others to send data
* @param uint8_t *data          Pointer to data array to send.
* @param uint16_t num_bytes     Length of data to send.
* @return void
*/
void lcd_write(uint8_t cmd_data, uint8_t *data, uint16_t num_bytes) {
    i2c1_tx(I2C_START);     // Send start condition
    TWDR1 = LCD_I2C_ADDR;   // Set Slave Addr
    i2c1_tx(I2C_DATA);      // Send Slave Addr
    
    if(cmd_data == LCD_CMD) {
        TWDR1 = LCD_CMD;    // Load "Command" byte for LCD
        i2c1_tx(I2C_DATA);  // Send "Command" byte
    } else {
        TWDR1 = LCD_DATA;   // Load "Data" byte for LCD
        i2c1_tx(I2C_DATA);  // Send "Data" byte
    }
    
    for(uint16_t i=0; i<num_bytes; i++) {   // Send bytes
        TWDR1 = data[i];
        i2c1_tx(I2C_DATA);
    }
    
    i2c1_tx(I2C_STOP);  // Send stop condition
}

/*!
* @brief Initialize LCD
* @return void
*/
void lcd_init(void) {
    // This function isn't quite right, needs updating once hardware is in
        
    uint8_t lcd_config_1[2] = {0x00, 0x38};
    uint8_t lcd_config_2[1] = {0x39};
    uint8_t lcd_config_3[7] = {0x14, 0x78, 0x5E, 0x6D, 0x0C, 0x01, 0x06};
        
    i2c1_write(LCD_I2C_ADDR, lcd_config_1, 2);  // Write first commands
    delay(10);
    
    i2c1_write(LCD_I2C_ADDR, lcd_config_2, 1);  // Write second commands
    delay(10);
    
    i2c1_write(LCD_I2C_ADDR, lcd_config_3, 7);  // Write third commands
    delay(10);
}

/*!
* @brief Test LCD (custom test)
* @return void
*/
void lcd_test(void) {
    uint8_t lcd_config_1[1] = {0x38};
    uint8_t lcd_config_2[1] = {0x39};
    uint8_t lcd_config_3[7] = {0x14, 0x78, 0x5E, 0x6D, 0x0C, 0x01, 0x06};
    uint8_t lcd_config_4[1] = {0b01110000};
    uint8_t lcd_config_5[2] = {0x39, 0x01};
                                
    uint8_t lcd_test_str[11] = "Hello World";
    
    lcd_write(LCD_CMD, lcd_config_1, 1);
    delay(10);
    lcd_write(LCD_CMD, lcd_config_2, 1);
    delay(10);
    lcd_write(LCD_CMD, lcd_config_3, 7);
    delay(10);
    lcd_write(LCD_CMD, lcd_config_4, 1);
    delay(10);
    lcd_write(LCD_CMD, lcd_config_5, 2);
    delay(10);    
    lcd_write(LCD_DATA, lcd_test_str, 11);
}


/*!
* @brief Test LCD (manufacturer test)
* @return void
*/
void lcd_test_mfg(void) {
    /* Initialization Routine */
    i2c1_tx(I2C_START);    
    /* First few bytes to send */
    TWDR1 = 0x7C; // Slave Addr
    i2c1_tx(I2C_DATA);    
    TWDR1 = 0x00; // Comsend
    i2c1_tx(I2C_DATA);    
    TWDR1 = 0x38;
    i2c1_tx(I2C_DATA);    
    delay(10);    
    /* Next byte to send */
    TWDR1 = 0x39;
    i2c1_tx(I2C_DATA);    
    delay(10);    
    /* Last few bytes of initialization data */
    TWDR1 = 0x14;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x78;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x5E;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x6D;
    i2c1_tx(I2C_DATA);  // This command changed the screen
    TWDR1 = 0x0C;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x01;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x06;
    i2c1_tx(I2C_DATA);
    delay(10);    
    i2c1_tx(I2C_STOP);  // Issue with sending the stop condition (waiting on ACK)
    
    delay(100);
    
//     /* CGRAM? */
//     i2c1_tx(I2C_START);
//     delay(10);
//     TWDR1 = 0x7C; // Slave Addr
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x00; // Comsend
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x38;
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x40;
//     i2c1_tx(I2C_STOP);
//     delay(10);    
//     i2c1_tx(I2C_START);
//     delay(10);
//     TWDR1 = 0x7C; // Slave Addr
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x00; // Comsend
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x00;
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x1E;
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x18;
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x14;
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x12;
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x01;
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x00;
//     i2c1_tx(I2C_DATA);
//     TWDR1 = 0x00;   
//     i2c1_tx(I2C_STOP);
//     delay(10);        
    
    /* Set cursor back home */
    i2c1_tx(I2C_START);    
    delay(10);
    TWDR1 = 0x7C; // Slave Addr
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x00; // Comsend
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x39;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x01;
    i2c1_tx(I2C_DATA);    
    i2c1_tx(I2C_STOP);
    delay(10);
    
    /* Display test string */
    i2c1_tx(I2C_START);
    
    delay(10);
    TWDR1 = 0x7C; // Slave Addr
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x00; // Comsend
    i2c1_tx(I2C_DATA);    

    TWDR1 = 0x46;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x20;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x55;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x20;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x43;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x20;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x4b;
    i2c1_tx(I2C_DATA);


    i2c1_tx(I2C_STOP);
    delay(10);   
}

