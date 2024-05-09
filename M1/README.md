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

## M1 - EX12

## M1 - EX15

## M1 - VISTO1