/** @file leds.h
* @brief A description of the module's purpose.
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef leds_h__
#define leds_h__

#include "EV_DAQ_Unit.h"

// LED Definitions
#define LED_DDR         DDRD
#define LED_PORT        PORTD
#define LED_RED         (1<<PORTD6)
#define LED_GRN         (1<<PORTD7)

// TODO Add status LED functionality

#endif // leds_h__