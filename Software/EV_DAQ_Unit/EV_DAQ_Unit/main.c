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

#define MAX_MILLI_NEWTONS   845162    // Used to indicate warning to operator. Equivalent to 190 pounds

uint16_t adc_val = 0;
uint8_t adc_str[16];
volatile uint32_t systck_tmp = 0;
volatile uint16_t adc_ms = 0;
uint8_t time_str[16];
float force = 0;
int milliforce = 0;
uint32_t systime_1 = 0;

uint8_t get_temp_raw(void) {
    uint8_t admux_old = ADMUX;  // Store last version of ADMUX
    
    ADMUX = ADC_REF_1V1 & 0b11000000;   // Set ADC Ref to internal 1.1 Vref
    adc_init(ADC_DIG_DIS_LC, ADC_DIV_128, ADC_MUX_1V1);
    adc_val = lc_get(ADC_MUX_1V1);
    ADMUX = admux_old;   // Reset ADMUX to what it was before
    return(adc_val);
}

int main(void) {
    /* Initialization Routines */
    sei();
    timer1_1ms_init();
    gpio_init();
    adc_init(ADC_DIG_DIS_LC, ADC_DIV_128, ADC_REF_AREF);  // Currently disables all digital i/o on all ADC pins, set external 3V reference
    i2c1_init(F_CPU, I2C_SCL_FREQ);
    lcd_init();
    delay(2000);

    while(1) {
        // Blink LEDs fast while SW2 is pressed 
        while((chkbit(SW_PIN, SW2) == 0)) {
            tbits(LED_PORT, (LED_ALL));
            delay(100);
        }        
            
        /* Get values to display on screen */
        systck_tmp = systck;   // Store current systck value
        adc_val = lc_get(ADC_MUX_ADC7);    // Read 40 Hz output from analog front end, 20 samples
        adc_ms = ((uint16_t)(systck - systck_tmp));  // Save time (in milliseconds) it took to do A/D conversion
            
        force = lc_adc2force(adc_val);    // Calculate force (Newtons)
        milliforce = force * 1000;     
        
        if(milliforce >= MAX_MILLI_NEWTONS) {
            sbit(LED_PORT, LED_RED);    // Turn on Red LED if overloaded
        } else {
            clrbit(LED_PORT, LED_RED);  // Turn off Red LED if not overloaded
        }
                           
        /* Print Force & time values on screen @ one second intervals */            
        if(systck >= (systime_1 + 1000)) {                                
            /* Format to ASCII strings */
            sprintf(adc_str, "Force: %6u mN", milliforce);      // Display Force (milliNewtons)
            sprintf(time_str, "Time:   %02d:%02d:%02d", systime_h, systime_m, systime_s);   // Display time since last reset (hh:mm:ss)
                        
            tbit(LED_PORT, LED_YLW);        // Toggle Yellow status LED every screen refresh
            
            lcd_set_line1();
            lcd_write(LCD_DATA, adc_str, 16);
            lcd_set_line2();
            lcd_write(LCD_DATA, time_str, 16);                
            systime_1 = systck;       
        }                
    }
}
