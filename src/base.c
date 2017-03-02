/**
 * @file base.c
 * @brief Base station code, main of this repo
 *
 * @author August Valera (avalera)
 * @version
 * @date 2017-02-28
 */

#include "hahalib.h"
#include "menu.h"

/**
 * @brief Initializes the menus for our project
 * @return Menu
 */
Menu* initMenus(void) {
  Menu* this = menuInit();
  MenuItem* first = menuItemInit(this->root);
  strcpy(first->value, "1:first");
  MenuItem* second = menuItemInit(this->root);
  strcpy(second->value, "2:second");
  MenuItem* secondFirst = menuItemInit(second);
  strcpy(secondFirst->value, "21:secondfirst");
  return(this);
}

/**
 * @brief Main of the program
 * @param argc Number of args
 * @param argv Array of args
 * @return Status
 */
int main(int argc, char** argv) {
  printf("Test executable.\n");
  Menu* menu = initMenus();
  menuItemPrintTree(menu->root);
  return(1);
}
