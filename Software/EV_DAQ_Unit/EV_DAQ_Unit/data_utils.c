/** @file data_utils.c
*
* @brief Contains insertion sort and averaging algorithms
*
* @par
* COPYRIGHT NOTICS: (c) 2016 John Fritz
* All rights reserved.
*/

#include "data_utils.h"

/*!
* @brief Insertion sort for uint16 array where max length is 65535 (2^16-1)
* @param[in] uint16_t *data     Pointer to array that contains data to average
* @param[in] uint16_t data_len  Length of data array
* @return void
*/
void data_insertion_sort_uint16(uint16_t *data, uint16_t data_len) {
    uint16_t i = 0;
    int32_t j = 0;
    uint16_t temp = 0;

    for(i=1; i < data_len; i++) {
        temp = data[i];
        j = i - 1;
        while((temp < data[j]) && (j >= 0)) {
            data[j+1] = data[j];
            j = j - 1;
        }
        data[j+1] = temp;
    }
}

/*!
* @brief Average a uint16 array of 2^n length where max length is 65535 (2^16-1)
* @param[in] uint16_t *data     Pointer to array that contains data to average
* @param[in] uint16_t data_len  Length of data array
* @return uint16_t   Data average over entire array length. Returns 0xFFFF if array is not power of 2. 
*/
uint16_t data_2n_average_uint16(uint16_t *data, uint16_t data_len) {
    uint32_t avg_acc = 0;               // Accumulator for data averaging
    uint16_t pow2_val = 1;              // Power of two to check length of array and calculate dividing factor
    uint8_t pow2_div = 0;               // Power of two divider
    uint16_t pow2_max_val = 0xFFFF;     // Maximum value for an 16-bit unsigned integer
    
    /* Check to see how long it is */
    if(data_len <= 1) { 
        return(data[0]); // Break from function if not more than one data point 
    }      
        
    /* Sum entire array */
    for(uint16_t i = 0; i < data_len; i++) {
        avg_acc += data[i];
    }
    
    /* Find power2_div where 2^power2_div is length of array */
    while((pow2_val < data_len) && (pow2_val <= pow2_max_val)) {
        pow2_val *= 2;  // Increment pow2_val by next power of 2
        pow2_div++;     // Increment divider by one
    }
    
    /* Break from function and return 0xFFFF if array is actually not a power of 2 */
    if(pow2_val != data_len) {
        return(0xFFFF);
    }

    /* Average and return accumulated value */
    return((uint16_t)(avg_acc >> pow2_div));
}