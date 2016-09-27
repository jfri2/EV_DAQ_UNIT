/*
 * EV_DAQ_Unit.c
 *
 * Created: 9/5/2016 11:13:18 AM
 * Author : John
 */ 
#include "EV_DAQ_Unit.h"
#include "util/delay.h"

#define PRINT_PROJECT_HEADER(interface) { fprintf(interface, "\n==============================================");\
                                          fprintf(interface, "\n                   DEBUG BUILD                ");\
                                          fprintf(interface, "\n                                              ");\
                                          fprintf(interface, "\n----ELECTRIC VEHICLE DATA ACQUISITION UNIT----");\
                                          fprintf(interface, "\n                                              ");\
                                          fprintf(interface, "\n    COPYRIGHT NOTICE: (c) 2016 John Fritz     ");\
                                          fprintf(interface, "\n==============================================\n"); }
                                
#define PRINT_SYSTIME(interface)        { fprintf(interface, "\n%d %02d:%02d:%02d:%03d    ", systime_d, systime_h, systime_m, systime_s, systime_ms); }

uint16_t lc_adc_val = 0;
uint32_t systck_1 = 0;
uint8_t lcd_temp[] = { 0x40, 0x46, 0x72, 0x69, 0x74, 0x7a }; // Sets line 1, Print "FRITZ"

int main(void) {
    /* Initialization Routines */
//    timer1_1ms_init();
//    uart0_init(F_CPU, UART_BAUD, TRUE);
    i2c1_init(F_CPU, I2C_SCL_FREQ);
//    adc_init((ADC_DIG_DIS_LC | ADC_DIG_DIS_HE), ADC_DIV_128);
//    lcd_init();
    DDRB |= (1<<PB2);
    DDRB &= ~((1<<PB0)|(1<<PB1));
    PORTB |= (1<<PB2)|(1<<PB1)|(1<<PB0);
    _delay_ms(10);
    PORTB &= ~(1<<PB2);
    PORTB |= (1<<PB2);
    _delay_ms(10);
    lcd_test();
    DDRD |= (1<<PD6)|(1<<PD7);       
    while(1) {
//         systck_1 = systck;
//         while(systck < (systck_1 + 500));

        // Status LED blink
        _delay_ms(500);
        PORTD ^= (1<<PD6)|(1<<PD7);       
         
        // Reset LCD if a button is pressed
        if(PINB & ~((1<<PB1)|(1<<PB0))) {
            PORTB &= ~(1<<PB2);
            _delay_ms(10);
            PORTB |= (1<<PB2);
        }
        //i2c1_write(LCD_I2C_ADDR, lcd_temp, 6);
        // TODO Test & Everything else
        // TODO Add state machine for general program flow
    }
}
