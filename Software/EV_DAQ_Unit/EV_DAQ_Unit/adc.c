/** @file adc.c
*
* @brief A description of the module's purpose.
*
* @par
* COPYRIGHT NOTICS: (c) 2016 John Fritz
* All rights reserved.
*/

#include "adc.h"

/*!
* @brief Initialize (enable) ADC with prescalar
* @param[in] adc_dig_disable  Digital input disable mask. ADC7=Bit7, ADC0=Bit0
* @param[in] adc_div          ADC prescalar (clock divider)
* @return void
*/
void adc_init(uint8_t adc_dig_disable, uint8_t adc_div) {
    DIDR0 = adc_dig_disable;    // Disable digital input buffer (saves power and causes PIN to always read 0)
    if(adc_div > ADC_DIV_128) adc_div = ADC_DIV_128;    // Handle invalid prescalars by forcing to 128 division 
    ADCSRA = ((1<<ADEN) | (adc_div));   // Enable ADC and set proper prescale
}

/*!
* @brief Identify the larger of two 8-bit numbers.
* @param[in] adc_mux   Bitmask for ADC channels used (to disable digital input buffers)
* @return void
*/
uint16_t adc_read(uint8_t adc_mux) {
    static uint8_t adc_last_adcmux;     // Holds adc_mux value from previous function call
    
    if(adc_last_adcmux != adc_mux) {    // Check if sequential function calls use same ADC channel
        
    }
    static uint16_t adc_val = 0;
    
    adc_val = ADCL;         // Read & store lower byte of adc result
    adc_val = (ADCH<<8);    // Read & store upper two bits of adc result
    return(adc_val);
}