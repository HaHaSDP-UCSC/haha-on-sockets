/**
 * @file init.c
 * @brief Initialization file
 * @author August Valera (avalera)
 * @version
 * @date 2017-03-07
 */

#include "init.h"

void initBase(Base* base, char* fileName) {
    printv("Reading base data.\n");
    bzero(base, sizeof(base));
    if(base) {
        strcpy(base->fileName, fileName);
        FILE* file = fopen(base->fileName, "r");
        char key[128];
        char value[128];
        if(file) {
            while(fscanf(file, "%s: %s\n", key, value) == 2) {
                if(streq(key, "firstName")) {
                    strcpy(base->firstName, value);
                } else if(streq(key, "lastName")) {
                    strcpy(base->lastName, value);
                } else if(streq(key, "phone")) {
                    strcpy(base->phone, value);
                } else if(streq(key, "homeAddr")) {
                    strcpy(base->homeAddr, value);
                } else {
                    printe("Invalid key found in storage file %s: %s\n",
                            base->fileName, key);
                }
            }
        } else {
            printv("No storage file found: %s\n", base->fileName);
            strcpy(base->firstName, "John");
            strcpy(base->lastName, "Smith");
            strcpy(base->phone, "111-111-1111");
            strcpy(base->homeAddr, "1156 High St, Santa Cruz, CA 95060");
        }
        //strcpy(base->addr, "127.0.0.1");
        writeBase(base);
    }
}

void writeBase(Base* base) {
    printv("Writing base data.\n");
    if(base) {
        FILE* file = fopen(base->fileName, "w");
        if(file) {
            fprintf(file, "%s: %s\n", "firstName", base->firstName);
            fprintf(file, "%s: %s\n", "lastName", base->lastName);
            fprintf(file, "%s: %s\n", "phone", base->phone);
            fprintf(file, "%s: %s\n", "homeAddr", base->homeAddr);
            fclose(file);
        } else {
            printe("Error writing to storage file: %s\n", base->fileName);
        }
    }
}

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
