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
* @brief Set cursor to LCD line 1
* @return void
*/
void lcd_set_line1() {
    uint8_t lcd_line1[1] = {LCD_LINE1};
        lcd_write(LCD_CMD, lcd_line1, 1);
        delay(100);
}

/*!
* @brief Set cursor to LCD line 2
* @return void
*/
void lcd_set_line2() {
    uint8_t lcd_line2[1] = {LCD_LINE2};
    lcd_write(LCD_CMD, lcd_line2, 1);
    delay(100);
}

/*!
* @brief Clear LCD display
* @return void
*/
void lcd_clear(void) {
    uint8_t lcd_clear[1] = {0x01};
    lcd_write(LCD_CMD, lcd_clear, 1);
    delay(10);
}

/*!
* @brief Initialize LCD
* @return void
*/
void lcd_init(void) {
    uint8_t lcd_config_1[1] = {0x38};
    uint8_t lcd_config_2[1] = {0x39};
    uint8_t lcd_config_3[7] = {0x14, 0x78, 0x5E, 0x6D, 0x0C, 0x01, 0x06};
    uint8_t lcd_config_4[1] = {0x70};     // Set contrast 
                                
    uint8_t lcd_init_str1[16] = "EV DAQ UNIT v0.1";
    uint8_t lcd_init_str2[16] = "github.com/jfri2";
    
    /* Reset LCD */
    clrbit(LCD_RST_PORT, LCD_RST);
    delay(10);
    sbit(LCD_RST_PORT, LCD_RST);
    delay(10);
    
    /* Write Configuration to LCD */
    lcd_write(LCD_CMD, lcd_config_1, 1);
    delay(10);
    lcd_write(LCD_CMD, lcd_config_2, 1);
    delay(10);
    lcd_write(LCD_CMD, lcd_config_3, 7);
    delay(10);
    lcd_write(LCD_CMD, lcd_config_4, 1);
    delay(10);    
    
    /* Display Initial Message */
    //lcd_set_line1();
    lcd_write(LCD_DATA, lcd_init_str1, 16);
    lcd_set_line2();
    lcd_write(LCD_DATA, lcd_init_str2, 16);
}


