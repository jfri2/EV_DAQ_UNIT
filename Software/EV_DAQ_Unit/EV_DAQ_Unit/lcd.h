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

// LCD Control Bytes
#define LCD_CTRL_IW         0x00        // LCD control byte instruction write operation mask
#define LCD_CTRL_IW_LAST    0x80        // LCD control byte instruction write operation mask (Last Control Byte Sent)
#define LCD_CTRL_DW         0x40        // LCD control byte data write operation mask
#define LCD_CTRL_DW_LAST    0xC0        // LCD control byte data write operation mask (Last Control Byte Sent)

// LCD Functions
void lcd_init();            // TODO
void lcd_stdio_assign();    // TODO
void lcd_write(uint8_t *data, uint16_t num_bytes);
void lcd_test();

// LCD Test String
static uint8_t lcd_test_str[16] = {"EV DAQ UNIT     "};

// TODO Add & define more LCD functions

#endif // lcd_h__

