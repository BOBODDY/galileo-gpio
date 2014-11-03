/**
 * userlcd.h - Userspace LCD functions
 *
 * author: Nick Mathews
 */
 
#ifndef USERLCD_H
#define USERLCD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

/* digital-pin assignments */
#define RS 18
#define E  28
#define D0 17
#define D1 24
#define D2 27
#define D3 26
#define D4 19
#define D5 16
#define D6 25
#define D7 38

/* commands */
#define LCD_CLEAR   0x01
#define LCD_HOME    0x02
#define LCD_ENTRY   0x04
#define LCD_ON_OFF  0x08
#define LCD_CDSHIFT 0x10
#define LCD_FUNC    0x20
#define LCD_CGRAM   0x40
#define LCD_DGRAM   0x80

#define LCD_ENTRY_SH  0x01
#define LCD_ENTRY_ID  0x02

#define LCD_ON_OFF_B  0x01
#define LCD_ON_OFF_C  0x02
#define LCD_ON_OFF_D  0x04

#define LCD_FUNC_F  0x04
#define LCD_FUNC_N  0x08
#define LCD_FUNC_DL 0x10

#define LCD_CDSHIFT_RL  0x04

void delay(int);
char *itoa(int val);
void dataByte(uint8_t data);
void putCommand(uint8_t command);
void lcdPosition(int x, int y);
void lcdPutchar(uint8_t data);
void lcdPuts(char *string);
void setup();
void clean_up();

#endif /* USERLCD_H */
