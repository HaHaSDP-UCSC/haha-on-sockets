/**
 * @file basecomm.c
 * @brief Application layer implementation
 * @author Kevin Lee
 * @version
 * @date 2017-03-07
 */

#include "basecomm.h"
#include "networkdevice.h"

#define MINPACKETSIZE 4 //TODO define better

ebool convertFromPacketToData(Packet *p, char *data);
ebool convertFromDataToPacket(Packet *p, char *data, int datalen);

//TODO unknown needed params
ebool init_network(char *listenport) {
	_init_network(listenport);
	return TRUE;
}

/**
 *  Get the packet ready and send as a char * to the device to send.
 *  TODO WHAT IS THIS?
 */
int convertFromPacketToData(Packet *p, char *data) {
	printd("Convert Packet to Data.\n");
	int offset = 0;
	int n = 0;
	if (p == NULL) {
		//Malformed packet.
		printe("Null Packet.\n");
		return ERROR;
	}
	char opcode = p->opcode;
	char flags = p->flags;
	data[offset++] = opcode;
	data[offset++] = flags;

	printd("Opcode: 0x%x\n", opcode);
	printd("Flags: 0x%x\n", flags);

	switch (opcode) {
	case PING_REQUEST:
		printd("PING OPCODE.\n");
		if (!IS_ACK(flags)) {
			data[offset++] = (char) (p->DESTUID >> 8);
			data[offset++] = (char) p->DESTUID;
			printd("DESTUID: 0x%x %x\n", (char) data[offset], (char) data[offset+1]);
		} else {
			data[offset++] = (char) (p->SRCUID >> 8); //Add SRCUID to packet.
			data[offset++] = (char) p->SRCUID;
			printd("DESTUID: 0x%x %x\n", (char) data[offset], (char) data[offset+1]);
			if ((n = strlen(&data[offset]) < MAXNAME)) {
				strcpy(p->SRCNAME, &data[offset + n + 1]); //Add SRCNAME to packet. TODO Optimize
			} else {
				printe("Malformed String.\n");
			}
		}
		break;
	default:
		printe("Unimplemented OPCODE.\n");
		break;
	}
	printd("Exiting packet to data conversion.\n");
	return offset;
	//return offset-1; //TODO is the math right?
	//return FALSE;
}

/**
 * Take the packet data and send to network device.
 * Returns if successful or not.
 */
ebool sendPacket(Packet *p, Base *dest) {
	char data[MAXBUFFER];
	int datalen = 0;
	if ((datalen = convertFromPacketToData(p, data)) <= 0) {
		printe("Error converting packet.\n");
		return FALSE;
	}

	if (_send_packet(data, datalen, dest->addr, dest->UID) <= 0) {
		printe("Error sending packet.\n");
		return FALSE;
	}
	return TRUE;
}

/**
 * Checks for a packet on the network layer. This then processes the packet.
 */
ebool recvPacket(Packet *p, Base *src) {
	char buffer[BUFFERSIZE];
	int receivelen;
	if ((receivelen = _recv_packet(buffer, BUFFERSIZE)) <= 0) {
		//printe("No packet to receive.\n");
		return FALSE;
	}
	convertFromDataToPacket(p, buffer, receivelen);

	return TRUE; //TODO Fix
}

/**
 * Processes received data from network. Converts into packet form.
 * They are sorted based on their opcode.
 */
ebool convertFromDataToPacket(Packet *p, char *data, int datalen) {
	printd("Convert Data to Packet.\n");
	int offset = 0;
	int n = 0;
	if (datalen < MINPACKETSIZE) {
		//Malformed packet.
		printe("Packet too small.\n");
		return ERROR;
	}
	char opcode = data[0];
	char flags = data[1];

	printd("Opcode: 0x%x\n", opcode);
	printd("Flags: 0x%x\n", flags);

	switch (opcode) {
	case PING_REQUEST:
		printd("PING OPCODE.\n");
		if (!IS_ACK(flags)) {
			p->DESTUID = (data[offset++] << 8) + data[offset++]; //Add SRCUID to packet.
		} else {
			p->DESTUID = (data[offset++] << 8) + data[offset++]; //Add SRCUID to packet.
			if ((n = strlen(&data[offset]) < MAXNAME)) {
				strcpy(p->SRCNAME, &data[offset + n + 1]); //Add SRCNAME to packet. TODO Optimize
			} else {
				printe("Malformed String.\n");
			}
		}

		printd("DESTUID: %d\n");

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
	}
	printd("Exiting data to packet conversion.\n");
	return TRUE;
}

ebool processPacket(Packet *p) {
	return FALSE; //TODO fix
}

//TODO For later
ebool networkUp() {
	return FALSE; //TODO fix.
}
