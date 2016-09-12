/** @file config.h*
* @brief Configuration file for EV_DAQ_Unit project
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef _CONFIG_H
#define _CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Drivers */
#include "gpio.h"
#include "i2c.h"
#include "adc.h"
#include "serial.h"
#include "timer.h"

/* Project Libraries */
#include "lcd.h"
#include "ftdi.h"
#include "hall_effect.h"
#include "pushbuttons.h"
#include "load_cell.h"
#include "leds.h"

#ifdef __cplusplus
}
#endif

#endif /* _CONFIG_H */