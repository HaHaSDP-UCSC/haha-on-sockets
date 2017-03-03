/**
 * @file lcd.h
 * @brief LCD application level, given menu, prints to LCD
 * @author August Valera (avalera)
 * @version
 * @date 2017-03-02
 */

#ifndef __LCD_H__
#define __LCD_H__

#include "hahalib.h"

#define LCD_LINES 4
#define LCD_COLS 16

void lcdInit(void);
void lcdClear(void);
void lcdUpdate(void);
int lcdWrite(int line, int col, char* msg);
int lcdDestroy(void);

#endif // __LCD_H__
