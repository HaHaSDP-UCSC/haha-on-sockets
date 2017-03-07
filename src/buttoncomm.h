/**
 * @file buttoncomm.h
 * @brief
 * @author
 * @version
 * @date 2017-03-07
 */


/* This will get the packet ready and send to buttondevice.c specific */
#ifndef _HA_BUTTONCOM_
#define _HA_BUTTONCOM_

#include "devtools.h"
#include "buttonnetwork.h"
#include "button.h"

//sockets: probably called directly in loop (instead of interrupt)
void init_button();
bool pollButton(Button *b);
bool recvAlert(Beacon *bc); //buttondevice will call this

//Some helper functions for processing beacon messages
void procBeacon(Beacon *bc, char* buff);
//etc

#endif // _HA_BUTTONCOMM_
