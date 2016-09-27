/** @file config.h
* @brief Configuration file for EV_DAQ_Unit project
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef config_h__
#define config_h__

/* Clock Definitions */
#define F_CPU           16000000
#define I2C_SCL_FREQ    100000

/* GPIO Definitions */
#define SW_DDR          DDRB
#define SW_PORT         PORTB
#define SW_PIN          PINB
#define SW1             PORTB0
#define SW2             PORTB1
#define LED_DDR         DDRD
#define LED_PORT        PORTD
#define LED_RED         PORTD6
#define LED_GRN         PORTD7
#define LCD_RST_DDR     DDRB
#define LCD_RST_PORT    PORTB
#define LCD_RST         PORTB2
#define HE_DDR          DDRC
#define HE_PORT         PORTC
#define HE_1            PORTC3
#define HE_2            PORTC4
#define HE_3            PORTC5

/* AVR Functions & Definitions*/
#include <avr/io.h>
#include <avr/interrupt.h>

/* Utilities */
#include "data_utils.h"
#include "data_types.h"

/* Project Drivers */
#include "i2c.h"
#include "adc.h"
#include "uart.h"

/* Project Driver & Component Combinations */
#include "timer.h"
#include "gpio.h"

/* Project Components */
#include "lcd.h"
#include "hall_effect.h"
#include "load_cell.h"
#include "print.h"

// TODO eventually add bootloader?

#endif // config_h__