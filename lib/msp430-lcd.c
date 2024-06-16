#include <msp430.h>
#include "msp430-lcd.h"

void lcd_init(void){

    UCB0I2CSA = PCF_ADR;
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

    lcd_aux(2);lcd_aux(8);

}

void lcd_aux(char data);
int pcf_read(void);
void pcf_write(char data);
int pcf_teste(char addr);
void led_vd(void);
void led_VD(void);
void led_vm(void);
void led_VM(void);
void i2c_config(void);
void gpio_config(void);
void delay(long limite);
void lcd_char(char x);
void lcd_cursor(char x);
void lcd_str(char *ptr);