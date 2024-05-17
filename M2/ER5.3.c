// Solved exercise 5.3
#include <msp430.h>

#define TRUE    1
#define FALSE   0
#define OPEN    1           // open switch
#define CLOSED  0           // closed switch
#define DBC     2000        // debounce

int mon_s1(void);
int mon_s2(void);
void cont_leds(int ct);
void debounce(int value);
void io_setup(void);

int main(void){

    int count = 0;

    WDTCTL = WDTPW | WDTHOLD;

    io_setup();

    while(TRUE){

        while((P2IN & BIT1) == BIT1);
        debounce(DBC);
        count++;
        cont_leds(count);
        while((P2IN & BIT1) == 0);
        debounce(DBC);
        
    }
    
    return 0;

}

// monitors S1 (P2.1), returns TRUE if it has been pressed
int mon_s1(void){

    static int ps1 = OPEN;

    if((P2IN & BIT1) == 0){
        if(ps1 == OPEN){
            debounce(DBC);
            ps1 = CLOSED;
            return TRUE;
        }
    }else{
        if(ps1 = CLOSED){
            debounce(DBC);
            ps1 = OPEN;
            return FALSE;
        }
    }

    return FALSE;

}

int mon_s2(void){

    static int ps2 = OPEN;

    if((P1IN & BIT1) == 0){
        if(ps2 == OPEN){
            debounce(DBC);
            ps2 = CLOSED;
            return TRUE;
        }
    }else{
        if(ps2 == CLOSED){
            debounce(DBC);
            ps2 = OPEN;
            return FALSE;
        }
    }
    
    return FALSE;

}

void cont_leds(int ct){
    switch(ct & 3){
        case 0: // 00
            P1OUT &= ~BIT0;
            P4OUT &= ~BIT7;
            break;
        case 1: // 01
            P1OUT &= ~BIT0;
            P4OUT |= BIT7;
            break;
        case 2: // 10
            P1OUT |= BIT0;
            P4OUT &= ~BIT7;
            break;
        case 3: // 11
            P1OUT |= BIT0;
            P4OUT |= BIT7;
            break;
    }
}

void debounce(int value){
    volatile unsigned int x;
    for(x = 0; x < value; x++);
}

void io_setup(void){
    // led1 setup - P1.0 hardware mapping
    P1DIR |= BIT0;      // set led1 as OUTPUT
    P1OUT &= ~BIT0;     // disable led1

    // led2 setup - P4.7 hardware mapping
    P4DIR |= BIT7;      // set led2 as OUTPUT
    P4OUT &= ~BIT7;     // disable led2

    // s1 setup - P2.1 hardware mapping
    P2DIR &= ~BIT1;     // set s1 as INPUT
    P2REN |= BIT1;      // enable resistor
    P2OUT |= BIT1;      // enable pullup

    // s2 setup - P1.0 hardware mapping
    P1DIR &= ~BIT1;     // set s2 as INPUT
    P1REN |= BIT1;      // enable resistor
    P1OUT |= BIT1;      // enable pullup
}
