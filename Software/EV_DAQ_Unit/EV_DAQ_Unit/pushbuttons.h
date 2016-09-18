/** @file pushbuttons.h
* @brief A description of the module's purpose.
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef pushbuttons_h__
#define pushbuttons_h__

#include "EV_DAQ_Unit.h"

// Switch (Pushbutton) Definitions
#define SW_DDR          DDRB
#define SW_PORT         PORTB
#define SW_1            (1<<PORTB0)
#define SW_2            (1<<PORTB1)

// TODO add pushbutton functionality including some form of software debounce

#endif // pushbuttons_h__