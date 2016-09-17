/** @file adc.h
* @brief ATMEGA328PB internal Analog to Digital Converter driver
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef adc_h__
#define adc_h__

#include <avr/io.h>

#define ADC_REF_AREF            0x00
#define ADC_REF_AVCC            0x01
#define ADC_REV_1V1             0x03

#define ADC_MUX_ADC0            0x00
#define ADC_MUX_ADC1            0x01
#define ADC_MUX_ADC2            0x02
#define ADC_MUX_ADC3            0x03
#define ADC_MUX_ADC4            0x04   
#define ADC_MUX_ADC5            0x05
#define ADC_MUX_ADC6            0x06
#define ADC_MUX_ADC7            0x07
#define ADC_MUX_TEMP            0x08
#define ADC_MUX_1V1             0x0F
#define ADC_MUX_GND             0x0E

#define ADC_DIV_2               0x01
#define ADC_DIV_4               0x02
#define ADC_DIV_8               0x03
#define ADC_DIV_16              0x04
#define ADC_DIV_32              0x05
#define ADC_DIV_64              0x06
#define ADC_DIV_128             0x07

#define ADC_BAD_CONVERSIONS     0x03    // Number of ADC conversions to throw out after switching ADC mux values   

void adc_init(uint8_t adc_dig_disable, uint8_t adc_div);
uint16_t adc_read_one(uint8_t adc_mux);
void adc_read(uint8_t adc_mux, uint16_t *adc_val, uint16_t adc_val_len);

#endif // adc_h__