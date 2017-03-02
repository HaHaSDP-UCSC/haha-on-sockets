/**
 * @file menu.c
 * @brief Menu and MenuItems library defines
 *
 * @author August Valera (avalera)
 * @version
 * @date 2017-02-28
 */

#include "hahalib.h"

#define MENUITEM_TITLE_MAXLEN 32

typedef struct MenuItem MenuItem;

typedef struct MenuItem {
  void (*onEnter)();
  void (*onExit)();
  char value[MENUITEM_TITLE_MAXLEN];
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

Menu* menuInit(void);
int menuDestroy(Menu* this);

MenuItem* menuItemInit(MenuItem* parent, char* value);
int menuItemSetValue(MenuItem* this, char* value);
void menuItemPrintTree(MenuItem* this);
void menuItemPrintTreeHelper(MenuItem* this, int level);
int menuItemDestroy(MenuItem* this);
