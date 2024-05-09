#include <msp430.h>

#define TA0_CCR0_INT 53         // Timer A0 CCR0 interruption priority
#define TA0_CCRN_INT 52         // Timer A0 CCR1,2,3,4 interruption priority

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P4DIR |= BIT7;              // direção de saída
	P4OUT &= ~BIT7;             // LED verde off

	/*
	 * TASSEL: seleciona frequência de entrada
	 * ID: divisão por 1,2,4,8 (ID_0,ID_1,ID_2,ID_3)
	 * MC (Mode Counter): modo UP selecionado (conta até TA0CCR0 e ativa FLAG)
	 */

	TA0CTL = (TASSEL_1 | ID_0 | MC_1);
	TA0CCR0 = 32768/2;          // Limite de contagem
	TA0EX0 = TAIDEX_0;          // 1/1

	while(1){
	    // do nothing
	    while((TA0CTL & TAIFG) == 0);
	    P4OUT ^= BIT7;
	    TA0CTL &= ~BIT0;
	}
}