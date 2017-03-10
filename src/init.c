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
    menuItemInit(mm, "Contact list");
    MenuItem* user = menuItemInit(mm, "User info");
    menuItemInit(user, "User ID");
    menuItemInit(user, "User name");
    menuItemInit(user, "User address");
    menuItemInit(user, "User phone");
    MenuItem* set = menuItemInit(mm, "Device settings");
    menuItemInit(set, "Office mode");
    MenuItem* setAlert = menuItemInit(set, "Alert settings");
    menuItemInit(setAlert, "Sound");
    menuItemInit(setAlert, "Lights");
    MenuItem* setTest = menuItemInit(set, "Test button");
    menuItemInit(setTest, "BUTTON TEST");
    menuItemInit(setTest, "Press button now");
    menuItemInit(setTest, "to test signal.");
    MenuItem* setTestStop = menuItemInit(setTest, "Stop testing");
    setTestStop->onClick = jumpToRoot;
    MenuItem* setNotice = menuItemInit(set, "Notice settings");
    menuItemInit(setNotice, "Test button");
    menuItemInit(setNotice, "Update info");
    menuItemInit(set, "Pair button");
    menuItemInit(set, "Disable system");
    menuItemInit(root, "Activity (XXX)");
    menuItemInit(root, "Network (XXX)");
    menuItemInit(root, "Button (XXX)");
    MenuItem* eventButton = menuItemInit(root, "__BUTTON__");
    eventButton->active = false;
    menuItemInit(eventButton, "Help request");
    menuItemInit(eventButton, "INSERT NAME");
    menu->current = menu->root->child;
    return(menu);
}

void* jumpToRoot(Menu* menu) {
    menu->current = menu->root->child;
    return NULL;
}
