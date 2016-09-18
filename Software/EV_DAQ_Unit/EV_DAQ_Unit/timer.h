/** @file timer.h
*
* @brief Driver for ATMEGA328PB timers
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef timer_h__
#define timer_h__

#include "EV_DAQ_Unit.h"

#ifndef F_CPU
#error "Define F_CPU in EV_DAQ_Unit.h"
#endif

#if ((F_CPU != 16000000) && (F_CPU != 16000000L) && (F_CPU != 16000000UL))
#error "F_CPU does not equal 16 MHz"
#endif

/* Definitions */
#define TIMER1_PRESCALE_MASK  ((1<<CS11) | (1<<CS10))

/* Global Variables */
extern uint32_t systck;         // This will only overflow after ~50 days of being on
extern uint16_t systime_ms;
extern uint8_t systime_s;
extern uint8_t systime_m;
extern uint8_t systime_h;
extern uint16_t systime_d;

/*!
* @brief Enable timer1 and timer1 interrupts
* @return void
*/
inline void timer1_enable(void) {
    TIMSK1 |= (1<<OCIE1A);  // Enable Output Compare Interrupt on Match A
    TCCR1B |= TIMER1_PRESCALE_MASK; // Enable timer1 clock source (disables timer)
}

/*!
* @brief Disable timer1 and timer1 interrupts
* @return void
*/
inline void timer1_disable(void) {
    TIMSK1 &= ~(1<<OCIE1A); // Disable Output compare Interrupt on Match A
    TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10)); // Disable timer1 clock source (disables timer)
}

void timer1_1ms_init(void);

#endif // timer_h__