/**
 * @file buttondevice.h
 * @brief Implementation of the button communication
 * @author
 * @version
 * @date 2017-03-07
 *
 * Uses TCP/IP
 */

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
