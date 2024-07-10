#include <msp430.h>

#include "msp430-oled.h"
#include "font5x7.h"

void i2c_init(void){
    P3SEL |= SDA_PIN + SCL_PIN;
    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;
    UCB0CTL1 = UCSSEL_2 + UCSWRST;
    UCB0BR0 = 10;
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;
    UCB0IE |= UCNACKIE;
}

void i2c_write_byte(unsigned char slave_addr, unsigned char reg_addr, unsigned char data){

    while(UCB0CTL1 & UCTXSTP);
    UCB0I2CSA = slave_addr;
    UCB0CTL1 |= UCTR + UCTXSTT;

    while(!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = reg_addr;

    while(!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = data;

    while(!(UCB0IFG & UCTXIFG));
    UCB0CTL1 |= UCTXSTP;
    while(UCB0CTL1 & UCTXSTP);

}

void oled_write_command(unsigned char command){

    i2c_write_byte(OLED_I2C_ADDR, 0x00, command);

}

void oled_init(void){

    oled_write_command(0xAE);
    oled_write_command(0xD5);
    oled_write_command(0x80);
    oled_write_command(0xA8);
    oled_write_command(0x3F);
    oled_write_command(0xD3);
    oled_write_command(0x00);
    oled_write_command(0x40);
    oled_write_command(0x8D);
    oled_write_command(0x14);
    oled_write_command(0x20);
    oled_write_command(0x00);
    oled_write_command(0xA1);
    oled_write_command(0xC8);
    oled_write_command(0xDA);
    oled_write_command(0x12);
    oled_write_command(0x81);
    oled_write_command(0xCF);
    oled_write_command(0xD9);
    oled_write_command(0xF1);
    oled_write_command(0xDB);
    oled_write_command(0x40);
    oled_write_command(0xA4);
    oled_write_command(0xA6);
    oled_write_command(0xAF);

}

void oled_clear(void){
    for(unsigned int i = 0; i < 8; i++){
        oled_write_command(0xB0 + i);
        oled_write_command(0x00);
        oled_write_command(0x10);

        for(unsigned int j = 0; j < 128; j++){
            i2c_write_byte(OLED_I2C_ADDR, 0x40, 0x00);
        }
    }
}

void oled_draw_char(unsigned char x, unsigned char y, unsigned char c){

    int i;
    unsigned int offset = c * 5;

    for(i = 0; i < 5; i++){
        i2c_write_byte(OLED_I2C_ADDR, 0x40, font5x7[offset + i]);
    }

    i2c_write_byte(OLED_I2C_ADDR, 0x40, 0x00);

}