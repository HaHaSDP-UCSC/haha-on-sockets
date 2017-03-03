/* This will get the packet ready and send to buttondevice.c specific */
#ifndef _HA_BUTTONCOM
#define _HA_BUTTONCOM

#include "devtools.h"
#include "buttonnetwork.h"
#include "button.h"

//sockets: probably called directly in loop (instead of interrupt)
void init_button();
bool pollButton(Button *b);
bool recvAlert(Beacon *bc);

//Some helper functions for processing beacon messages
void procBeacon(Beacon *bc, char* buff);
//etc

#endif
