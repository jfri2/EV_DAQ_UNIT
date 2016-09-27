/** @file gpio.c
*
* @brief General Purpose Input Output (GPIO) driver for ATMEGA328PB
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved.
*/

#include "gpio.h"

/*!
* @brief Initialize GPIO for EV DAQ UNIT project
* @return void
*/
void gpio_init(void) {
    /* Setup Switches */
    clrbits(SW_DDR, ((1<<SW1)|(1<<SW2))); // Set switches to input
    sbits(SW_PORT, ((1<<SW1)|(1<<SW2)));  // Turn on pullups on switches
    
    /* Setup LEDs */
    sbits(LED_DDR, ((1<<LED_RED)|(1<<LED_GRN)));  // LEDs as output
    
    /* Setup LCD /RST */
    sbit(LCD_RST_DDR, LCD_RST);     // Set LCD_RST to output
    sbit(LCD_RST_PORT, LCD_RST);    // Drive LCD_RST high    
}