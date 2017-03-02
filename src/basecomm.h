#ifndef _HA_BASECOM
#define _HA_BASECOM

#include "devtools.h"
#include "network.h"
#include "base.h"

/* Base Communication */
/* These functions will call the functions in network.h
*  The network.h file is the actual implementation of network comm.
*/
/* init()
* Initialize any settings that are needed
* Just pass it off to the device's init
*/
void init(); //unknown needed params
bool sendToBase(Packet *p, Base dest);
bool sendPacket(Packet *p, baseaddr dest);

bool networkUp();
#endif
