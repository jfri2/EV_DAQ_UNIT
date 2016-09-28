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
#define LCD_LINE1           0x02        // Send this as a command to set the LCD to Line 1
#define LCD_LINE2           0xC0        // Send this as a command to set the LCD to Line 2

// LCD Functions
void lcd_write(uint8_t cmd_data, uint8_t *data, uint16_t num_bytes);
void lcd_set_line1(void);
void lcd_set_line2(void);
void lcd_init();
void lcd_stdio_assign();    // TODO

// LCD Test String
static uint8_t lcd_test_str[16] = {"EV DAQ UNIT     "};

// TODO Add & define more LCD functions

#endif // lcd_h__

