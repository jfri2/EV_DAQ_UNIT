/*
 * EV_DAQ_Unit.c
 *
 * Created: 9/5/2016 11:13:18 AM
 * Author : John
 */ 

#include "config.h"

#define PRINT_PROJECT_HEADER()  printf("\n==============================================");\
                                printf("\n                   DEBUG BUILD                ");\
                                printf("\n                                              ");\
                                printf("\n----ELECTRIC VEHICLE DATA ACQUISITION UNIT----");\
                                printf("\n                                              ");\
                                printf("\n    COPYRIGHT NOTICE: (c) 2016 John Fritz     ");\
                                printf("\n==============================================\n")
                                
#define PRINT_SYSTIME() printf("\n%d %02d:%02d:%02d:%03d    ", systck_d, systck_h, systck_m, systck_s, systck_ms);

int main(void) {
    /* Initialization Routines */
    timer1_1ms_init();
    uart0_init(F_CPU, UART_BAUD);
    i2c1_init(F_CPU, I2C_SCL_FREQ);
    adc_init((ADC_DIG_DIS_LC | ADC_DIG_DIS_HE), ADC_DIV_128);
    
    PRINT_PROJECT_HEADER();
    
    while (1) {
        PRINT_SYSTIME();
    }
}
