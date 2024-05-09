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
            
