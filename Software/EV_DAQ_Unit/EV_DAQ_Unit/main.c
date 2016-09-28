/*
 * EV_DAQ_Unit.c
 *
 * Created: 9/5/2016 11:13:18 AM
 * Author : John
 */ 
#include "EV_DAQ_Unit.h"

#define PRINT_PROJECT_HEADER(interface) { fprintf(interface, "\n==============================================");\
                                          fprintf(interface, "\n                   DEBUG BUILD                ");\
                                          fprintf(interface, "\n                                              ");\
                                          fprintf(interface, "\n----ELECTRIC VEHICLE DATA ACQUISITION UNIT----");\
                                          fprintf(interface, "\n                                              ");\
                                          fprintf(interface, "\n    COPYRIGHT NOTICE: (c) 2016 John Fritz     ");\
                                          fprintf(interface, "\n==============================================\n"); }
                                
#define PRINT_SYSTIME(interface)        { fprintf(interface, "\n%d %02d:%02d:%02d:%03d    ", systime_d, systime_h, systime_m, systime_s, systime_ms); }

uint16_t lc_adc_val = 0;
uint8_t lcd_temp[] = { 0x40, 0x46, 0x72, 0x69, 0x74, 0x7a }; // Sets line 1, Print "FRITZ"

int main(void) {
    /* Initialization Routines */
    sei();
    gpio_init();
    timer1_1ms_init();
    i2c1_init(F_CPU, I2C_SCL_FREQ);
    lcd_init();
    tbit(LED_PORT, LED_YLW);

    while(1) {
        // Status LED blink
        delay(500);
        tbits(LED_PORT, ((1<<LED_YLW)|(1<<LED_RED)));     
        
        // Blink LEDs fast while SW2 is pressed 
        while((chkbit(SW_PIN, SW2) == 0)) {
            tbits(LED_PORT, (LED_ALL));
            delay(100);
        }
        
        // Blink LEDs faster while SW1 is pressed
        while((chkbit(SW_PIN, SW1) == 0)) {
            tbits(LED_PORT, (LED_ALL));
            delay(50);
        }        
                 
        // TODO Test & Everything else
        // TODO Add state machine for general program flow
    }
}
