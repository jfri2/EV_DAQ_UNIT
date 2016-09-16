/** @file lcd.h
* @brief A description of the module's purpose.
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef lcd_h__
#define lcd_h__

#include "config.h"

void lcd_init();
void lcd_stdio_assign();
void lcd_set_line_1();
void lcd_set_line_2();

#endif // lcd_h__