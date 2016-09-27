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
* @brief Test LCD
* @return void
*/
void lcd_test(void) {
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
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x0C;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x01;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x06;
    i2c1_tx(I2C_DATA);
    delay(10);    
    i2c1_tx(I2C_STOP);
    
    delay(100);
    
    /* CGRAM? */
    i2c1_tx(I2C_START);
    delay(10);
    TWDR1 = 0x7C; // Slave Addr
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x00; // Comsend
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x38;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x40;
    i2c1_tx(I2C_STOP);
    delay(10);    
    i2c1_tx(I2C_START);
    delay(10);
    TWDR1 = 0x7C; // Slave Addr
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x00; // Comsend
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x00;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x1E;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x18;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x14;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x12;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x01;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x00;
    i2c1_tx(I2C_DATA);
    TWDR1 = 0x00;   
    i2c1_tx(I2C_STOP);
    delay(10);        
    
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

    TWDR1 = 'H';
    i2c1_tx(I2C_DATA);
    TWDR1 = 'e';
    i2c1_tx(I2C_DATA);
    TWDR1 = 'l';
    i2c1_tx(I2C_DATA);
    TWDR1 = 'l';
    i2c1_tx(I2C_DATA);
    TWDR1 = 'o';
    i2c1_tx(I2C_DATA);
    TWDR1 = ' ';
    i2c1_tx(I2C_DATA);
    TWDR1 = 'W';
    i2c1_tx(I2C_DATA);
    TWDR1 = 'o';
    i2c1_tx(I2C_DATA);
    TWDR1 = 'r';
    i2c1_tx(I2C_DATA);
    TWDR1 = 'l';
    i2c1_tx(I2C_DATA);
    TWDR1 = 'd';
    i2c1_tx(I2C_DATA);

    i2c1_tx(I2C_STOP);
    delay(10);   
}

