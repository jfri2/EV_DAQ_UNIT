/** @file config.h
* @brief Configuration file for EV_DAQ_Unit project
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef config_h__
#define config_h__

// Clock Definitions
#define F_CPU           16000000
#define I2C_SCL_FREQ    100000

/* AVR Functions & Definitions*/
#include <avr/io.h>
#include <avr/interrupt.h>

/* Utilities */
#include "data_utils.h"

/* Project Drivers */
#include "gpio.h"
#include "i2c.h"
#include "adc.h"
#include "uart.h"

/* Project Driver & Component Combinations */
#include "timer.h"

/* Project Components */
#include "lcd.h"
#include "hall_effect.h"
#include "pushbuttons.h"
#include "load_cell.h"
#include "leds.h"
#include "print.h"

// TODO eventually add bootloader?

#endif // config_h__