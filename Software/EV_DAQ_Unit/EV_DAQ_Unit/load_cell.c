/** @file load_cell.c
*
* @brief A description of the module's purpose.
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved.
*/

#include "load_cell.h"

/*!
* @brief Identify the larger of two 8-bit numbers.
* @param[in] uint8_t lc_adc_mux    Load Cell channel to read
* @return int8_t
*/
uint16_t lc_get(uint8_t lc_adc_mux) {
    // Local variables
    static uint16_t lc_raw[LC_RAW_LEN] = {0};       // Stores raw values read from ADC
    static uint16_t lc_trim[LC_TRIM_LEN] = {0};     // Stores trimmed values read from ADC
    
    adc_read(lc_adc_mux, lc_raw, LC_RAW_LEN);               // Get LC_RAW_LEN values from ADC
    data_insertion_sort_uint16(lc_raw, LC_RAW_LEN);    // Sort raw values from lowest to highest
    data_trim_uint16(lc_raw, lc_trim, LC_RAW_LEN, LC_TRIM_VAL);     // Eliminate 2 highest and 2 lowest values in array
    return(data_2n_average_uint16(lc_trim, LC_TRIM_LEN));      // Average and return array
}
