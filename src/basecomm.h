/**
 * @file basecomm.h
 * @brief Base communication
 * @author Kevin Lee
 * @version
 * @date 2017-03-07
 *
 * These functions will call the functions in network.h
 * The network.h file is the actual implementation of network comm.
 */

#ifndef _HA_BASECOMM
#define _HA_BASECOMM

#include "halib.h"
#include "network.h"
#include "base.h"
#include "baseopcode.h"

#define BUFFERSIZE 1000

/* init_network()
 * Initialize any settings that are needed
 * Pass it off to the device's init
 */
ebool init_network(char *listenport); //unknown needed params

/* sendToBase()
 *  Get the packet ready and send as a char* to the devices send
 */
ebool sendPacket(Packet *p, Base *dest);
ebool recvPacket(Packet *p, Base *src);
ebool processPacket(Packet *p);
//Packet* procRecv(char* data); //received from networkdevice.c
ebool networkUp();
#endif
