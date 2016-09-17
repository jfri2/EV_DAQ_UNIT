/** @file module.c
*
* @brief A description of the module's purpose.
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
    uint8_t *
    i2c1_write(LCD_I2C_ADDR, lcd_init_1, 3);
}