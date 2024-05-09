#include <msp430.h> 
#include <stdint.h>

#define TA0_CCR0_INT 53         // Timer A0 CCR0 interruption priority
#define TA0_CCRN_INT 52         // Timer A0 CCR1,2,3,4 interruption priority

void debounce();

/**
 * main.c
 */

float tempo;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	/* S1 */
	P2DIR &= ~BIT1;             // direção de entrada
	P2REN |= BIT1;              // resistor habilitado
	P2OUT |= BIT1;              // pull-up
	P2IE |= BIT1;               // interrupt enabled
	P2IES |= BIT1;              // Hi/lo edge
	P2IFG &= ~BIT1;             // P2.1 IFG = 0

	/* S2 */
    P1DIR &= ~BIT1;             // direção de entrada
    P1REN |= BIT1;              // resistor habilitado
    P1OUT |= BIT1;              // pull-up
    P1SEL |= BIT1;              // modo de captura selecionado

    /* LEDs */
	P1DIR |= BIT0;              // direção de saída
	P1OUT &= ~BIT0;             // LED vermelho off

	P4DIR |= BIT7;              // direção de saída
	P4OUT &= ~BIT7;             // LED verde off

	/*********
	 *  TA0  *
	 *********/
	/**
	 * Capture Mode: 1,2,3 (flanco de subida, descida, ambos)
	 * CCIS: seleciona entradas
	 * SCS: 0,1 (assincrono e sincrono)
	 * CAP: captura habilitada ou não
	 * OUTMOD:
	 * CCIE: interrupções do capture mode habilitadas
	 */
	TA0CCTL0 = (CM_2 | CCIS_0 | SCS | CAP | CCIE);
	/*
     * TASSEL: seleciona frequência de entrada (ACLK)
     * ID: divisão por 1,2,4,8 (ID_0,ID_1,ID_2,ID_3)
     * MC (Mode Counter): modo continuo
     */
    TA0CTL = (TASSEL_1 | ID_2 | MC_2);

    __enable_interrupt();



	while(1){
	    while((TA0CCTL0 & CCIFG) == 0);

	    tempo /= (32678/4);
	    if(tempo < 1){
	        P1OUT |= BIT0;
	    }
	    else if((tempo >= 1) && (tempo <= 3)){
	        P4OUT |= BIT7;
	        P1OUT |= BIT0;
	    }
	    else if(tempo > 3){
	        P4OUT |= BIT7;
	    }
	    else{
	        // Algo errado...
	    }
	}
}


// S.1
#pragma vector=PORT2_VECTOR
__interrupt void P2ISR(){
    switch(P2IV){
    case 0x4:                   // P2.1
        TA0CTL |= TACLR;        // limpa o timer
        debounce();
        break;
    default: break;
    }
}

#pragma vector=TA0_CCR0_INT
__interrupt void TIMER_A0_ISR(){
    /**
     * TA0CCR0: valor obtido pelo modo de captura
     * TA0R: valor do clock atual
     * tempo: quantas vezes (segundos) se passaram
     */
    tempo = TA0CCR0;
}

void debounce(){
    uint16_t i;
    for(i = 6000; i>0; i--);
}