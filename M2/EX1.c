#include <msp430.h>

#define     TRUE    1;
#define     FALSE   0;

void io_setup(void);

// main loop - literally
int main(void){
    
    WDTCTL = WDTPW | WDTHOLD;

    io_setup();

    while(1){
        if((P2DIR & BIT1)){ // for each pusle, check if the switch was pressed
            P4OUT ^= BIT7; // toggle led
        }
    }
}

void io_setup(void){
    // S1 setup - P2.1 hardware mapping
    P2DIR &= ~BIT1;         // S1 is INPUT
    P2REN |= BIT1;           // enable led1 resistor
    P2OUT |= BIT1;           // set resistor as pullup resistor

    // LED2 setup - P4.7 hardware mapping
    P4DIR |= BIT7;          // set LED2 as OUTPUT
    P4OUT &= ~BIT7;         // disable LED2
}
