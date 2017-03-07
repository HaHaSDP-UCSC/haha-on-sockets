/**
 * @file lcd.c
 * @brief LCD application level, given menu, prints to LCD
 * @author August Valera (avalera)
 * @version
 * @date 2017-03-02
 */

#include "lcd.h"

char** LCD;

/**
 * @brief Allocates memory for the LCD screen buffer
 */
void lcdInit(void) {
    if(! LCD) {
        LCD = calloc(LCD_LINES, sizeof(char*));
        int i;
        for(i = 0; i < LCD_LINES; i++)
            LCD[i] = calloc(LCD_COLS, sizeof(char));
    }
}

/**
 * @brief Clears the LCD screen buffer
 */
void lcdClear(void) {
    if(LCD) {
        int i;
        for(i = 0; i < LCD_LINES; i++)
            lcdSetChar(i, 0, '\0');

    }
}

/**
 * @brief Prints out the LCD buffer
 */
void lcdUpdate(void) {
    if(LCD) {
        printf("%s\n", LCD_SEPARATE);
        int i;
        for(i = 0; i < LCD_LINES; i++)
            printf("%s\n", LCD[i]);
        printf("%s\n", LCD_SEPARATE);
    }
}

/**
 * @brief Sets a line in LCD buffer
 * @param line Integer from 0 to LCD_LINE
 * @param msg String to copy to buffer
 * @return Charaters written
 */
int lcdSetLine(int line, char* msg) {
    //printf("lcdSetLine(%d, %s)\n", line, msg);
    int chars = 0, i;
    if(LCD && line >= 0 && line < LCD_LINES) {
        strncpy(LCD[line], msg, LCD_COLS);
        chars = strlen(LCD[line]);
        if(chars < LCD_COLS)
            for(i = chars; i < LCD_COLS; i++) {
                lcdSetChar(line, i, ' ');
            }
    } else return(-1);
    //printf("success\n");
    return(chars);
}

/**
 * @brief Gets a line from LCD buffer
 * @param line Integer from 0 to LCD_LINE
 * @param msg String buffer to take input
 * @return Characters written
 */
int lcdGetLine(int line, char* msg) {
    int chars = 0;
    if(LCD && line >= 0 && line < LCD_LINES) {
        strcpy(msg, LCD[line]);
        chars = strlen(LCD[line]);
    } else return(-1);
    return(chars);
}

/**
 * @brief Sets character to LCD buffer
 * @param line Integer from 0 to LCD_LINE
 * @param col Integer from 0 to LCD_COL
 * @param msg Character to write
 * @return 0 on success, -1 otherwise
 */
int lcdSetChar(int line, int col, char msg) {
    if(LCD && line >= 0 && line < LCD_LINES && col >= 0 && col < LCD_COLS) {
        LCD[line][col] = msg;
    } else return(-1);
    return(0);
}

/**
 * @brief Gets character from LCD buffer
 * @param line Integer from 0 to LCD_LINE
 * @param col Integer from 0 to LCD_COL
 * @param msg Character to write
 * @return 0 on success, -1 otherwise
 */
char lcdGetChar(int line, int col) {
    char msg;
    if(LCD && line >= 0 && line < LCD_LINES && col >= 0 && col < LCD_COLS) {
        msg = LCD[line][col];
    } else return('\0');
    return(msg);
}

/**
 * @brief Deallocates LCD buffer
 * @return 0 on success, -1 otherwise
 */
int lcdDestroy(void) {
    if(LCD) {
        int i;
        for(i = 0; i < LCD_LINES; i++)
            free(LCD[i]);
        free(LCD);
    } else return(-1);
    return(0);
}
