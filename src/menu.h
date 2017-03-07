/**
 * @file menu.c
 * @brief Menu and MenuItems library defines
 *
 * @author August Valera (avalera)
 * @version
 * @date 2017-02-28
 */

#ifndef _HA_MENU_
#define _HA_MENU_

#include "halib.h"
#include "lcd.h"

#define MENU_MAXLEN 32
#define MENU_WRAP true
#define MENU_DBUG true

typedef struct MenuItem MenuItem;

typedef struct MenuItem {
    void (*onEnter)();
    void (*onExit)();
    char value[MENU_MAXLEN];
    bool visible;
    MenuItem* parent;
    MenuItem* child;
    MenuItem* prev;
    MenuItem* next;
} MenuItem;

typedef struct Menu {
    MenuItem* root;
    MenuItem* current;
} Menu;

typedef enum MenuDirection {
    MENU_UNDEF = 0,
    MENU_UP,
    MENU_DOWN,
    MENU_LEFT,
    MENU_RIGHT
} MenuDirection;

Menu* menuInit(void);
int menuMove(Menu* menu, MenuDirection direct);
int menuSetLcd(Menu* menu);
int menuDestroy(Menu* this);

MenuItem* menuItemInit(MenuItem* parent, char* value);
int menuItemSetValue(MenuItem* this, char* value);
void menuItemPrintTree(MenuItem* this);
void menuItemPrintTreeHelper(MenuItem* this, int level);
int menuItemDestroy(MenuItem* this);

#endif // _HA_MENU_
