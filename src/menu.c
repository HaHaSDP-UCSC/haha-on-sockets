/**
 * @file menu.c
 * @brief
 *
 * @author August Valera (avalera)
 * @version
 * @date 2017-02-28
 */

#include "menu.h"


/**
 * @brief Constructor for global menu
 *
 * @return New menu
 */
Menu* menuInit(void) {
  Menu* ret = calloc(1, sizeof(Menu));
  ret->root = menuItemInit(NULL);
  ret->current = ret->root;
  return(ret);
}


/**
 * @brief Destructor for global menu
 *
 * @param this Menu to destroy
 *
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
 *
 * @param parent
 *
 * @return
 */
MenuItem* menuItemInit(MenuItem* parent) {
  MenuItem* this = calloc(1, sizeof(MenuItem));
  this->onEnter = NULL;
  this->onExit = NULL;
  this->active = true;
  this->parent = parent;
  this->child = NULL;
  this->next = NULL;
  if(this->parent) {
    if(this->parent->child) { // Not first child
      this->prev = this->parent->child;
      while(this->prev->next) this->prev = this->prev->next;
      this->prev->next = this;
    } else {
      this->prev = NULL;
      this->parent->child = this;
    }
  }
  return(this);
}

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
