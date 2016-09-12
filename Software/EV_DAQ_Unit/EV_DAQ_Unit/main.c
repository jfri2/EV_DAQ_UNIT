/*
 * EV_DAQ_Unit.c
 *
 * Created: 9/5/2016 11:13:18 AM
 * Author : John
 */ 

#define F_CPU 16000000

#define I2C_SCL_FREQ    100000
#define I2C_DEV_ADDR    0b00000001

#define UART_BAUD       115200

#define HE_DDR
#define HE_PORT
#define HE_1
#define HE_2
#define HE_3

#define LED_DDR
#define LED_PORT
#define LED_RED
#define LED_GRN

#include <avr/io.h>
// #include "gpio.h"
// #include "i2c.h"
// #include "adc.h"
// #include "serial.h"
// #include "timer.h"
// #include "lcd.h"
// #include "ftdi.h"
// #include "hall_effect.h"
// #include "pushbuttons.h"
// #include "load_cell.h"
// #include "leds.h"
// #include "config.h"

uint8_t my_i2c_data[] = {0xDE, 0xAD, 0xBE, 0xEF};

int main(void) {
    /* Replace with your application code */
    i2c1_init(I2C_SCL_FREQ);
    while (1) {
        i2c1_write(I2C_DEV_ADDR, my_i2c_data, sizeof(my_i2c_data));
        // Stuff
        
    }
}

