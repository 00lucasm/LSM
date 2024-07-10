#include <msp430.h>

#ifndef MSP430_LCD_H_
#define MSP430_LCD_H_

#define TRUE    1
#define FALSE   0

#define LINE_0_INIT 0
#define LINE_0_END  0xF
#define LINE_1_INIT 0x40
#define LINE_1_END  0x4F

// PCF_8574 address
#define PCF_ADDR1 0x3F
#define PCF_ADDR2 0x27
#define PCF_ADDR  PCF_ADDR1

#define BR_100K    11  // SMCLK/100K = 11
#define BR_50K     21  // SMCLK/50K  = 21
#define BR_10K    105  // SMCLK/10K  = 105

void lcd_init(void);
void lcd_aux(char data);
int pcf_read(void);
void pcf_write(char data);
int pcf_test(char addr);
void led_vd(void);
void led_VD(void);
void led_vm(void);
void led_VM(void);
void lcd_i2c_config(void);
void lcd_gpio_config(void);
void delay(long limit);
void lcd_char(char x);
void lcd_cursor(char x);
void lcd_str(char *ptr);

#endif
