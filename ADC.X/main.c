/* 
 * File:   main.c
 * Author: tm2-weber
 *
 * Created on 23 October 2019, 11:48
 */

//lets set the device configuration bits using the pre-processor macros  

//primary oscillator with 8 times pll no clock switching
#pragma config FOS = PRI
#pragma config FPR = XT_PLL8
#pragma config FCKSMEN = CSW_FSCM_OFF

//watch dog is disabled
#pragma config WDT = WDT_OFF

//brown out disabled, master-clear enabled, power on reset time = 64ms
#pragma config BOREN = PBOR_OFF
#pragma config MCLRE = MCLR_EN
#pragma config FPWRT = PWRT_64

// pwm low side is active high, pwm high side is active low, reset state controlled with HPOL/LPOL bits    
#pragma config LPOL = PWMxL_ACT_HI
#pragma config HPOL = PWMxH_ACT_LO
#pragma config PWMPIN = RST_PWMPIN

#include "IOSetup.h"



int main (void){
    IOSetup();
    InterruptSetup();
    pwmSetup();
    configUART();
    setupA2D();
    
    while(1){}
}
