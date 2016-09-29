/*
 * EV_DAQ_Unit.c
 *
 * Created: 9/5/2016 11:13:18 AM
 * Author : John
 */ 
#include "EV_DAQ_Unit.h"

#define PRINT_PROJECT_HEADER(interface) { fprintf(interface, "\n==============================================");\
                                          fprintf(interface, "\n    ELECTRIC VEHICLE DATA ACQUISITION UNIT    ");\
                                          fprintf(interface, "\n                                              ");\
                                          fprintf(interface, "\n                  Version 0.1                 ");\
                                          fprintf(interface, "\n    COPYRIGHT NOTICE: (c) 2016 John Fritz     ");\
                                          fprintf(interface, "\n               github.com/jfri2               ");\
                                          fprintf(interface, "\n==============================================\n"); }
                                
#define PRINT_SYSTIME(interface)        { fprintf(interface, "\n%d %02d:%02d:%02d:%03d    ", systime_d, systime_h, systime_m, systime_s, systime_ms); }

uint16_t adc_val = 0;
uint8_t adc_str[16];
volatile uint32_t systck_tmp = 0;
volatile uint16_t adc_ms = 0;
uint8_t time_str[16];

int main(void) {
    /* Initialization Routines */
    sei();
    timer1_1ms_init();
    gpio_init();
    adc_init(ADC_DIG_DIS_LC, ADC_DIV_128, ADC_REF_AREF);  // Currently disables all digital i/o on all ADC pins, set external 3V reference
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
        
        // Read temperature sensor on ADC and display values on SW1 activation
        if((chkbit(SW_PIN, SW1) == 0)) {
            
            /* Get values to display on screen */
            systck_tmp = systck;   // Store current systck value
            adc_val = lc_get(ADC_MUX_ADC7);    // Read 40 Hz output from analog front end
            //adc_val = adc_read_one(ADC_MUX_ADC7);
            adc_ms = ((uint16_t)(systck - systck_tmp));  // Save time (in milliseconds) it took to do A/D conversion
                    
            /* Format to ASCII strings */
            sprintf(adc_str,  "ADC:  %04d", adc_val);
            sprintf(time_str, "Time: %04d ms", adc_ms);
                    
            /* Print ADC & time values on screen */
            lcd_clear();
            lcd_set_line1();
            lcd_write(LCD_DATA, adc_str, 16);
            lcd_set_line2();
            lcd_write(LCD_DATA, time_str, 16);
        }           
                 
        // TODO Test & Everything else
        // TODO Add state machine for general program flow
    }
}
