/** @file uart.c
*
* @brief Serial UART driver for ATMEGA328PB with stdio
*
* @par
* COPYRIGHT NOTICE: (c) 2016 John Fritz
* All rights reserved.
*/

#include "uart.h"
#include "timer.h"

/*!
* @brief Initialize uart0
* @param[in] uint32_t cpu_freq      Frequency of CPU in Hz
* @param[in] uint32_t uart_baud     Desired UART baud rate
* @param[in] bool b_flow_ctrl    HW Flow control used? (T/F)
* @return void
*/
void uart0_init(uint32_t cpu_freq, uint32_t uart_baud, bool b_flow_ctrl) {    
    // Set UART0 to no parity, 8 data bits, 1 stop bit
    // Enable Tx & Rx UART
    UCSR0A = 0x00;
    UCSR0B = 0x18;
    UCSR0C = 0x06;
    
    // Set UART0 Baud Rate
    UBRR0H = (((cpu_freq/uart_baud)/32)-1)>>8;  // Set baud rate div (upper register)
    UBRR0L = (((cpu_freq/uart_baud)/32)-1);     // Set baud rate div (lower register)   
    
    // Initialize hardware flow control gpio
    if(b_flow_ctrl != FALSE) {
        UART_DDR |= UART_RTS;   // Set UART RTS as output
        UART_DDR &= ~UART_CTS;  // Set UART CTS as input
        UART_PORT |= (UART_CTS | UART_RTS);  // Turn CTS pullup resistors on, tells host cannot accept data
    }
}

/*!
* @brief Write byte over UART0
* @param[in] uint8_t ch     Byte to write
* @param[in] bool b_flow_ctrl    HW Flow control used? (T/F)
* @return uint8_t   0 if write operation successful, 0xFF if operation timeout
*/
uint8_t uart0_put(uint8_t ch, bool b_flow_ctrl) {
    uint32_t uart_start_ms = systck;    // Store start time of operation    
    
    if(b_flow_ctrl) {
        /* Flow Control Implementation */
        UART_ASSRT_RTS();     // Send request to send signal        
        while(UART_GET_CTS() == 0) {      // Wait for clear to send signal from downstream device (active low)
            if(systck > (uart_start_ms + UART_TOUT_MS)) {
                return(0xFF);   // Break from function and return error if timeout
            }
        }
        while((UCSR0A & (1<<UDRE0)) == 0x00);    // Wait until tx buffer is empty
        UDR0 = ch;      // Load tx buffer with character to send
        UART_DSSRT_RTS();     // De-assert RTS signal
        return(0);  // Return successful write                       
    } else {
        /* Normal Implementation */
        while((UCSR0A & (1<<UDRE0)) == 0x00) {      // Wait until tx buffer is empty
            if(systck > (uart_start_ms + UART_TOUT_MS)) {
               return(0xFF);    // Break from function and return error if timeout
            }
        }                           
        UDR0 = ch;      // Load tx buffer with character to send
        return(0);  // Return successful write
    }        
}

/*!
* @brief Send uint8_t array over UART0
* @param[in] uint8_t *ch      Pointer to array to send
* @param[in] uint8_t ch_len   Length of array
* @param[in] bool b_flow_ctrl    HW Flow control used? (T/F)
* @param[out] uint8_t   Return 0 if operation successful, 0xFF if unsuccessful
*/
uint8_t uart0_puts(uint8_t *ch, uint8_t ch_len, bool b_flow_ctrl) {
    uint8_t r_val = 0;    
    
    for(uint8_t i=0; i < ch_len; i++) {
        r_val |= uart0_put(ch[i], b_flow_ctrl);
        if(r_val != 0) return(0xFF);    // Break from function if a write was unsuccessful
    }        
    return(r_val);
}

/*!
* @brief Get uint8_t over UART0
* @return uint8_t   Value from UART0
* @param[in] bool b_flow_ctrl    HW Flow control used? (T/F)
*/
uint8_t uart0_get(bool b_flow_ctrl) {
    if(b_flow_ctrl != FALSE) {
        // TODO
        while((UCSR0A & (1<<RXC0)) == 0x00);    // Wait until rx char flag is set
        return(UDR0);
    } else {
        while((UCSR0A & (1<<RXC0)) == 0x00);    // Wait until rx char flag is set
        return(UDR0);           
    }
}

/*!
* @brief Get uint8_t array over UART0
* @param[in] uint8_t *ch      Pointer to array to store
* @param[in] uint8_t ch_len   Length of array
* @param[in] bool b_flow_ctrl    HW Flow control used? (T/F)
* @return void
*/
void uart0_gets(uint8_t *ch, uint8_t ch_len, bool b_flow_ctrl) {
    for(uint8_t i=0; i < ch_len; i++) {
        ch[i] = uart0_get(b_flow_ctrl);
    }
}
