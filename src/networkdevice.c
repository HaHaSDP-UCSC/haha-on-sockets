/* Implementation of network device specific communication */
/* Functions to call in upper layer:
*  bool recvPacket(Packet *p);
*
*/
#include "networkdevice.h"
#include "basecomm.h"

/* Do the init stuff */
void _init_network(){

}

/* Receiving side of basecomm.c
*  Send the data to the address specified
*  Return 0 for failure, otherwise any number
*/
bool _data_send(char* data, char* addr){

}

/* Take a packet from the network layer and construct a Packet and populate
*  send to recvPacket() in the upper layer. If the packet parses correctly
*  the return is != 0, otherwise there was an error and we need to not ack
*  the packet so that it is sent again (assumption made about how network works)
*/
bool _recv_packet(char* data){

}
