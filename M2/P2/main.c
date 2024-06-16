/*

Nome: Lucas Rodrigues da Silva Melo
Matricula: 170149757

PROBLEMA 2: Controle remoto infravermelho (Visto 2)

*/

#include <msp430.h>

//TA1CCTL1 = CM_2 | SCS | CAP; // flanco de descida
//TA1CCTL1 = CM_1 | SCS | CAP; // flanco de subida

// volatile long x, y, dif, code;
// volatile int vet[32];

#define TRUE    1
#define FALSE   0
#define PARTm   0.9*14051
#define PARTM   1.1*14051

void ta1_setup(void);
char partida(void);
void cap32(void);
void io_setup(void);

int main(void){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    ta1_setup();
    io_setup();

    while(TRUE){

        partida();
        cap32();
        //conversion();
        //interpreter();

    }

    return 0;
}

void ta1_setup(void){

    TA1CTL = TASSEL_2 | MC_2;

    TA1CCTL1 = CM_2 | SCS | CAP;

    P2DIR &= ~BIT0; // P2.0 saída

    P2SEL |= BIT0;  // P2.0 I/O

}

char partida(void){

    volatile long x, y, dif, code;
    TA1CCTL1 = CM_2 | SCS | CAP; // flanco de descida
    while(TRUE){
        TA1CCTL1 &= ~CCIFG;
        while((TA1CCTL1 & CCIFG) == 0);
        x = TA1CCR1;
        TA1CCTL1 &= ~CCIFG;
        while((TA1CCTL1 & CCIFG) == 0);
        y = TA1CCR1;
        dif = y - x;
        if(dif < 0)
            dif += 65535;
        if((PARTm < dif) && (dif < PARTm))
            return TRUE;
    }
}

void cap32(){

    volatile int vet[32];
    volatile long x, y, dif;
    char i;

    TA1CCTL1 = CM_1 | SCS | CAP; // flanco de subida
    TA1CCTL1 &= ~CCIFG;

    while((TA1CCTL1 & CCIFG) == 0);

    x = TA1CCR1;

    for(i = 0; i < 32; i++){
        TA1CCTL1 &= ~CCIFG;
        while((TA1CCTL1 & CCIFG) == 0);
        y = TA1CCR1;
        dif = y - x;
        if(dif < 0)
            dif += 65535;
        vet[i] = dif;
        x = y;
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
