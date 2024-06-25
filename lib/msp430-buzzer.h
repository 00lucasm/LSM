#ifndef _MSP430_BUZZER_H_
#define _MSP430_BUZZER_H_

int freq[];
int tetris_theme_verse[];
int tetris_theme_chorus[];

void pin_config(void);
void t2_config(void);
void tom(int freq, int tp);

#endif
