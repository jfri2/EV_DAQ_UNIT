/** @file hall_effect.h
* @brief A description of the module's purpose.
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef hall_effect_h__
#define hall_effect_h__

#include "EV_DAQ_Unit.h"

// Hall Effect Definitions
#define ADC_NC_MASK     ((1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2))  // NC (no connect) pins
#define ADC_DIG_DIS_HE  ((1<<ADC0D) | (1<<ADC1D) | (1<<ADC2D))     // NC pin ADC channels (used to disable digital input buffers)

#endif // hall_effect_h__