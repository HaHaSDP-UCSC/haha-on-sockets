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

ebool convertFromPacketToData(Packet *p, unsigned char *data);
ebool convertFromDataToPacket(Packet *p, unsigned char *data, int datalen);

/**
 * Initializes the network.
 */
ebool init_network(char *listenport) {
	if (_init_network(listenport) <= 0) {
		return FALSE;
	}
	return TRUE;
}

/**
 * Take the packet data and send to network device.
 * Returns if successful or not.
 */
ebool sendPacket(Packet *p, Base *dest) {
	unsigned char data[MAXBUFFER];
	int datalen = 0;
	if ((datalen = convertFromPacketToData(p, data)) <= 0) {
		printe("Error converting packet.\n");
		return FALSE;
	}

	if (_send_packet((char *) data, datalen, dest->addr, dest->UID) <= 0) {
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
	convertFromDataToPacket(p, (unsigned char *) buffer, receivelen);

	return TRUE; //TODO Fix
}

/**
 * Processes Packet data to send on network. Converts into byte data.
 * They are processed based on their opcode.
 */
int convertFromPacketToData(Packet *p, unsigned char *data) {
	printd("Convert Packet to Data.\n");
	int n = 0;
	if (p == NULL) {
		//Malformed packet.
		printe("Null Packet.\n");
		return ERROR;
	}
	unsigned char opcode = p->opcode;
	unsigned char flags = p->flags;

	int offset = 0;
	data[offset++] = opcode;
	data[offset++] = flags;

	printd("Opcode: 0x%x\n", data[offset - 2]);
	printd("Flags: 0x%x\n", data[offset - 1]);

	switch (opcode) {
	case PING_REQUEST:
		printd("PING OPCODE.\n");
		if (!IS_ACK(flags)) {
			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
		} else {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			if ((n = strlen(p->SRCFIRSTNAME)) < MAXFIRSTNAME - 1) {
				printd("SRCFNAME: %s\nstrlen: %d\n", p->SRCFIRSTNAME, n);
				strcpy((char *) &data[offset], p->SRCFIRSTNAME); //Add SRCNAME to packet. TODO Optimize
				offset += n + 1; //String length + null terminator.
			} else {
				printe("Malformed First Name.\n");
			}
			if ((n = strlen(p->SRCLASTNAME)) < MAXLASTNAME - 1) {
				printd("SRCLNAME: %s\nstrlen: %d\n", p->SRCLASTNAME, n);
				strcpy((char *) &data[offset], p->SRCLASTNAME); //Add SRCNAME to packet. TODO Optimize
				offset += n + 1; //String length + null terminator.
			} else {
				printe("Malformed Last Name.\n");
			}
		}
		break;
	case HELP_REQUEST:
		printd("HELP REQ OPCODE.\n");
		//TODO FIX
		if (!IS_ACK(flags)) {
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

		//TODO:
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

		//TODO:BROADCAST
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

		//TODO:BROADCAST
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
		printe("Unimplemented OPCODE.\n");
		break;
	}
	printd("Exiting packet to data conversion.\n");
	printd("Offset: %d.\n", offset);
	return offset;
}

/**
 * Processes received data from network. Converts into packet form.
 * They are processed based on their opcode.
 */
int convertFromDataToPacket(Packet *p, unsigned char *data, int datalen) {
	printd("Convert Data to Packet.\n");
	int n = 0;
	printf("Datalen: %d\n", datalen);
	if (datalen < MINPACKETSIZE) {
		//Malformed packet.
		printe("Packet too small.\n");
		return ERROR;
	}

	int offset = 0;
	unsigned char opcode = data[offset++];
	unsigned char flags = data[offset++];

	p->opcode = opcode;
	p->flags = flags;

	printd("Opcode: 0x%x\n", opcode);
	printd("Flags: 0x%x\n", flags);

	//TODO Do a check to see if this packet needs to be processed.
	//If the packet is not expected, drop the packet.
	/**
	 * if (!isExpecting(opcode, PING_REQUEST_FLAG)) {
	 * 	//drop packet
	 * }
	 */

	switch (opcode) {
	case PING_REQUEST:
		printd("PING OPCODE.\n");
		if (!IS_ACK(flags)) {
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; //Add DESTUID to packet.
			printd("DESTUID: %u\n", p->DESTUID);
		} else {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			if ((n = strlen((char *) &data[offset])) < MAXFIRSTNAME - 1) {
				strcpy(p->SRCFIRSTNAME, (char *) &data[offset]); //Add SRCNAME to packet. TODO Optimize
				offset += n + 1; //String length + null terminator.
				printd("SRCFNAME: %s\nstrlen: %d\n", p->SRCFIRSTNAME, n);
			} else {
				printe("Malformed First Name String.\n");
			}
			if ((n = strlen((char *) &data[offset])) < MAXLASTNAME - 1) {
				strcpy(p->SRCLASTNAME, (char *) &data[offset]); //Add SRCNAME to packet. TODO Optimize
				offset += n + 1; //String length + null terminator.
				printd("SRCLNAME: %s\nstrlen: %d\n", p->SRCLASTNAME, n);
			} else {
				printe("Malformed Last Name String.\n");
			}
		}
		break;

	case HELP_REQUEST:
		printd("HELP REQ OPCODE.\n");
		//TODO FIX
		if (!IS_ACK(flags)) {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add SRCHOMEADDR to packet.
			//Add SRCPHONE to packet.
		} else {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);

		}
		break;

	case HELP_RESPONSE:
		printd("HELP RESPONSE OPCODE.\n");
		if (!IS_ACK(flags)) {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
		} else {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
		}
		break;

		//TODO:
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
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add DESTUID to packet.
			//Add SRCNAME to packet.
		} else {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add DESTUID to packet.
			//Add SRCHOMEADDR to packet.
			//Add SRCPHONE to packet.
		}
		break;

		//TODO:BROADCAST
	case FIND_HOPS_REQUEST:
		printd("FIND HOPS REQUEST OPCODE.\n");
		//Add ORIGINUID to packet.
		//Add TTL to packet.
		break;

	case FIND_HOPS_RESPONSE:
		printd("FIND HOPS RESPONSE OPCODE.\n");
		if (!IS_ACK(flags)) {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add ORIGINUID to packet.
			//Add TTL to packet.
		} else {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add DESTUID to packet.
		}
		break;

		//TODO:BROADCAST
	case FIND_NEIGHBORS_REQUEST:
		printd("FIND NEIGHBORS REQUEST OPCODE.\n");
		//Add ORIGINUID to packet.
		//Add TTL to packet.
		break;

	case FIND_NEIGHBORS_RESPONSE:
		printd("FIND NEIGHBORS RESPONSE OPCODE.\n");
		if (!IS_ACK(flags)) {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add ORIGINUID to packet.
			//Add TTL to packet.
			//Add SRCNAME to packet.
		} else {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add DESTUID to packet.
		}
		break;

	case FRIEND_REQUEST:
		printd("FRIEND REQUEST OPCODE.\n");
		if (!IS_ACK(flags)) {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add DESTUID to packet.
			//Add SRCNAME to packet.
		} else {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add DESTUID to packet.
			//Add SRCNAME to packet.
		}
		break;

	case FRIEND_RESPONSE:
		printd("FRIEND RESPONSE OPCODE.\n");
		if (!IS_ACK(flags)) {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add DESTUID to packet.
		} else {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add DESTUID to packet.
		}
		break;

	case UNFRIEND_REQUEST:
		printd("UNFRIEND REQUEST OPCODE.\n");
		if (!IS_ACK(flags)) {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add DESTUID to packet.
		} else {
			//TODO FIX
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			//Add DESTUID to packet.
		}
		break;

	default:
		printe("Unhandled OPCODE.\n");
		//TODO Undefined.
		return ERROR;
	}
	printd("Exiting data to packet conversion.\n");
	printd("Offset: %d.\n", offset);
	return offset;
}

ebool processPacket(Packet *p) {
	return FALSE; //TODO fix
}

//TODO For later
ebool networkUp() {
	return FALSE; //TODO fix.
}
