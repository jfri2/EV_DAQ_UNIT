/** @file lcd.h
* @brief Functions and definitions for the TODO LCD
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/


#ifndef lcd_h__
#define lcd_h__

#include "EV_DAQ_Unit.h"

// LCD I2C Definitions
#define LCD_DEV_ADDR        0b00000001
#define LCD_I2C_ADDR        0x7C        // Left justified LCD I2C address

// LCD Control Bytes (TODO)
#define LCD_CMD             0x00        // Send this before sending commands to LCD
#define LCD_DATA            0x40        // Send this before sending data to LCD
#define LCD_LINE2           0xC0        // Send this to set the LCD to Line 2

// LCD Functions
void lcd_write(uint8_t cmd_data, uint8_t *data, uint16_t num_bytes);
void lcd_init();            // TODO
void lcd_stdio_assign();    // TODO
void lcd_test(void);
void lcd_test_mfg(void);

// LCD Test String
static uint8_t lcd_test_str[16] = {"EV DAQ UNIT     "};

// TODO Add & define more LCD functions

#endif // lcd_h__

