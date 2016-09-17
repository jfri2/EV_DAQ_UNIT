/** @file load_cell.c
*
* @brief Various functions for reading and interpreting data pertaining to the TODO Load Cell
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved.
*/

#include "load_cell.h"

/*!
* @brief Get processed ADC value from Load Cell
* @param[in] uint8_t lc_adc_mux    Load Cell channel to read
* @return uint16_t
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

/*!
* @brief Get processed ADC value from Load Cell
* @param[in] uint8_t lc_adc_mux    Load Cell channel to read
* @return uint16_t
*/
uint16_t lc_adc2force(uint16_t adc_val) {
    return(0);
}

/*!
* @brief Get processed ADC value from Load Cell
* @param[in] uint8_t lc_adc_mux    Load Cell channel to read
* @return uint16_t
*/
uint16_t lc_force2torque(uint16_t force_val) {
    return(0);
}

// TODO Define functions for getting actual force & torque from load cell reads