
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
vetor:		.byte	8,"TESTTEST"			; lowest = 'E' = 0x45
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
            