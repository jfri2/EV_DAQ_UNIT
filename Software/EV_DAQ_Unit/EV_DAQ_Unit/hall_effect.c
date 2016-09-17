/** @file hall_effect.c
*
* @brief A description of the module's purpose.
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved.
*/

#include "hall_effect.h"

/*!
* @brief Identify the larger of two 8-bit numbers.
* @param[in] num1    The first number to be compared.
* @param[in] num2    The second number to be compared.
* @return int8_t
*/
// TODO add IRQ handler & initializer for Pin-change interrupts
// TODO add functions for determining speed based off of PCINT IRQ handler