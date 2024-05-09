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

; Módulo 1 - Exercício 8

; Retorna o maior valor de 16 bits da sequência de Fibonacci

; R5 = endereço na memória = 0x2400
; R6 = n-2
; R7 = n-1
; R9 = registrador variável
; R10 = maior valor

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
FIB16:		mov		R6,R9		; R9 passa a ser (n-2)
			mov		R7,R6		; R6 passa a ser (n-1)
			add		R9,R7		; R7 = R9 + R6 = (n-2) + (n-1) = n
			jc		END			; Se carry = 1, R7 > 16 bits
			mov		R7,0(R5)
			incd	R5
			jmp		FIB16
			nop
FIM:		decd	R5			; Volta ao elemento anterior (< 16 bits)
			mov		@R5,R10		; R10 = último elemento < 16 bits
			ret

			.data
; data is empty
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
            
