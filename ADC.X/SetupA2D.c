#include "IOSetup.h"
#include "PWM.h"
#include "Timer1Function.h"
#include "p30F4011.h"

void setupA2D(void){
    ADCON1bits.ADON = 0; //switch the A2D converter off during configuration
    //configure the analog input
    //the default state of the TRIS register is 1, i.e. they are inputs
    //additionally we configure the ports we are going to use in the
    //A2D peripheral
    ADPCFG = 0xffff; //make all of them digital
    //and then select the ones we use in analog mode
    ADPCFGbits.PCFG0 = 0; //we use analog input 0
    ADPCFGbits.PCFG1 = 0; // and analog input 1
    //we now need configure the "scan sequence", we set the whole register
    ADCSSL = 0x0003; //select scanned channels: 0b 0000 0000 0000 0011
    ADCON2bits.CSCNA = 1; //this enables the scanning
    //we will sample those channels in (close) sequence
    //and connect the negative input of the s&h to VrefADCHSbits.CH0NA=0;
    ADCHSbits.CH0SA = 0b0000; //we scan through the other channels,
    //so this does not matter
    ADCON1bits.SIMSAM = 0; //no simultaneous sampling
    ADCON2bits.CHPS = 0b00; //and we only sample and hold unit 0 (Ch0)
    ADCON2bits.SMPI = 0b0001; // generate an interrupt after conversion of
    //two channels (0b0001 + 1)
    //select the conversion clock
    ADCON2bits.ALTS = 0; //always use multiplexer settings A, i.e. scanning through inputs
    ADCON2bits.BUFM = 0; //the conversion buffer is selected to use all 16 words
    //(not 2 x 8 words)
    ADCON2bits.VCFG = 0b000; //this selects the AVdd and AVss as voltage reference
    ADCON1bits.FORM = 0b00; //we use the (unsigned) integer format for the A2D value
    ADCON3bits.ADRC = 0; //clock is derived from internal clock;
    //Tad needs to be selected and must be a minimum of 83.33 ns
    //we derive Tad from Tcyc ==> Tad=32xTcyc = 2us
    ADCON3bits.ADCS = 0b111111; //sets the conversion period to 32 x Tcyc (slowest possible)
    ADCON3bits.SAMC = 0b11111; // sets the auto sample speed to 32xTad ==> slowest setting
    //we need to select the source to start a conversion
    ADCON1bits.SSRC = 0b111; //conversion (not sampling) is started with A2D clock
    //afer SAMC (see above) cycles
    ADCON1bits.SAMP = 1; //we are ready for sampling
    ADCON1bits.ASAM = 0; //we start the auto-sampling in the timer ISR
    //lets now enable the interrupt and set the priority
    IFS0bits.ADIF = 0; //clear the interrupt flag (in case it was on)
    IPC2bits.ADIP = 5; // lets set the A2D priority to 5;
    IEC0bits.ADIE = 1; //enable a2d interrupts
    //finally, we switch on the A2D converter again
    ADCON1bits.ADON = 1; //ready to convert!
}
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void){
    float potentiometer;
    unsigned int temperature;
    IFS0bits.ADIF = 0; //reset the interrupt flag
    ADCON1bits.ASAM = 0; //stop the sampling
    //now read the data from the buffers ADCBUF0, ADCBUF1 etc.
    potentiometer = ADCBUF0; //get the result
    temperature = ADCBUF1;
    
    /*
    if (potentiometer >= 716){
        LED2Latch = 1;
    } else if (potentiometer <= 307) {
        LED2Latch = 0;
    }
    */ 
    
    // PDC1 = (potentiometer * (32000/1023));
    
    
}
