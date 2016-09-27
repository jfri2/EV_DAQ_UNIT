/** @file timer.c
*
* @brief Driver for ATMEGA328PB timers
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved.
*/

#include "timer.h"

/* systck (Global) Definitions */
volatile uint32_t systck = 0;
volatile uint16_t systime_ms = 0;
volatile uint8_t systime_s = 0;
volatile uint8_t systime_m = 0;
volatile uint8_t systime_h = 0;
volatile uint16_t systime_d = 0;

ISR(TIMER1_COMPA_vect) {
    /* Increment systck global vars to keep system time */
    systck++;
    systime_ms++;
    if(systime_ms >= 1000) {
        systime_ms = 0;
        systime_s++;
        if(systime_s >= 60) {
            systime_s = 0;
            systime_m++;
            if(systime_m >= 60) {
                systime_m = 0;
                systime_h++;
                if(systime_h >= 24) {
                    systime_h = 0;
                    systime_d++;
                }
            }
        }        
    }
}

/*!
* @brief Initialize timer1 for 1ms interrupts
* @return void
*/
void timer1_1ms_init(void) {
    static uint16_t timer1_1ms_compare_value = 250-1;
        
    timer1_disable();
    TCCR1A = 0x00;  // Make sure no pins are set to output
    TCCR1B |= (1<<WGM12) | TIMER1_PRESCALE_MASK;  // Set CTC, prescalar to clk(io)/64 (250 counts per 1ms)
    OCR1A = timer1_1ms_compare_value;    
    timer1_enable();
}

/*!
* @brief Delay milliseconds
* @param uint16_t delay_ms  Time to delay in milliseconds
* @return void
*/
void delay(uint16_t delay_ms) {
    uint32_t systck_1 = systck;
    while(systck < (systck_1 + delay_ms));  // delay
}