#include <msp430.h>
#include "msp430-buzzer.h"

enum notas {
    ZR,
    CC,
    CS,
    D,
    DS,
    E,
    F,
    FS,
    G,
    GS,
    A,
    AS,
    B,
    CH,
    CSH,
    DH,
    DSH,
    EH,
    FH,
    FSH,
    GH,
    GSH,
    AH,
    ASH,
    BH
}

int freq[] = {
    0,      // ZR
    261,    // CC
    277,    // CH
    293,    // D
    311,    // DH
    329,    // E
    349,    // F
    369,    // FH
    392,    // G
    415,    // GH
    440,    // A
    466,    // AH
    493,    // B
    523,    // CS
    554,    // CSH
    587,    // DS
    622,    // DSH
    659,    // ES
    698,    // FS
    739,    // FSH
    784,    // GS
    830,    // GSH
    880,    // AS
    932,    // ASH
    987,    // BS
};

int tetris_theme_verse[] = {
    E, 400, B, 200, CC, 200, D, 400, CC, 200, B, 200,
    A, 400, A, 200, CC, 200, E, 400, D, 200, CC, 200,
    B, 600, CC, 200, D, 400, E, 400,
    CC, 400, A, 400, A, 400, ZR, 400,
    ZR, 200, D, 400, F, 200, AH, 400, GH, 200, F, 200,
    E, 600, CC, 200, E, 400, D, 200, CC, 200,
    B, 400, B, 200, CC, 200, D, 400, E, 400,
    CC, 400, A, 400, A, 400, ZR, 400,
    ZR,
    ZR
};

int tetris_theme_chorus[] = {
    FS, 800, D, 800,
    E, 800, CS, 800,
    D, 800, B, 800,
    AS, 800, CS, 400,
    FS, 800, D, 800,
    E, 800, CS, 800,
    D, 400, FS, 400, B, 800,
    AS, 800, ZR, 800,
    ZR,
    ZR
};


void pin_config(void){
    P2DIR |= BIT5;
    P2OUT &= ~BIT5;
    P2SEL |= BIT5;

    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;
}

void t2_config(void){
    TA2CTL = TASSEL_2 | ID_0 | MC_1 | TACLR;
    TA2EX0 = TAIDEX_0;
    TA2CCTL2 = OUTMOD_6;
}

void tom(int freq, int tp){
    int cont;
    if(freq != ZR){
        TA2CCR0 = 1048576L/freq;
        TA2CCR2 = TA2CCR0/2;
        cont = freq*(tp/1000.0);
    }else{
        TA2CCR0 = 1048576L/1000;
        TA2CCR2 = 0;
        cont = tp;
    }
    while(cont > 0){
        while((TA2CCTL0 & CCIFG) == 0);
        TA2CCTL0 &= ~CCIFG;
        cont--;
    }
}

