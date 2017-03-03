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
        printf("\r");
}

void lcdUpdate(void) {
    printf("==================\n");
    for(int i = 0; i < LCD_LINES; i++)
        printf("%d/%s\n", i, LCD[i]);
    printf("==================\n");
}

int lcdWrite(int line, int col, char* msg) {
    int chars = 0;
    if(line >= 0 && line < LCD_LINES && col >= 0) {
        for(int i = col; i < LCD_COLS && msg[chars]; i++)
            LCD[line][i] = msg[chars++];
    } else return(-1);
    return(chars);
}

int lcdDestroy(void) {
    if(LCD) {
        for(int i = 0; i < LCD_LINES; i++) {
            free(LCD[i]);
        }
        free(LCD);
    } else return(-1);
    return(0);
}
