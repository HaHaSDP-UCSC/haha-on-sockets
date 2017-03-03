/* Device specific implementation of button communication */
#ifndef _HA_BUTTONNET
#define _HA_BUTTONNET
#include "../devtools.h"
#include "buttonnetwork.h"

//This function will handle all sending of messages. Just make approparite
bool _send_beacon(char* msg);
void _recv_beacon(char* msg); //not sure how bluetooth messages will come in

//Other specific stuff

#endif
