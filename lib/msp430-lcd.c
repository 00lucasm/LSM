#include <msp430.h>

#include "msp430-lcd.h"

void lcd_init(void){

    UCB0I2CSA = PCF_ADDR;
    UCB0CTL1 |= UCTR | UCTXSTT;

    while((UCB0IFG & UCTXIFG) == 0);

    UCB0TXBUF = 0;

    while((UCB0CTL1 & UCTXSTT) == UCTXSTT);

    if((UCB0IFG & UCNACKIFG) == UCNACKIFG){
        while(TRUE);
    }

    lcd_aux(0);
    delay(20000);
    lcd_aux(3);
    delay(10000);
    lcd_aux(3);
    delay(10000);
    lcd_aux(3);
    delay(10000);
    lcd_aux(2);

    lcd_aux(2);     lcd_aux(8);
    lcd_aux(0);     lcd_aux(8);
    lcd_aux(0);     lcd_aux(1);
    lcd_aux(0);     lcd_aux(6);
    lcd_aux(0);     lcd_aux(0xF);

    while((UC0IFG & UCTXIFG) == 0);

    UCB0CTL1 |= UCTXSTP;

    while((UCB0CTL0 & UCTXSTP) == UCTXSTP);

    delay(50);

}

void lcd_aux(char data){

    while((UCB0IFG & UCTXIFG) == 0);

    UCB0TXBUF = ((data << 4) & 0xF0) | BIT3;

    delay(50);

    while((UCB0IFG & UCTXIFG) == 0);

    UCB0TXBUF = ((data << 4) & 0xF0) | BIT3 | BIT2;

    delay(50);

    while((UCB0IFG & UCTXIFG) == 0);

    UCB0TXBUF = ((data << 4) & 0xF) | BIT3;

}

int pcf_read(void){

    int data;

    UCB0I2CSA = PCF_ADDR;
    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTT;

    while((UCB0CTL1 & UCTXSTT) == UCTXSTT);

    UCB0CTL1 |= UCTXSTP;

    while((UCB0CTL1 & UCTXSTP) == UCTXSTP);

    while((UCB0IFG & UCRXIFG) == 0);

    data = UCB0RXBUF;

    return data;

}

void pcf_write(char data){

    UCB0I2CSA = PCF_ADDR;
    UCB0CTL1 |= UCTR | UCTXSTT;

    while((UCB0IFG & UCTXIFG) == 0);

    UCB0TXBUF = data;

    while((UCB0CTL1 & UCTXSTT) == 0);

    if((UCB0IFG & UCNACKIFG) == UCNACKIFG){
        while(TRUE);
    }

    UCB0CTL1 |= UCTXSTP;

    while((UCB0CTL1 & UCTXSTP) == UCTXSTP);

}

int pcf_test(char addr){

    UCB0I2CSA = addr;
    UCB0CTL1 |= UCTR | UCTXSTT;

    while((UCB0IFG & UCTXIFG) == 0);

    UCB0CTL1 |= UCTXSTP;

    while((UCB0CTL1 & UCTXSTP) == UCTXSTP);

    if((UCB0IFG & UCNACKIFG) == 0)
        return TRUE;
    else
        return FALSE;

}

void led_i2c_config(void){

    UCB0CTL1 |= UCSWRST;

    UCB0CTL0 = UCSYNC | UCMODE_3 | UCMST;

    UCB0BRW = BR_100K;

    P3SEL |= BIT1 | BIT0;

    UCB0CTL1 = UCSSEL_2;

}

void led_vd(void);
void led_VD(void);
void led_vm(void);
void led_VM(void);
void gpio_config(void);

void delay(long limit){

    volatile long count = 0;

    while(count++ < limit);

}

void lcd_char(char x){

    char lsn, msn;

    msn = (x & 0xF0);
    lsn = ((x & 0xF) << 4);

    pcf_write(msn | 9);
    pcf_write(msn | 0xD);
    pcf_write(msn | 9);
    pcf_write(lsn | 9);
    pcf_write(lsn | 0xD);
    pcf_write(lsn | 9);

}

void lcd_cursor(char x){

    char lsn, msn;
    x |= 0x80;

    msn = (x & 0xF0);
    lsn = ((x & 0xF) << 4);

    pcf_write(msn | 8);
    pcf_write(msn | 0xC);
    pcf_write(msn | 8);
    pcf_write(lsn | 8);
    pcf_write(lsn | 0xC);
    pcf_write(lsn | 8);

}

void lcd_str(char *ptr){

    char i = 0;

    while(ptr[i] != '\0'){
        if((15 - i) > 0){
            lcd_char(ptr[i]);
        }else{
            lcd_cursos(LINE_1_INIT);
        }
    }

}
