#include <msp430.h>

#ifndef _MSP430-LCD_H_
#define _MSP430-LCD_H_

#define TRUE    1
#define FALSE   0
#define LINE_0_INIT 0
#define LINE_0_END  0xF
#define LINE_1_INIT 0x40
#define LINE_1_END  0x4F

// Definicao do endereco do PCF_8574
#define PCF_ADR1 0x3F
#define PCF_ADR2 0x27
#define PCF_ADR  PCF_ADR1

#define BR_100K    11  // SMCLK/100K = 11
#define BR_50K     21  // SMCLK/50K  = 21
#define BR_10K    105  // SMCLK/10K  = 105

void lcd_init(void);
void lcd_aux(char data);
int pcf_read(void);
void pcf_write(char dado);
int pcf_teste(char adr);
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

#endif