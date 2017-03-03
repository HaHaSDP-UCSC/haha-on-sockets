/* App layer implementation */
#include "devtools.h"
#include "basecomm.h"

void init_network(); //unknown needed params

/* sendToBase()
*  Get the packet ready and send as a char* to the devices send
*/
bool sendToBase(Packet *p, Base dest){

}

/* Take the packet and conver it to a single char and send to networkdevice
*  Return the return value from networkdevice
*/
bool sendPacket(Packet *p, char* dest){

}

//Will be called by networkdevice.c
bool recvPacket(Packet *p){

}

//For later
bool networkUp();
