/** @file adc.c
*
* @brief ATMEGA328PB internal Analog to Digital Converter driver
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved.
*/

#include "adc.h"
#include "timer.h"

/*!
* @brief Initialize (enable) ADC with prescalar
* @param[in] adc_dig_disable  Digital input disable mask. ADC7=Bit7, ADC0=Bit0
* @param[in] adc_div          ADC prescalar (clock divider)
* @return void
*/
void adc_init(uint8_t adc_dig_disable, uint8_t adc_div) {
    DIDR0 = adc_dig_disable;    // Disable digital input buffer (saves power and causes PIN to always read 0)
    if(adc_div > ADC_DIV_128) {
        adc_div = ADC_DIV_128;    // Handle invalid prescalars by forcing to 128 division 
    }   
         
    ADCSRA = ((1<<ADEN) | (adc_div));   // Enable ADC and set proper prescale
}

/*!
* @brief Read one value from ADC
* @param[in] adc_mux   ADC channel to read
* @return void
*/
uint16_t adc_read_one(uint8_t adc_mux) {
    uint16_t adc_val = 0;
    static uint8_t adc_last_adcmux;     // Holds adc_mux value from previous function call
    
    if(adc_last_adcmux != adc_mux) {    // Check if sequential function calls use same ADC channel
        ADMUX = adc_mux;    // Set new ADMUX value
        for(uint8_t i=0; i < ADC_BAD_CONVERSIONS; i++) {
            /* Throw out first few conversions */
            ADCSRA |= (1<<ADSC);    // start ADC conversion.
            while(ADCSRA & (1<<ADSC)); // wait for conversion complete
        }
    }
    
    ADCSRA |= (1<<ADSC);   // Start ADC conversion
    while(ADCSRA & (1<<ADSC));  // Wait until conversion is complete (13 adc clock cycles)
    adc_val = ADCL;         // Read & store lower byte of adc result
    adc_val = (ADCH<<8);    // Read & store upper two bits of adc result
    
    return(adc_val);
}

/*!
* @brief Read multiple values from ADC
* @param[in] adc_mux    ADC channel to read
* @param[in] *adc_val   Pointer to location to store data read from ADC
* @param[in] *adc_val_len   Length of adc_val (number of reads to perform)
* @return void
*/
void adc_read(uint8_t adc_mux, uint16_t *adc_val, uint16_t adc_val_len) {
    for(uint16_t i=0; i < adc_val_len; i++) {
        adc_val[i] = adc_read_one(adc_mux);
    }
}
