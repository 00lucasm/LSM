#ifndef MSP430_OLED_H_
#define MSP430_OLED_H_

#define TRUE    1
#define FALSE   0
#define SDA_PIN BIT0
#define SCL_PIN BIT1
#define ADDR_0  0x78
#define ADDR_1  0x7B
#define ADDR_2  0x7A
#define ADDR_3  0x3C
#define OLED_I2C_ADDR   ADDR_3

void i2c_init(void);
void i2c_write_byte(unsigned char slave_addr, unsigned char reg_addr, unsigned char data);
void oled_write_command(unsigned char command);
void oled_init(void);
void oled_clear(void);
void oled_draw_char(unsigned char x, unsigned char y, unsigned char c);
void oled_display_text(unsigned char row, unsigned char column, const char *text);

#endif