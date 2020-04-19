#include "IOSetup.h"
#include "pwm.h"
#include "Timer1Function.h"
#include "p30F4011.h"


void configUART(void){
    U2MODEbits.UARTEN = 0;       // Disable the UART
    U2BRG = 16;                  // setting the baud rate
    U2MODEbits.LPBACK = 0;       // disable loop-back mode 
    U2MODEbits.WAKE = 0;         // ignore serial activity
    U2MODEbits.ABAUD = 0;        // no auto-baud connection
    U2MODEbits.PDSEL = 0b00;     // transmit 8bit, no parity bits
    U2MODEbits.STSEL = 0;        // use 1 stop bit
    U2STAbits.URXISEL = 0;       // receive interrupt when 1 character arrives
    IFS1bits.U2RXIF = 0;         // UART Receive interrupt flag
    _U2RXIP = 3;                 // Set priority for receiving interrupts
    _U2RXIE = 1;                 // Enable receiving interrupts
    U2MODEbits.UARTEN = 1;       // enable UART
    U2STAbits.UTXEN = 1;         // enable transmit 
    
}


void __attribute__((interrupt, auto_psv)) _U2RXInterrupt(void){
    IFS1bits.U2RXIF = 0;  //set flag to 0
    
    U2RXREGbits.URX8 = 0; // clear the TX buffer   
}