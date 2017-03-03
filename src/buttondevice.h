/* Impelmentation of the button communication */
/* For Linux sim: TCP/IP */
#ifndef _HA_BUTTONDEVICE
#define _HA_BUTTONDEVICE

#include "button.h"
#include "buttonnetwork.h"

/* Must Implement for App */
void _init_button();
bool _recv_alert(char* data); //from sockets
bool _poll_button(char *b); //

/* Other Functions for device specific networking */
//Socket stuff

#endif
