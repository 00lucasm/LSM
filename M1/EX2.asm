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
SETUP:		mov		#vetor,R4				; R4 ptr que recebe end do vetor
			mov		@R4+,R5					; R5 é o contador do loop
			clr		R6						; R6 recebe maior valor
			mov		#1,R7					; R7 contador de freq
			call	#MAIOR16				; chama a subrot principal
			jmp		$						; trava a exec
MAIOR16:	cmp		@R4,R6
			jhs		LB1
			mov		@R4+,R6
LB1:		inc		R4
			dec		R5
			jnz		MAIOR16
			ret

			.data
vetor:		.byte	6,0,"JOAQUIMJOSE",0			;maior = 0x534F
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
            
