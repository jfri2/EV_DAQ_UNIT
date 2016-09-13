/** @file config.h*
* @brief Configuration file for EV_DAQ_Unit project
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef config_h__
#define config_h__

// Clock Definitions
#define F_CPU 16000000

// I2C & LCD Definitions
#define I2C_SCL_FREQ    100000
#define LCD_DEV_ADDR    0b00000001
#define LCD_RST_DDR     DDRB
#define LCD_RST_PORT    PORTB
#define LCD_RST         PORTB2

// UART & FTDI Definitions
#define UART_BAUD       115200
#define UART_DDR        DDRD
#define UART_PORT       PORTD
#define UART_RTS        PORTD2
#define UART_CTS        PORTD3

// Hall Effect Definitions
#define HE_DDR          DDRC
#define HE_PORT         PORTC
#define HE_1            PORTC3
#define HE_2            PORTC4 
#define HE_3            PORTC5

// LED Definitions
#define LED_DDR         DDRD
#define LED_PORT        PORTD
#define LED_RED         PORTD6
#define LED_GRN         PORTD7

// Switch (Pushbutton) Definitions
#define SW_DDR          DDRB
#define SW_PORT         PORTB
#define SW_1            PORTB0
#define SW_2            PORTB1

/* AVR */
#include <avr/io.h>

/* Project Drivers */
#include "gpio.h"
#include "i2c.h"
#include "adc.h"
#include "serial.h"
#include "timer.h"

/* Project Components */
#include "lcd.h"
#include "ftdi.h"
#include "hall_effect.h"
#include "pushbuttons.h"
#include "load_cell.h"
#include "leds.h"

#endif // config_h__