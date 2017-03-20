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
    MenuItem* temp;
    Menu* menu = menuInit();
    MenuItem* root = menu->root;
    MenuItem* mm = menuItemInit(root, "Main Menu");
    MenuItem* contacts = menuItemInit(mm, "Contact list");
    contacts->onClick = listFriends;
    MenuItem* user = menuItemInit(mm, "User info");
    temp = menuItemInit(user, "__USERPORT__");
    temp->onView = viewUserInfo;
    temp = menuItemInit(user, "__USERNAME__");
    temp->onView = viewUserInfo;
    temp->onClick = editUserInfo;
    temp = menuItemInit(user, "__USERADDR__");
    temp->onView = viewUserInfo;
    temp->onClick = editUserInfo;
    temp = menuItemInit(user, "__USERCALL__");
    temp->onView = viewUserInfo;
    temp->onClick = editUserInfo;
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
    menuItemInit(root, "Activity (%dh)");
    menuItemInit(root, "Network (%dh)");
    menuItemInit(root, "Button (%dh)");
    MenuItem* simulate = menuItemInit(root, "Simulate req");
    simulate->onClick = jumpToEvent;
    eventButton = menuItemInit(root, "__BUTTON__");
    eventButton->active = false;
    MenuItem* eventAccept = menuItemInit(eventButton, "__YES__");
    eventAccept->onView = eventButtonView;
    eventAccept->onClick = eventButtonAnswer;
    MenuItem* eventDeny = menuItemInit(eventButton, "__NO__");
    eventDeny->onView = eventButtonView;
    eventDeny->onClick = eventButtonAnswer;

    menu->current = menu->root->child;
    return(menu);
}

void* jumpToRoot(Menu* menu) {
    menu->current = menu->root->child;
    return(NULL);
}

// User date code

void* listFriends(Menu* menu) {
    char title[16];
    MenuItem* this = menu->current;
    while(this->child)
        menuItemDestroy(this->child);
    int i, j = 0;
    for(i = 0; i < 128; i++)
        if(self.friends[i] != 0) {
            sprintf(title, "%d: Port %d", j++, self.friends[i]);
            MenuItem* friend = menuItemInit(this, title);
            MenuItem* friendDelete = menuItemInit(friend, "Delete");
            friendDelete->onClick = deleteFriend;
            MenuItem* friendEdit = menuItemInit(friend, "Edit");
            friendEdit->onClick = editFriend;
        }
    MenuItem* addFriend = menuItemInit(this, "Add Friend");
    addFriend->onClick = addFriendInput;
    menuItemOnClickDefault(menu);
    return(NULL);
}

void* editFriend(Menu* menu) {
    int idx = -1, friend = -1;
    if(sscanf(menu->current->parent->value, "%d: ", &idx) != 1) {
        printe("editFriend could not parse index");
        return(NULL);
    }
    friend = self.friends[idx];
    printf("Edit friend %d (currently %d): ", idx, friend);
    if(scanf("%d", &friend) == 1)
        self.friends[idx] = friend;
    jumpToRoot(menu);
}

void* deleteFriend(Menu* menu) {
    int idx = -1;
    if(sscanf(menu->current->parent->value, "%d: ", &idx) != 1) {
        printe("editFriend could not parse index");
        return(NULL);
    }
    for(;idx < 127; idx++)
        self.friends[idx] = self.friends[idx + 1];
    jumpToRoot(menu);
}

void* viewUserInfo(Menu* menu) {
    char buffer[LCD_COLS];
    bzero(&buffer, LCD_COLS);
    lcdClear();
    lcdSetLine(3, "v More    Edit >");
    if(streq(menu->current->value, "__USERPORT__")) {
        lcdSetLine(0, "User Port");
        lcdSetLine(1, listenPort);
        lcdSetLine(3, "v More");
    } else if(streq(menu->current->value, "__USERNAME__")) {
        lcdSetLine(0, "User Name");
        lcdSetLine(1, self.firstName);
        lcdSetLine(2, self.lastName);
    } else if(streq(menu->current->value, "__USERADDR__")) {
        lcdSetLine(0, "User Address");
        int len = strlen(self.homeAddr);
        if(len > LCD_COLS) len = LCD_COLS;
        strncpy(buffer, self.homeAddr, len);
        lcdSetLine(1, buffer);
        bzero(&buffer, LCD_COLS);
        if((len = strlen(self.homeAddr)) > LCD_COLS) {
            len -= LCD_COLS;
            if(len > LCD_COLS) len = LCD_COLS;
            strncpy(buffer, &self.homeAddr[LCD_COLS], len);
            lcdSetLine(2, buffer);
        }
    } else if(streq(menu->current->value, "__USERCALL__")) {
        lcdSetLine(0, "User Phone");
        lcdSetLine(1, self.phone);
    } else {
        printe("viewUserInfo called from invalid menu item");
    }
    lcdUpdate();
}

void* editUserInfo(Menu* menu) {
    char buffer[1024];
    bzero(&buffer, 1024);
    if(streq(menu->current->value, "__USERNAME__")) {
        printf("Enter in your first name (currently %s): ", self.firstName);
        fgets(buffer, 17, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        //scanf("%s", buffer);
        if(strlen(buffer) != 0) strncpy(self.firstName, buffer, 17);
        printf("Enter in your last name (currently %s): ", self.lastName);
        fgets(buffer, 17, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        //scanf("%s", buffer);
        if(strlen(buffer) != 0) strncpy(self.lastName, buffer, 17);
    } else if(streq(menu->current->value, "__USERADDR__")) {
        printf("Enter in your address (currently %s): ", self.homeAddr);
        fgets(buffer, 75, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        //scanf("%s", buffer);
        if(strlen(buffer) != 0) strncpy(self.homeAddr, buffer, 75);
    } else if(streq(menu->current->value, "__USERCALL__")) {
        printf("Enter in your address (currently %s): ", self.phone);
        fgets(buffer, 16, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        //scanf("%s", buffer);
        if(strlen(buffer) != 0) strncpy(self.phone, buffer, 16);
    } else {
        printe("viewUserInfo called from invalid menu item");
    }
}

// Bluetooth button code

// @TODO Jamie Call this function (or copy the body of it)
// to trigger the alert screen
void* jumpToEvent(Menu* menu) {
    menu->current = eventButton->child;
    menu->current->onView(menu);
    return(NULL);
}

void* eventButtonView(Menu* menu) {
    char* name = "John Smith"; // @TODO Jamie put requester's name
    // Recommendation: put a char[] in the Menu
    // struct to hold the name. Before running the
    // code in jumpToEvent() to display the alert,
    // strcpy() the name of the requester into that
    // char[]. Then you can set it here.
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
    lcdUpdate();
    return(NULL);
}

void* eventButtonAnswer(Menu* menu) {
    if(menu->current->next) {
        // Accept
        printd("Help request accepted\n");
        acceptReq = TRUE;
    } else {
        // Deny
        printd("Help request denied :(\n");
        acceptReq = FALSE;
    }
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
