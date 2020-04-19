/* 
 * File:   IOSetup.h
 * Author: tm2-weber
 *
 * Created on 23 October 2019, 11:47
 */

#include "XC.h"


#ifndef IOSETUP_H
#define	IOSETUP_H

#ifdef	__cplusplus
extern "C" {
#endif
    

    //Define bits for the LED
#define LED2Latch   LATDbits.LATD1
#define LED2Port    PORTDbits.RD1
#define LED2Tris    TRISDbits.TRISD1

    
#define LED3Latch   LATDbits.LATD3
#define LED3Port    PORTDbits.RD3
#define LED3Tris    TRISDbits.TRISD3    

   //Define bits foe the switch
#define SW3Latch    LATDbits.LATD2
#define SW3Port     PORTDbits.RD2
#define SW3Tris     TRISDbits.TRISD2
  
    //functions used in the program
    void IOSetup(void);
    void pwmSetup(void);
    void configUART(void);
    void InterruptSetup(void);
    void sendString();
    void setupA2D(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* IOSETUP_H */

