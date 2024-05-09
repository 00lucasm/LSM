# M1 labs solutions

## M1 - EX1
Write a subroutine called "MENOR" which receives in R5 the memory address of a bytes vector (unsigned) and returns:

- R6 -> the smallest item in the vector
- R7 -> how many times it has appeared 

Solution:

```asm
SETUP:		mov		#vetor,R4				; initialize the pointer
			mov.b	@R4+,R5					; loop counter
			mov.b	@R4+,R6					; lowest value tmp
			mov.b	#1,R7					; repeater counter eq to zero
			call	#MENOR
			jmp		$						; inifinity loop
MENOR:		cmp.b	@R4,R6					;
			jhs		LB1
			inc		R4
			dec		R5
			jnz		MENOR
			ret
LB1:		cmp.b	@R4,R6
			jne		FREQ
			inc		R7
LB2:		mov.b	@R4+,R6
			dec		R5
			jnz		MENOR
			ret
FREQ:		mov.b	#1,R7
			jmp		LB2
			nop

			.data
vetor:		.byte	10,"TESTTEST"			; lowest = 'E' = 0x45
```

## M1 - EX2

Solution

```asm
SETUP:		mov		#vetor,R4				; pointer that receives the vector mem addr 
			mov		@R4+,R5					; loop counter 
			clr		R6						; greatest value
			mov		#1,R7					; repeater count
			call	#MAIOR16				;
			jmp		$						;
MAIOR16:	cmp		@R4,R6
			jhs		LB1
			mov		@R4+,R6
LB1:		inc		R4
			dec		R5
			jnz		MAIOR16
			ret

			.data
vetor:		.byte	6,0,"JOAQUIMJOSE",0			;maior = 0x534F
```

## M1 - EX8

Solution

```asm
SETUP:		mov		#0x2400,R5	; memory address with the first value
			clrc
			mov		#1,R6		; 
			mov		R6,0(R5)
			incd	R5
			mov		#1,R7		; R7 = (n-1) = 1
			mov 	R7,0(R5)
			incd	R5
			add		R6,R7		; R7 = (n-2) + (n-1) = n
			mov		R7,0(R5)
			incd	R5
			call	#FIB16
			jmp		$
			nop
FIB16:		mov		R6,R9		
			mov		R7,R6		
			add		R9,R7		
			jc		END			
			mov		R7,0(R5)
			incd	R5
			jmp		FIB16
			nop
FIM:		decd	R5			
			mov		@R5,R10		
			ret
```

## M1 - EX12


Solution

```asm
SETUP:		mov		#vetor,R5				; ponteiro
			mov.b	@R5+,R4					; varridas
			mov.b	R4,R6					; contador do loop
			call	#ORDENA
			jmp		$
			nop
ORDENA:		cmp.b	0(R5),1(R5)
			jhs		LB1
			mov.b	0(R5),R7				; reg auxiliar
			mov.b	1(R5),0(R5)
			mov.b	R7,1(R5)
LB1:		inc		R5
			dec		R6
			jnz		ORDENA
VARRE:		mov		#vetor,R5
			mov.b	@R5+,R6
			dec		R4
			cmp		#1,R4
			jne		ORDENA
			ret

                                            
			.data
vetor:		.byte	5,4,7,3,5,1				;
```

## M1 - EX15


Solution

```asm
DELAY1		.equ	300				; Debounce ≃ 0,5s
DELAY2		.equ	300

ATZ1		.equ	600				; Frequência ≃ 1s
ATZ2		.equ	600

			call 	#LEDS
			jmp		$
			nop

LEDS:		bic.b	#BIT1,&P2DIR	; S1 P2.1 = entrada
			bis.b	#BIT1,&P2REN
			bis.b	#BIT1,&P2OUT

			bic.b	#BIT1,&P1DIR	; S2 P1.1 = entrada
			bis.b	#BIT1,&P1REN
			bis.b	#BIT1,&P1OUT

			bis.b	#BIT0,&P1DIR	; LED1 P1.0 = saída
			bis.b	#BIT7,&P4DIR	; LED2 P4.7 = saída

LOOP:		bit.b	#BIT1,&P2IN
			jz		SFA				; Se S1 for pressionada
			bit.b	#BIT1,&P1IN
			jz		SAF				; Se S2 for pressionada
			jmp		LOOP
			nop

SFA:		bit.b	#BIT1,&P1IN		; Rotina para S1 pressionada
			jz		PISCA			; Se S2 for pressionada tbm
			xor.b	#BIT0,&P1OUT	; Senão, inverte LED1
			call	#DEBOUNCE
			jmp		LOOP
			nop

SAF:		bit.b	#BIT1,&P2IN		; Rotina para S2 pressionada
			jz		PISCA			; Se S1 for pressionada tbm
			xor.b	#BIT7,&P4OUT	; Senão, inverte LED2
			call	#DEBOUNCE
			jmp		LOOP
			nop
									; Rotina para S1 e S2 pressionadas
PISCA:		xor.b	#BIT0,&P1OUT	; Inverte LED1
			xor.b	#BIT7,&P4OUT	; Inverte LED2

			bit.b	#BIT1,&P2IN
			jnz		SAF				; Se S1 for solta

			bit.b	#BIT1,&P1IN
			jnz		SFA				; Se S2 for solta

			call	#ROT_ATZ
			jmp		PISCA
			nop

DEBOUNCE:	mov		#DELAY1,R6		; Rotina de debouncer
RT1:		mov		#DELAY2,R5
RT2:		dec		R5
			jnz		RT2
			dec		R6
			jnz		RT1
			ret

ROT_ATZ:	mov		#ATZ1,R6		; Rotina que define frequência de 1 Hz
ROT1:		mov		#ATZ2,R5
ROT2:		dec		R5
			jnz		ROT2
			dec		R6
			jnz		ROT1
			ret

```

## M1 - VISTO1


Solution

```asm
```