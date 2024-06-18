#ifndef MSP430_OLED_H_
#define MSP430_OLED_H_

#define TRUE    1
#define FALSE   0
#define SDA_PIN BIT0
#define SCL_PIN BIT1
#define OLED_I2C_ADDR   0x78

extern const unsigned char font5x7[][5];

void i2c_init(void);
void i2c_write_byte(unsigned char slave_addr, unsigned char reg_addr, unsigned char data);
void oled_write_command(unsigned char command);
void oled_init(void);
void oled_clear(void);
void oled_draw_char(unsigned char x, unsigned char y, char c);
void oled_display_text(unsigned char row, unsigned char column, const char *text);

#endif
