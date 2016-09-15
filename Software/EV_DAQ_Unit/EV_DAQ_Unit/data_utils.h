/** @file data_utils.h
* @brief Contains insertion sort and averaging algorithms
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef data_utils_h__
#define data_utils_h__

#include "config.h"

void data_insertion_sort_uint16(uint16_t *data, uint16_t data_len);
void data_2n_average(uint16_t *data, uint16_t data_len);
void data_copy_uint16(uint16_t *data_from, uint16_t *data_to, uint16_t data_len);

#endif // data_utils_h__