/**
 * @file basecomm.c
 * @brief Application layer implementation
 * @author
 * @version
 * @date 2017-03-07
 */

#include "basecomm.h"
#include "networkdevice.h"
#include "baseopcode.h"

#define MINPACKETSIZE 4 //TODO define better

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
 * Take the packet and convert it to a char * and send to network device
 * Return the return value from network device.
 */
ebool sendPacket(Packet *p, char* dest) {

    _send_packet(p->data, strlen(p->data), "127.0.0.1", p->dst); //TODO turn packet into sendable.
    return FALSE; //TODO fix.
}

/**
 * Checks for a packet on the network layer. This then processes the packet.
 */
ebool recvPacket(Packet *p, char *src) {
	char buffer[BUFFERSIZE];
	int receivelen;
	if ((receivelen = _recv_packet(buffer, BUFFERSIZE)) <= 0) {
		convertFromDataToPacket(p, buffer, receivelen);
	}
	//return TRUE;
	return FALSE;
}

/**
 * Processes received data from network. Converts into packet form.
 * They are sorted based on their opcode.
 */
ebool convertFromDataToPacket(Packet *p, char *data, int datalen) {
	int offset = STATICDATAOFFSET;
	int n = 0;
	if (datalen < MINPACKETSIZE) {
		//Malformed packet.
		printe("Packet too small.\n");
		return ERROR;
	}
	char opcode = data[0];
	char flags = data[1];
	switch(opcode)
	case PING_REQUEST:
		printd("PING OPCODE.\n");
	if (!IS_ACK(flags)) {
		p->DESTUID = data[offset] << 8 + data[++offset]; //Add DESTUID to packet.
	} else {
		p->DESTUID = data[offset] << 8 + data[++offset]; //Add SRCUID to packet.
		if ((n = strlen(&data[offset]) < MAXNAME)) {
			strcpy(p->SRCNAME, &data[offset += n]); //Add SRCNAME to packet.
		} else {
			printe("Malformed String.\n");
		}
	}
		break;
	case HELP_REQUEST:
		printd("HELP REQ OPCODE.\n");
	//TODO FIX
	if (!IS_ACK(flags)) {
		//TODO FIX
		//Add SRCUID to packet.
		//Add SRCHOMEADDR to packet.
		//Add SRCPHONE to packet.
	} else {
		//TODO FIX
		//Add SRCUID to packet.
	}
		break;
	case HELP_RESPONSE:
		printd("HELP RESPONSE OPCODE.\n");
	if (!IS_ACK(flags)) {
		//TODO FIX
		//Add SRCUID to packet.
	} else {
		//TODO FIX
		//Add SRCUID to packet.
	}
		break;
	case HELP_FROM_ANYONE_REQUEST:
		printd("HELP FROM ANYONE REQUEST OPCODE.\n");
		//Add SRCUID to packet.
		//Add TTL to packet.
		//Add SRCNAME to packet.
		break;
	case HELP_FROM_ANYONE_RESPONSE:
		printd("HELP FROM ANYONE RESPONSE OPCODE.\n");
	if (!IS_ACK(flags)) {
		//TODO FIX
		//Add SRCUID to packet.
		//Add DESTUID to packet.
		//Add SRCNAME to packet.
	} else {
		//TODO FIX
		//Add SRCUID to packet.
		//Add DESTUID to packet.
		//Add SRCHOMEADDR to packet.
		//Add SRCPHONE to packet.
	}
		break;
	case FIND_HOPS_REQUEST:
		printd("FIND HOPS REQUEST OPCODE.\n");
		//Add ORIGINUID to packet.
		//Add TTL to packet.
		break;
	case FIND_HOPS_RESPONSE:
		printd("FIND HOPS RESPONSE OPCODE.\n");
	if (!IS_ACK(flags)) {
		//TODO FIX
		//Add SRCUID to packet.
		//Add ORIGINUID to packet.
		//Add TTL to packet.
	} else {
		//TODO FIX
		//Add SRCUID to packet.
		//Add DESTUID to packet.
	}
		break;
	case FIND_NEIGHBORS_REQUEST:
		printd("FIND NEIGHBORS REQUEST OPCODE.\n");
		//Add ORIGINUID to packet.
		//Add TTL to packet.
		break;
	case FIND_NEIGHBORS_RESPONSE:
		printd("FIND NEIGHBORS RESPONSE OPCODE.\n");
	if (!IS_ACK(flags)) {
		//TODO FIX
		//Add SRCUID to packet.
		//Add ORIGINUID to packet.
		//Add TTL to packet.
		//Add SRCNAME to packet.
	} else {
		//TODO FIX
		//Add SRCUID to packet.
		//Add DESTUID to packet.
	}
		break;
	case FRIEND_REQUEST:
		printd("FRIEND REQUEST OPCODE.\n");
	if (!IS_ACK(flags)) {
		//TODO FIX
		//Add SRCUID to packet.
		//Add DESTUID to packet.
		//Add SRCNAME to packet.
	} else {
		//TODO FIX
		//Add SRCUID to packet.
		//Add DESTUID to packet.
		//Add SRCNAME to packet.
	}
		break;
	case FRIEND_RESPONSE:
		printd("FRIEND RESPONSE OPCODE.\n");
	if (!IS_ACK(flags)) {
		//TODO FIX
		//Add SRCUID to packet.
		//Add DESTUID to packet.
	} else {
		//TODO FIX
		//Add SRCUID to packet.
		//Add DESTUID to packet.
	}
		break;
	case UNFRIEND_REQUEST:
		printd("UNFRIEND REQUEST OPCODE.\n");
	if (!IS_ACK(flags)) {
		//TODO FIX
		//Add SRCUID to packet.
		//Add DESTUID to packet.
	} else {
		//TODO FIX
		//Add SRCUID to packet.
		//Add DESTUID to packet.
	}
		break;
	default:
		printe("Unhandled OPCODE.\n");
		//TODO Undefined.
		return ERROR;
	return TRUE;
}

ebool processPacket(Packet *p) {
	
}

//TODO For later
ebool networkUp() {
    return FALSE; //TODO fix.
}
