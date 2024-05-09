;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------

; Módulo 1 - Exercício 15

; Cada acionamento A->F de S1 (P2.1) inverte LED1 (P1.0)
; Cada acionamento A->F de S2 (P1.1) inverte LED2 (P4.7)
; Quando S1 e S2 estão acionadas, LEDs piscam com 1 Hz

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

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
