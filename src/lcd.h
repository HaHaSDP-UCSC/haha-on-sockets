/**
 * @file lcd.h
 * @brief LCD application level, given menu, prints to LCD
 * @author August Valera (avalera)
 * @version
 * @date 2017-03-02
 */

#ifndef _HA_LCD_
#define _HA_LCD_

#include "halib.h"

#define LCD_LINES 4
#define LCD_COLS 16

#define LCD_SEPARATE "================"

void lcdInit(void);
void lcdClear(void);
void lcdUpdate(void);
int lcdSetLine(int line, char* msg);
int lcdGetLine(int line, char* msg);
int lcdSetChar(int line, int col, char msg);
char lcdGetChar(int line, int col);
int lcdDestroy(void);

#endif // _HA_LCD_
