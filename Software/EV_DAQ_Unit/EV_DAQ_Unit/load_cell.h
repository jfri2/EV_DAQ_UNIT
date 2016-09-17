/** @file load_cell.h
* @brief Various functions for reading and interpreting data pertaining to the TODO Load Cell
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef load_cell_h__
#define load_cell_h__

#include "EV_DAQ_Unit.h"

// Load Cell Definitions
#define ADC6D           6
#define ADC7D           7
#define ADC_DIG_DIS_LC  ((1<<ADC6D) | (1<<ADC7D))
#define LC_ADC_8K       ADC_MUX_ADC6
#define LC_ADC_40       ADC_MUX_ADC7
#define LC_RAW_LEN      20      // Length of "raw" array (outliers included)
#define LC_TRIM_LEN     16      // Length of "trimmed" array (outliers excluded), must be power of 2
#define LC_TRIM_VAL     ((LC_RAW_LEN - LC_TRIM_LEN) / 2)    // Values to trim from start and end of array

// Macros & Functions
#define lc_get_one(lc_adc_mux)  { adc_read(lc_adc_mux); }
uint16_t lc_get(uint8_t lc_adc_mux);

// TODO Add functions for getting actual force & torque from load cell reads

#endif // load_cell_h__