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

//TODO unknown needed params
bool init_network(char *listenport) {
	_init_network(listenport);
	return TRUE;
}

/**
 *  Get the packet ready and send as a char* to the device to send.
 *  TODO WHAT IS THIS?
 */
bool sendToBase(Packet *p, Base dest) {
	return FALSE; //TODO fix.
}

/**
 * Take the packet and convert it to a single char and send to network device
 *  Return the return value from network device
 */
bool sendPacket(Packet *p, char* dest) {

	_send_packet(p->data, strlen(p->data), "127.0.0.1", p->dst); //TODO turn packet into sendable.
	return FALSE; //TODO fix.
}

/**
 * Will be called by networkdevice.c
 */
bool recvPacket(Packet *p) {
	if (_recv_packet(p->data, BUFFERSIZE) == TRUE) {
		return TRUE;
	}
	return FALSE; //TODO fix.
}

//TODO For later
bool networkUp() {
	return FALSE; //TODO fix.
}
