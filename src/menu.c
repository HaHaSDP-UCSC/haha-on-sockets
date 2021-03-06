/**
 * @file menu.c
 * @brief Menu and MenuItem library functions
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
    this->root = menuItemInit(NULL, "__ROOT__");
    this->root->active = false;
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
                } else return(1);
                break;
            case MENU_RIGHT:
                menu->current->onClick(menu);
                break;
            case MENU_UP:
                menu->current = menuItemGetPrev(menu->current);
                break;
            case MENU_DOWN:
                menu->current = menuItemGetNext(menu->current);
                break;
            default:
                return(-1);
                break;
        }
    } else return(-1);
    menu->current->onView(menu);
    return(0);
}

int menuSetLcd(Menu* menu) {
    int lines = 0;
    if(menu && menu->current) {
        lcdClear();
        MenuItem* this = menu->current;
        for(lines = 0; lines < LCD_LINES; lines++) {
            lcdSetLine(lines, this->value);
            if(this->child) {
                if(lines == 0) lcdSetChar(lines, LCD_COLS - 1, '>');
                else lcdSetChar(lines, LCD_COLS - 1, '-');
            } else if(this->onClick != menuItemOnClickDefault) {
                if(lines == 0) lcdSetChar(lines, LCD_COLS - 1, '>');
                else lcdSetChar(lines, LCD_COLS - 1, '~');
            }
            this = menuItemGetNext(this);
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
    this->onView = menuItemOnViewDefault;
    this->onClick = menuItemOnClickDefault;
    menuItemSetValue(this, value);
    this->active = true;
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
    if(this && level >= 0) {
        int i;
        for(i = 0; i < level; i++)
            printd("\t");
        if(this->active) printd("* ");
        else printd("X ");
        printd("%s\n", this->value);
        MenuItem* child;
        for(child = this->child; child; child = child->next)
            menuItemPrintTreeHelper(child, level + 1);
    }
}

MenuItem* menuItemGetNext(MenuItem* this) {
    if(this && this->parent) {
        MenuItem* current = this->next;
        while(current != this) {
            if(! current) {
                if(MENU_WRAP) current = this->parent->child;
                else return(this);
            }
            if(current->active) return(current);
            current = current->next;
        }
    }
    return(this);
}

MenuItem* menuItemGetPrev(MenuItem* this) {
    if(this && this->parent) {
        MenuItem* current = this->prev;
        while(current != this) {
            if(! current) {
                if(MENU_WRAP) current = menuItemGetLast(this);
                else return(this);
            }
            if(current->active) return(current);
            current = current->prev;
        }
    }
    return(this);
}

MenuItem* menuItemGetLast(MenuItem* this) {
    MenuItem* last;
    if(this) for(last = this; last->next; last = last->next);
    else return(this);
    return(last);
}

/**
 * @brief Destructor for MenuItem, recursive on children
 * @param this MenuItem to destroy
 * @return 0 on success, else error
 */
int menuItemDestroy(MenuItem* this) {
    if(this) {
        printd("DELETE %s\n", this->value);
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

void* menuItemOnViewDefault(Menu* menu) {
    menuSetLcd(menu);
    lcdUpdate();
    return NULL;
}

void* menuItemOnClickDefault(Menu* menu) {
    if(menu && menu->current) {
        if(menu->current->child) {
            menu->current = menu->current->child;
        } else return(1);
    } else return(-1);
    return(0);
}
