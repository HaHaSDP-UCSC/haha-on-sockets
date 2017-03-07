/**
 * @file basecomm.h
 * @brief Base communication
 * @author
 * @version
 * @date 2017-03-07
 *
 * These functions will call the functions in network.h
 * The network.h file is the actual implementation of network comm.
 */



#ifndef _HA_BASECOMM
#define _HA_BASECOMM

#include "devtools.h"
#include "network.h"
#include "base.h"

#define BUFFERSIZE 1000

/* init_network()
 * Initialize any settings that are needed
 * Pass it off to the device's init
 */
bool init_network(char *listenport); //unknown needed params

/* sendToBase()
 *  Get the packet ready and send as a char* to the devices send
 */
bool sendToBase(Packet *p, Base dest); //TODO what is this for?
bool sendPacket(Packet *p, char* dest);
bool recvPacket(Packet *p);
//Packet* procRecv(char* data); //received from networkdevice.c
bool networkUp();
#endif
