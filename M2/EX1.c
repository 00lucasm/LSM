#include <msp430.h>

#define TRUE    1;
#define FALSE   0;

void io_setup(){
    P2DIR &= 
}

int main(void){

    WDTCTL = WDTPW | WDTHOLD;

    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;

    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    while(1){
        if(!(P2DIR & BIT1)){
            P4OUT ^= BIT7;
        }
    }
}
