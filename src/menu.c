/**
 * @file menu.c
 * @brief Menu and MenuItem library functions
 *
 * @author August Valera (avalera)
 * @version
 * @date 2017-02-28
 */

#include "menu.h"

/**
 * @brief Constructor for global menu
 * @return New Menu
 */
Menu* menuInit(void) {
    Menu* this = calloc(1, sizeof(Menu));
    this->root = menuItemInit(NULL, "MENU_ROOT");
    this->root->visible = false;
    this->current = NULL;
    return(this);
}

/**
 * @brief Moves menu cursor in given direction
 * @param menu Menu object containing cursor
 * @param direct Direction to move
 * @return 0 on success, 1 on invalid direction, -1 on error
 */
int menuMove(Menu* menu, MenuDirection direct) {
    if(menu && menu->current) {
        switch(direct) {
            case MENU_LEFT:
                // Root node should not be accessible
                if(menu->current->parent && menu->current->parent->parent) {
                    menu->current = menu->current->parent;
                } else return 1;
                break;
            case MENU_RIGHT:
                if(menu->current->child) {
                    menu->current = menu->current->child;
                } else return 1;
                break;
            case MENU_UP:
                if(menu->current->prev) {
                    menu->current = menu->current->prev;
                } else if(MENU_WRAP && menu->current->next) {
                    // Find last item
                    MenuItem* last;
                    for(last = menu->current->next; last->next;
                            last = last->next);
                    menu->current = last;
                } else return 1;
                break;
            case MENU_DOWN:
                if(menu->current->next) {
                    menu->current = menu->current->next;
                } else if(MENU_WRAP && menu->current->prev) {
                    menu->current = menu->current->parent->child;
                } else return 1;
        }
    } else return -1;
}

int menuSetLcd(Menu* menu) {
    int lines = 0;
    if(menu && menu->current) {
        lcdClear();
        MenuItem* this = menu->current;
        for(lines = 0; lines < LCD_LINES; lines++) {
            lcdSetLine(lines, this->value);
            if(this->next == NULL) {
                this = this->parent->child;
            } else this = this->next;
            if(this == menu->current) break;
        }
    } else return(-1);
    return(lines);
}

/**
 * @brief Destructor for global menu
 * @param this Menu to destroy
 * @return 0 on success, else error
 */
int menuDestroy(Menu* this) {
    if(this) {
        menuItemDestroy(this->root);
        free(this);
    } else return(-1);
    return(0);
}

/**
 * @brief Constructor for menu item, inserted in list of parent
 * @param parent
 * @return New MenuItem
 */
MenuItem* menuItemInit(MenuItem* parent, char* value) {
    MenuItem* this = calloc(1, sizeof(MenuItem));
    this->onEnter = NULL;
    this->onExit = NULL;
    menuItemSetValue(this, value);
    this->visible = true;
    this->parent = parent;
    this->child = NULL;
    this->next = NULL;
    this->prev = NULL;
    if(this->parent) { // Should be true except for root
        if(this->parent->child) { // Not first child
            this->prev = this->parent->child;
            while(this->prev->next) this->prev = this->prev->next;
            this->prev->next = this;
        } else {
            this->parent->child = this;
        }
    }
    return(this);
}

/**
 * @brief Sets value of MenuItem
 * @param this MenuItem to edit
 * @param value String value to copy over
 * @return 0 on success, else error
 */
int menuItemSetValue(MenuItem* this, char* value) {
    if(this && value) {
        strcpy(this->value, value);
    } else return(-1);
    return(0);
}

/**
 * @brief Prints out tree representation of MenuItem and children
 * @param this Root of tree
 */
void menuItemPrintTree(MenuItem* this) {
    if(this)
        menuItemPrintTreeHelper(this, 0);
}

/**
 * @brief Recursive helper of menuItemPrintTree()
 * @param this Root of tree
 * @param level Level of recursion we are in
 */
void menuItemPrintTreeHelper(MenuItem* this, int level) {
    if(this) {
        int i;
        for(i = 0; i < level; i++)
            printf("\t");
        if(this->visible) printf("> ");
        else printf("X ");
        printf("%s\n", this->value);
        MenuItem* child;
        for(child = this->child; child; child = child->next)
            menuItemPrintTreeHelper(child, level + 1);
    }
}

/**
 * @brief Destructor for MenuItem, recursive on children
 * @param this MenuItem to destroy
 * @return 0 on success, else error
 */
int menuItemDestroy(MenuItem* this) {
    if(this) {
        if(MENU_DBUG) printf("DELETE %s\n", this->value);
        while(this->child) {
            menuItemDestroy(this->child);
        }
        if(this->prev) { // Not first child
            this->prev->next = this->next;
        } else {
            if(this->next) this->next->prev = NULL;
            if(this->parent) this->parent->child = this->next;
        }
        free(this);
    } else return(-1);
    return(0);
}
