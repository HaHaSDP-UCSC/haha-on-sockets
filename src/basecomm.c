/* App layer implementation */
#include "devtools.h"
#include "basecomm.h"

void init_network(); //unknown needed params

/* sendToBase()
*  Get the packet ready and send as a char* to the device to send.
*/
bool sendToBase(Packet *p, Base dest){

}

/* Take the packet and convert it to a single char and send to network device
*  Return the return value from network device
*/
bool sendPacket(Packet *p, char* dest){

}

//Will be called by networkdevice.c
bool recvPacket(Packet *p){

}

//For later
bool networkUp();
