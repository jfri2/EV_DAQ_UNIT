/** @file lcd.h
* @brief A description of the module's purpose.
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/


#ifndef lcd_h__
#define lcd_h__

#include "EV_DAQ_Unit.h"

// LCD I2C Address
#define LCD_I2C_ADDR        0x7C        // Left justified LCD I2C address

// LCD Control Bytes
#define LCD_CTRL_IW         0x00        // LCD control byte instruction write operation mask
#define LCD_CTRL_IW_LAST    0x80        // LCD control byte instruction write operation mask (Last Control Byte Sent)
#define LCD_CTRL_DW         0x40        // LCD control byte data write operation mask
#define LCD_CTRL_DW_LAST    0xC0        // LCD control byte data write operation mask (Last Control Byte Sent)



void lcd_init();
void lcd_stdio_assign();
void lcd_set_line_1();
void lcd_set_line_2();

#endif // lcd_h__

