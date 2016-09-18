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

// LCD Definitions
#define LCD_DEV_ADDR    0b00000001
#define LCD_RST_DDR     DDRB
#define LCD_RST_PORT    PORTB
#define LCD_RST         (1<<PORTB2)

// LCD I2C Address
#define LCD_I2C_ADDR        0x7C        // Left justified LCD I2C address

// LCD Control Bytes
#define LCD_CTRL_IW         0x00        // LCD control byte instruction write operation mask
#define LCD_CTRL_IW_LAST    0x80        // LCD control byte instruction write operation mask (Last Control Byte Sent)
#define LCD_CTRL_DW         0x40        // LCD control byte data write operation mask
#define LCD_CTRL_DW_LAST    0xC0        // LCD control byte data write operation mask (Last Control Byte Sent)

// LCD Functions
void lcd_init();
void lcd_stdio_assign();
void lcd_set_line_1();
void lcd_set_line_2();

// TODO Add & define more LCD functions

#endif // lcd_h__

