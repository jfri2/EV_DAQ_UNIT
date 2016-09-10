/** @file module.c
*
* @brief A description of the module's purpose.
*
* @par
* COPYRIGHT NOTICS: (c) 2016 John Fritz
* All rights reserved.
*/

#include "adc.h"

/*!
* @brief Identify the larger of two 8-bit numbers.
* @param[in] num1    The first number to be compared.
* @param[in] num2    The second number to be compared.
* @return int8_t
*/
int8_t max8 (int8_t num1, int8_t num2) {
	return ((num1 > num2) ? num1 : num2);
}