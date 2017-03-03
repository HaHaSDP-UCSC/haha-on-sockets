#ifndef _HA_BASECOM
#define _HA_BASECOM

#include "devtools.h"
#include "network.h"
#include "base.h"

/* Base Communication */
/* These functions will call the functions in network.h
*  The network.h file is the actual implementation of network comm.
*/
/* init_network()
* Initialize any settings that are needed
* Pass it off to the device's init
*/
void init_network(); //unknown needed params

/* sendToBase()
*  Get the packet ready and send as a char* to the devices send
*/
bool sendToBase(Packet *p, Base dest);
bool sendPacket(Packet *p, char* dest);
bool recvPacket(Packet *p);
//Packet* procRecv(char* data); //received from networkdevice.c
bool networkUp();
#endif
