#include <msp430.h>

#define     TRUE    1;
#define     FALSE   0;
#define     OPEN    1;
#define     CLOSED  0;
#define     DBC     2000;

void io_setup(void);
void debounce(int value);

// main loop - literally
int main(void){
    
    WDTCTL = WDTPW | WDTHOLD;

    io_setup();

    while(1){
        if(!(P2IN & BIT1)){
            P4OUT ^= BIT7;
            debounce(DBC);
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

void debounce(int value){
    volatile unsigned int x;
    for(x = 0; x < value; x++);
}
