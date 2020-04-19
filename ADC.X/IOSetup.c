#include "IOSetup.h"



/* a function to configure the tristates to allow the LEDs to be outputs and 
 * the switch to be an input.*/
 void IOSetup(void){
        SW3Tris  =  1;
        LED2Tris =  0;
        LED3Tris =  0;
       
    } 