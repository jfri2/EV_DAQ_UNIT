/** @file config.h
* @brief Configuration file for EV_DAQ_Unit project
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved
*/

#ifndef config_h__
#define config_h__

// Clock Definitions
#define F_CPU           16000000

// I2C & LCD Definitions
#define I2C_SCL_FREQ    100000
#define LCD_DEV_ADDR    0b00000001
#define LCD_RST_DDR     DDRB
#define LCD_RST_PORT    PORTB
#define LCD_RST         (1<<PORTB2)

// UART & FTDI Definitions
#define UART_BAUD       115200
#define UART_DDR        DDRD
#define UART_PORT       PORTD
#define UART_RTS        (1<<PORTD2)
#define UART_CTS        (1<<PORTD3)

// Hall Effect Definitions
#define HE_DDR          DDRC
#define HE_PORT         PORTC
#define HE_1            (1<<PORTC3)
#define HE_2            (1<<PORTC4) 
#define HE_3            (1<<PORTC5)
#define ADC_NC_MASK     ((1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2))  // NC (no connect) pins
#define ADC_DIG_DIS_HE  ((1<<ADC0D) | (1<<ADC1D) | (1<<ADC2D))     // NC pin ADC channels (used to disable digital input buffers)

// LED Definitions
#define LED_DDR         DDRD
#define LED_PORT        PORTD
#define LED_RED         (1<<PORTD6)
#define LED_GRN         (1<<PORTD7)

// Switch (Pushbutton) Definitions
#define SW_DDR          DDRB
#define SW_PORT         PORTB
#define SW_1            (1<<PORTB0)
#define SW_2            (1<<PORTB1)


/* AVR Functions & Definitions*/
#include <avr/io.h>
#include <avr/interrupt.h>

/* Utilities */
#include "data_utils.h"

/* Project Drivers */
#include "gpio.h"
#include "i2c.h"
#include "adc.h"
#include "uart.h"

/* Project Driver & Component Combinations */
#include "timer.h"

/* Project Components */
#include "lcd.h"
#include "ftdi.h"
#include "hall_effect.h"
#include "pushbuttons.h"
#include "load_cell.h"
#include "leds.h"
#include "print.h"

/* Global Variables */
extern uint32_t systck;         // This will only overflow after ~50 days of being on
extern uint16_t systime_ms;
extern uint8_t systime_s;
extern uint8_t systime_m;
extern uint8_t systime_h;
extern uint16_t systime_d;

#endif // config_h__