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
  Menu* ret = calloc(1, sizeof(Menu));
  ret->root = menuItemInit(NULL);
  ret->current = ret->root;
  return(ret);
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
MenuItem* menuItemInit(MenuItem* parent) {
  MenuItem* this = calloc(1, sizeof(MenuItem));
  this->onEnter = NULL;
  this->onExit = NULL;
  this->active = true;
  this->parent = parent;
  this->child = NULL;
  this->next = NULL;
  this->prev = NULL;
  if(this->parent) { // Only case this wouldn't happen is root
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
    for(int i = 0; i < level; i++)
      printf("\t");
    printf("- %s\n", this->value);
    for(MenuItem* child = this->child; child; child = child->next)
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
    while(this->child) {
      menuItemDestroy(this->child);
    }
    if(this->prev) { // Not first child
      this->prev->next = this->next;
    } else {
      this->parent->child = this->next;
    }
    free(this);
  } else return(-1);
  return(0);
}
