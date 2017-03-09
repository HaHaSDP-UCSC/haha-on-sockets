/**
 * @file menu.c
 * @brief Menu and MenuItems library defines
 * @author August Valera (avalera)
 * @version
 * @date 2017-02-28
 */

// TODO: Implement menus with stack memory instead of malloc()

#ifndef _HA_MENU_
#define _HA_MENU_

#include "halib.h"
#include "lcd.h"

#define MENU_MAXLEN 32
#define MENU_WRAP true

typedef struct MenuItem MenuItem;

typedef struct MenuItem {
    void (*onView)();
    void (*onClick)();
    char value[MENU_MAXLEN];
    bool active;
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
MenuItem* menuItemGetNext(MenuItem* this);
MenuItem* menuItemGetPrev(MenuItem* this);
MenuItem* menuItemGetLast(MenuItem* this);
int menuItemDestroy(MenuItem* this);
void* menuItemOnViewDefault(Menu* menu);
void* menuItemOnClickDefault(Menu* menu);


#endif // _HA_MENU_
