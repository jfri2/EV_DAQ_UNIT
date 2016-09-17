/** @file lcd.c
*
* @brief Functions and definitions for the TODO LCD
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved.
*/

#include "lcd.h"

/*!
* @brief Initialize LCD
* @return void
*/
void lcd_init(void) {
    // This function isn't quite right, needs updating once hardware is in
    uint32_t temp_ms = 0;
    
    uint8_t lcd_config_1[2] = {0x00, 0x38};
    uint8_t lcd_config_2[1] = {0x39};
    uint8_t lcd_config_3[7] = {0x14, 0x78, 0x5E, 0x6D, 0x0C, 0x01, 0x06};
        
    i2c1_write(LCD_I2C_ADDR, lcd_config_1, 2);  // Write first commands
    temp_ms = systck;   // Get current time
    while(systck < (temp_ms + 10));     // Wait for command to process
    
    i2c1_write(LCD_I2C_ADDR, lcd_config_2, 1);  // Write second commands
    temp_ms = systck;   // Get current time
    while(systck < (temp_ms + 10));     // Wait for command to process
    
    i2c1_write(LCD_I2C_ADDR, lcd_config_3, 7);  // Write third commands
}

