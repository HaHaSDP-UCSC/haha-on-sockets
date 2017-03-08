/**
 * @file init.c
 * @brief Initialization file
 * @author August Valera (avalera)
 * @version
 * @date 2017-03-07
 */

#include "init.h"

Menu* initMenus(void) {
    Menu* menu = menuInit();
    MenuItem* root = menu->root;
    MenuItem* mm = menuItemInit(root, "Main Menu");
    MenuItem* contacts = menuItemInit(mm, "Contact list");
    MenuItem* user = menuItemInit(mm, "User info");
    MenuItem* userId = menuItemInit(user, "User ID");
    MenuItem* userName = menuItemInit(user, "User name");
    MenuItem* userAddr = menuItemInit(user, "User address");
    MenuItem* userPhone = menuItemInit(user, "User phone");
    MenuItem* set = menuItemInit(mm, "Device settings");
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
    menuItemInit(root, "Activity (XXX)");
    menuItemInit(root, "Network (XXX)");
    menuItemInit(root, "Button (XXX)");
    menu->current = menu->root->child;
    return(menu);
}
