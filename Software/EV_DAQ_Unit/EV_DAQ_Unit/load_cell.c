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

/* Load Cell Specs 
*   10 V excitation, 3mV/V
*   Default torque arm length = 0.25 meters
*   200 lbs = 30 mV * 100(Av) = 3 V
*   3V / 1024 = .00292969 V per bit (+/- 2 LSB absolute accuracy)
*   200 lbsf / 1024 = 0.1953125 lbsf per bit (+/- 2 LSB absolute accuracy)
*   889.6443 N / 1024 = 0.86879326 N per bit (+/- 2 LSB absolute accuracy)
*/         



/*!
* @brief Calculate force (Newtons)
* @param[in] float adc_val    10 bit value from ADC
* @return float
*/
float lc_adc2force(uint16_t adc_val) {
    return((float)(adc_val * 0.86879));
}

/*!
* @brief Calculates torque
* @param[in] float force_val  Force value
* @param[in] float t_len      Length of torque arm
* @return float
*/
float lc_force2torque(float force_val, float t_len) {
    return(force_val * t_len);
}

// TODO Define functions for getting actual force & torque from load cell reads