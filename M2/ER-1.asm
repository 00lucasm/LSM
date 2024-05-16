;ER1
DELAY       .equ    65535
            ;
            call    #P_VM
            jmp     $
P_VM:       bis.b   #BIT0, &P1DIR       ;set P1.0 as OUTPUT
P_VM1:      bis.b   #BIT0, &P1OUT       ;set P1.0 = 1 (enabled)
            call    #TIMER              ;delay
            bic.b   #BIT0, &P1OUT       ;set P1.0 = 0 (disabled)
            call    #TIMER              ;delay
            jmp     P_VM1
TIMER:      mov     #DELAY,R5
TIMER1:     dec     R5
            jnz     TIMER1
            ret