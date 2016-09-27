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
    timer1_1ms_init();
    gpio_init();
    tbit(LED_PORT, LED_GRN);

    while(1) {
        // Status LED blink
        _delay_ms(500);
        tbits(LED_PORT, ((1<<LED_GRN)|(1<<LED_RED)));     
         
        // Reset LCD & blink LEDs fast if a button is pressed
        if((chkbit(SW_PIN, SW1) == 0) || (chkbit(SW_PIN, SW2) == 0)) {
            clrbit(LCD_RST_PORT, LCD_RST);
            _delay_ms(100);
            sbit(LCD_RST_PORT, LCD_RST);
            _delay_ms(100);
            tbits(LED_PORT, ((1<<LED_GRN)|(1<<LED_RED)));
            _delay_ms(100);
            tbits(LED_PORT, ((1<<LED_GRN)|(1<<LED_RED)));
            _delay_ms(100);
            tbits(LED_PORT, ((1<<LED_GRN)|(1<<LED_RED)));
         }
        // TODO Test & Everything else
        // TODO Add state machine for general program flow
    }
}
