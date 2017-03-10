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

Menu* initMenus(void);
void* jumpToRoot(Menu* menu);

#endif // _HA_INIT_
