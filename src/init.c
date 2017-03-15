/**
 * @file init.c
 * @brief Initialization file
 * @author August Valera (avalera)
 * @version
 * @date 2017-03-07
 */

#include "init.h"

void initBase(Base* base, char* fileName) {
    int i;
    if(base) {
        strcpy(base->fileName, fileName);
        printv("Reading base data from file: %s\n", base->fileName);
        FILE* file = fopen(base->fileName, "r");
        char line[128];
        char key[128];
        char value[128];
        for(i = 0; i < 128; i++) base->friends[i] = 0;
        if(file) {
            while(fgets(line, 128, file)) {
                printd("line: '%s'\n", line);
                if(sscanf(line, "%[^:]%*c %[^\n]%*c", key, value) == 2) {
                    if(streq(key, "firstName")) {
                        strcpy(base->firstName, value);
                    } else if(streq(key, "lastName")) {
                        strcpy(base->lastName, value);
                    } else if(streq(key, "phone")) {
                        strcpy(base->phone, value);
                    } else if(streq(key, "homeAddr")) {
                        strcpy(base->homeAddr, value);
                    } else if(streq(key, "friends")) {
                        char* friend = strtok(value, " ");
                        int i = 0;
                        while(friend) {
                            base->friends[i++] = atoi(friend);
                            friend = strtok(NULL, " ");
                        }
                    } else printe("Invalid key found in storage file %s: %s\n",
                            base->fileName, key);
                } else(printe("Bad line found in storage file: %s\n", line));
            }
            fclose(file);
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
            fprintf(file, "%s: ", "friends");
            int i, friend;
            for(i = 0; i < 128; i++)
                if((friend = base->friends[i]) > 0)
                    fprintf(file, "%d ", friend);
            fprintf(file, "\n");
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
    MenuItem* contacts = menuItemInit(mm, "Contact list");
    contacts->onClick = listFriends;
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
    MenuItem* simulate = menuItemInit(root, "Simulate req");
    simulate->onClick = jumpToEvent;
    eventButton = menuItemInit(root, "__BUTTON__");
    eventButton->active = false;
    MenuItem* eventAccept = menuItemInit(eventButton, "__YES__");
    eventAccept->onView = eventButtonView;
    eventAccept->onClick = eventButtonAccept;
    MenuItem* eventDeny = menuItemInit(eventButton, "__NO__");
    eventDeny->onView = eventButtonView;
    eventDeny->onClick = eventButtonDeny;

    menu->current = menu->root->child;
    return(menu);
}

void* jumpToRoot(Menu* menu) {
    menu->current = menu->root->child;
    return(NULL);
}

// Call this function (or copy the body of it)
// to trigger the alert screen
void* jumpToEvent(Menu* menu) {
    menu->current = eventButton->child;
    menu->current->onView(menu);
    return(NULL);
}

void* listFriends(Menu* menu) {
    char title[16];
    MenuItem* this = menu->current;
    while(this->child)
        menuItemDestroy(this->child);
    int i, j = 0;
    for(i = 0; i < 128; i++)
        if(self.friends[i] != 0) {
            sprintf(title, "%d: Port %d", j++, self.friends[i]);
            menuItemInit(this, title);
        }
    MenuItem* addFriend = menuItemInit(this, "Add Friend");
    addFriend->onClick = addFriendInput;
    menuItemOnClickDefault(menu);
    return(NULL);
}

void* eventButtonView(Menu* menu) {
    char* name = "John Smith"; // TODO put requester's name
    lcdClear();
    lcdSetLine(0, "HELP REQUEST");
    lcdSetLine(1, name);
    lcdSetLine(2, "Help Them");
    lcdSetLine(3, "Dismiss");
    int this = 3, other = 2;
    if(menu->current->next)
        this = 2, other = 3;
    lcdSetChar(this, LCD_COLS - 1, '>');
    lcdSetChar(other, LCD_COLS - 1, '-');
    return(NULL);
}

void* eventButtonAccept(Menu* menu) {
    // TODO code to accept help request
    printd("Help request accepted\n");
    jumpToRoot(menu);
    return(NULL);
}

void* eventButtonDeny(Menu* menu) {
    // TODO code to deny help request
    printd("Help request denied :(\n");
    jumpToRoot(menu);
    return(NULL);
}

void* addFriendInput(Menu* menu) {
    printf("Enter in your friend's port number: ");
    int friend;
    if(scanf("%d", &friend) == 1) {
        if(friend > 0) {
            int i;
            for(i = 0; i < 128; i++)
                if(self.friends[i] == 0)
                    break;
            self.friends[i] = friend;
        } else printe("Invalid port number provided");
    } else printe("Invalid input provided");
    jumpToRoot(menu);
    return(NULL);
}
