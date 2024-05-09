#include <msp430.h>

#define DBC 90000;

void setup(void);
void debounce(void);

int main(void){
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	setup();

	while(1){
	    if(!(P2IN & BIT1)){
	        P1OUT ^= BIT0;
	        debounce();
	    }
	    if(!(P1IN & BIT1)){
	        P1OUT ^= BIT0;
	        debounce();
	    }
	}
}

void setup(void){
	P2DIR &= ~BIT1;             // direção de entrada
	P2REN |= BIT1;              // habilita resistor
	P2OUT |= BIT1;              // pull-up

	P1DIR &= ~BIT1;             // direção de entrada
	P1REN |= BIT1;              // habilita resistor
	P1OUT |= BIT1;              // pull-up

	P1DIR |= BIT0;              // direção de saída
	P1OUT &= ~BIT0;             // LED vermelho off
}

void debounce(void){
    volatile int dbc = DBC;
    for(i; i>0; i--);
}