/**
 * @file lcd.c
 * @brief LCD application level, given menu, prints to LCD
 * @author August Valera (avalera)
 * @version
 * @date 2017-03-02
 */

#include "lcd.h"

char*** LCD;

void lcdInit(void) {
    LCD = calloc(LCD_LINES, sizeof(char*));
    for(int i = 0; i < LCD_LINES; i++)
        LCD[i] = calloc(LCD_COLS, sizeof(char));
}

void lcdClear(void) {
    for(int i = 0; i < LCD_LINES; i++)
        lcdSetChar(i, 0, '\0');
}

void lcdUpdate(void) {
    printf("%s\n", LCD_SEPARATE);
    for(int i = 0; i < LCD_LINES; i++)
        printf("%s\n", LCD[i]);
    printf("%s\n", LCD_SEPARATE);
}

int lcdSetLine(int line, char* msg) {
    //printf("lcdSetLine(%d, %s)\n", line, msg);
    int chars = 0;
    if(line >= 0 && line < LCD_LINES) {
        strncpy(LCD[line], msg, LCD_COLS);
        chars = strlen(LCD[line]);
    } else return(-1);
    //printf("success\n");
    return(chars);
}

int lcdGetLine(int line, char* msg) {
    int chars = 0;
    if(line >= 0 && line < LCD_LINES) {
        strcpy(msg, LCD[line]);
        chars = strlen(LCD[line]);
    } else return(-1);
    return(chars);
}

int lcdSetChar(int line, int col, char msg) {
    if(line >= 0 && line < LCD_LINES && col >= 0 && col < LCD_COLS) {
        LCD[line][col] = msg;
    } else return(-1);
    return(0);
}

char lcdGetChar(int line, int col) {
    char msg;
    if(line >= 0 && line < LCD_LINES && col >= 0 && col < LCD_COLS) {
        msg = LCD[line][col];
    } else return('\0');
    return(msg);
}

int lcdDestroy(void) {
    if(LCD) {
        for(int i = 0; i < LCD_LINES; i++)
            free(LCD[i]);
        free(LCD);
    } else return(-1);
    return(0);
}
