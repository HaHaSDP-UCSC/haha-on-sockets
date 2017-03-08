/**
 * @file basecomm.c
 * @brief Application layer implementation
 * @author
 * @version
 * @date 2017-03-07
 */

#include "halib.h"
#include "basecomm.h"
#include "networkdevice.h"
#include "baseopcode.h"

//TODO unknown needed params
ebool init_network(char *listenport) {
    _init_network(listenport);
    return TRUE;
}

/**
 *  Get the packet ready and send as a char * to the device to send.
 *  TODO WHAT IS THIS?
 */
ebool sendToBase(Packet *p, Base dest) {
    return FALSE; //TODO fix.
}

/**
 * Take the packet and convert it to a single char * and send to network device
 *  Return the return value from network device
 */
ebool sendPacket(Packet *p, char* dest) {

    _send_packet(p->data, strlen(p->data), "127.0.0.1", p->dst); //TODO turn packet into sendable.
    return FALSE; //TODO fix.
}

/**
 * Will be called by networkdevice.c
 */
ebool recvPacket(Packet *p) {
    return _recv_packet(p->data, BUFFERSIZE); // TODO fix
}

/**
 * Processes received packets. They are sorted based on their opcode.
 */
ebool processPacket(Packet *p) {
	char opcode = p->opcode;
	switch(opcode)
	case PING_REQUEST:
		break;
	case HELP_REQUEST:
		break;
	case HELP_RESPONSE:
		break;
	case HELP_FROM_ANYONE_REQUEST:
		break;
	case HELP_FROM_ANYONE_RESPONSE:
		break;
	case FIND_HOPS_REQUEST:
		break;
	case FIND_HOPS_RESPONSE:
		break;
	case FIND_NEIGHBORS_REQUEST:
		break;
	case FIND_NEIGHBORS_RESPONSE:
		break;
	case FRIEND_REQUEST:
		break;
	case FRIEND_RESPONSE:
		break;
	case UNFRIEND_REQUEST:
		break;
	default:
		//TODO Undefined.
		return ERROR;
	return TRUE;
}


//TODO For later
ebool networkUp() {
    return FALSE; //TODO fix.
}
