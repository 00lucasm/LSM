#include <msp430.h> 

#define TA0_CCR0_INT 53         // Timer A0 CCR0 interruption priority
#define TA0_CCRN_INT 52         // Timer A0 CCR1,2,3,4 interruption priority

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P4DIR |= BIT7;              // direção de saída
	P4OUT &= ~BIT7;             // LED verde off

    TA0CCTL0 = CCIE;            // Enable interrupts for CCR0.
	/*
     * TASSEL: seleciona frequência de entrada
     * ID: divisão por 1,2,4,8 (ID_0,ID_1,ID_2,ID_3)
     * MC (Mode Counter): modo UP selecionado (conta até TA0CCR0 e ativa FLAG)
     */
	TA0CTL = (TASSEL_1 | ID_0 | MC_1);
    TA0CCR0 = 32768/2;          // Limite de contagem
    TA0EX0 = TAIDEX_0;          // 1/1

    __enable_interrupt();       // habilita interrupções

    while(1){

	}
}

// Indicar endereço da próxima função
#pragma vector=TA0_CCR0_INT
__interrupt void TA0_CCR0_ISR(){
    // quando contador estoura chama essa função
    P4OUT ^= BIT7;          // swtich LED
}
