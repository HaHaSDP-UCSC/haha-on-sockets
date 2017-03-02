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
Menu* createMenus(void) {
  Menu* menu = menuInit();
  MenuItem* root = menu->root;
  MenuItem* main = menuItemInit(root, "Main Menu");
  MenuItem* contacts = menuItemInit(main, "Contact list");
  MenuItem* user = menuItemInit(main, "User info");
  MenuItem* userId = menuItemInit(user, "User ID");
  MenuItem* userName = menuItemInit(user, "User name");
  MenuItem* userAddr = menuItemInit(user, "User address");
  MenuItem* userPhone = menuItemInit(user, "User phone");
  MenuItem* set = menuItemInit(main, "Device settings");
  MenuItem* setOffice = menuItemInit(set, "Office mode");
  MenuItem* setAlert = menuItemInit(set, "Alert settings");
  MenuItem* setAlertSound = menuItemInit(setAlert, "Sound");
  MenuItem* setAlertLight = menuItemInit(setAlert, "Lights");
  MenuItem* setTest = menuItemInit(set, "Test button");
  MenuItem* setTestExit = menuItemInit(setTest, "Stop testing");
  MenuItem* setNotice = menuItemInit(set, "Notice settings");
  MenuItem* setNoticeTest = menuItemInit(setNotice, "Test button");
  MenuItem* setNoticeContact = menuItemInit(setNotice, "Update info");
  MenuItem* setPair = menuItemInit(set, "Pair button");
  MenuItem* setDisable = menuItemInit(set, "Disable system");
  return(menu);
}

/**
 * @brief Main of the program
 * @param argc Number of args
 * @param argv Array of args
 * @return Status
 */
int main(int argc, char** argv) {
  printf("Test executable.\n");
  Menu* menu = createMenus();
  menuItemPrintTree(menu->root);
  menuDestroy(menu);
  return(1);
}
