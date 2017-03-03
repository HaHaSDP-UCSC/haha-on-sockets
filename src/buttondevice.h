/* Impelmentation of the button communication */
/* For Linux sim: TCP/IP */
#ifndef _HA_BUTTONDEVICE
#define _HA_BUTTONDEVICE

#include "button.h"
#include "buttonnetwork.h"

/* Must Implement for App */
void _init_button();
bool _recv_alert(char* data); //from sockets
Beacon* _recv_beacon_up(); //Send the beacon up to the app
bool _poll_button(Button *b); //

/* Other Functions for device specific networking */
//Socket stuff

#endif
