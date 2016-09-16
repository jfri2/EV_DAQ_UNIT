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
uint16_t systck_ms = 0;
uint8_t systck_s = 0;
uint8_t systck_m = 0;
uint8_t systck_h = 0;
uint16_t systck_d = 0;

ISR(TIMER1_COMPA_vect) {
    /* Increment systck global vars to keep system time */
    systck_ms++;
    if(systck_ms >= 1000) {
        systck_ms = 0;
        systck_s++;
        if(systck_s >= 60) {
            systck_s = 0;
            systck_m++;
            if(systck_m >= 60) {
                systck_m = 0;
                systck_h++;
                if(systck_h >= 24) {
                    systck_h = 0;
                    systck_d++;                    
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

