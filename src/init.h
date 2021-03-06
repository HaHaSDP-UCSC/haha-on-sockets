/**
 * @file init.h
 * @brief Initialization headers
 * @author August Valera (avalera)
 * @version
 * @date 2017-03-07
 */

#ifndef _HA_INIT_
#define _HA_INIT_

#include "halib.h"
#include "menu.h"
#include "base.h"

// Global variables
Menu *menu;
char *listenPort;
char *destinationPort;
Base self;
MenuItem *eventButton;
ebool acceptReq; //TODO user input needs to block.

void initBase(Base* base, char* fileName);
void writeBase(Base* base);

Menu* initMenus(void);
void* jumpToRoot(Menu* menu);
void* jumpToEvent(Menu* menu);
void* listFriends(Menu* menu);
void* editFriend(Menu* menu);
void* deleteFriend(Menu* menu);
void* editUserInfo(Menu* menu);
void* viewUserInfo(Menu* menu);
void* eventButtonView(Menu* menu);
void* eventButtonAnswer(Menu* menu);
void* addFriendInput(Menu* menu);

#endif // _HA_INIT_
