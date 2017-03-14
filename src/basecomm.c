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
 * Creates a packet from a standardized structure to be sent.
 */
bool formPacketToData(Packet *p, unsigned char *data, int *oldoffset, bool srcuid,
bool destuid, bool originuid, bool srcname, bool srchomeaddr, bool srcphone,
bool ttl) {
	int n = 0;
	int offset = *oldoffset;

	if (srcuid) {
		printd("Expected SRCUID: 0x%x\n", p->SRCUID);
		data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
		data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
		printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
	}
	if (destuid) {
		printd("Expected DESTUID: 0x%x\n", p->DESTUID);
		printd("Offset: %d\n", offset);
		data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
		printd("Offset: %d\n", offset);
		data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
		printd("Offset: %d\n", offset);
		printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
	}
	if (originuid) {
		printd("Expected ORIGINUID: 0x%x\n", p->ORIGINUID);
		data[offset++] = p->ORIGINUID >> 8; //Add UPPER ORIGINUID to packet.
		data[offset++] = p->ORIGINUID; //Add LOWER ORIGINUID to packet.
		printd("ORIGINUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
	}
	if (srcname) {
		if ((n = strlen(p->SRCFIRSTNAME)) < MAXFIRSTNAME - 1) {
			printd("SRCFNAME: %s\nstrlen: %d\n", p->SRCFIRSTNAME, n);
			strcpy((char *) &data[offset], p->SRCFIRSTNAME); //Add SRCNAME to packet. TODO Optimize
			offset += n + 1; //String length + null terminator.
		} else {
			printe("Malformed First Name.\n");
			return false;
		}
		if ((n = strlen(p->SRCLASTNAME)) < MAXLASTNAME - 1) {
			printd("SRCLNAME: %s\nstrlen: %d\n", p->SRCLASTNAME, n);
			strcpy((char *) &data[offset], p->SRCLASTNAME); //Add SRCNAME to packet. TODO Optimize
			offset += n + 1; //String length + null terminator.
		} else {
			printe("Malformed Last Name.\n");
			return false;
		}
	}
	if (srchomeaddr) {
		if ((n = strlen(p->SRCHOMEADDR)) < MAXHOMEADDR - 1) {
			printd("SRCHOMEADDR: %s\nstrlen: %d\n", p->SRCHOMEADDR, n);
			strcpy((char *) &data[offset], p->SRCHOMEADDR); //Add SRCHOMEADDR to packet. TODO Optimize
			offset += n + 1; //String length + null terminator.
		} else {
			printe("Malformed Home Address.\n");
			return false;
		}
	}
	if (srcphone) {
		if ((n = strlen(p->SRCPHONE)) < MAXPHONE - 1) {
			printd("SRCPHONE: %s\nstrlen: %d\n", p->SRCPHONE, n);
			strcpy((char *) &data[offset], p->SRCPHONE); //Add SRCNAME to packet. TODO Optimize
			offset += n + 1; //String length + null terminator.
		} else {
			printe("Malformed Phone Number.\n");
			return false;
		}
	}
	if (ttl) {
		data[offset++] = p->ttl;
	}
	*oldoffset = offset; //Make the old offset new.
	return true;
}

/**
 * Creates a packet from a standardized structure to be received.
 */
bool formDataToPacket(Packet *p, unsigned char *data, int *oldoffset, bool srcuid,
bool destuid, bool originuid, bool srcname, bool srchomeaddr, bool srcphone,
bool ttl) {
	int n = 0;
	int offset = *oldoffset;

	if (srcuid) {
		p->SRCUID = data[offset++] << 8;
		p->SRCUID += data[offset++]; //Add SRCUID to packet.
		printd("SRCUID: %u\n", p->SRCUID);
	}
	if (destuid) {
		p->DESTUID = data[offset++] << 8;
		p->DESTUID += data[offset++]; //Add DESTUID to packet.
		printd("DESTUID: %u\n", p->DESTUID);
	}
	if (originuid) {
		p->ORIGINUID = data[offset++] << 8;
		p->ORIGINUID += data[offset++]; //Add DESTUID to packet.
		printd("ORIGINUID: %u\n", p->ORIGINUID);
	}
	if (srcname) {
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
	if (srchomeaddr) {
		if ((n = strlen((char *) &data[offset])) < MAXHOMEADDR - 1) {
			strcpy(p->SRCHOMEADDR, (char *) &data[offset]); //Add SRCHOMEADDR to packet
			offset += n + 1; //String length + null terminator.
			printd("SRCFNAME: %s\nstrlen: %d\n", p->SRCHOMEADDR, n);
		} else {
			printe("Malformed Home Address String.\n");
		}

	}
	if (srcphone) {
		if ((n = strlen((char *) &data[offset])) < MAXPHONE - 1) {
			strcpy(p->SRCPHONE, (char *) &data[offset]); //Add SRCPHONE to packet
			offset += n + 1; //String length + null terminator.
			printd("SRCLNAME: %s\nstrlen: %d\n", p->SRCPHONE, n);
		} else {
			printe("Malformed Phone Number String.\n");
		}
	}
	if (ttl) {
		p->ttl = data[offset++];
	}
	*oldoffset = offset; //Make the old offset new.
	return true;
}

/**
 * Processes Packet data to send on network. Converts into byte data.
 * They are processed based on their opcode.
 */
int convertFromPacketToData(Packet *p, unsigned char *data) {
	printd("Convert Packet to Data.\n");
	if (p == NULL) {
		//Malformed packet.
		printe("Null Packet.\n");
		return ERROR;
	}
	int n = 0; //TODO delete this, deprecated
	unsigned char opcode = p->opcode;
	unsigned char flags = p->flags;

	int offset = 0;
	data[offset++] = opcode;
	data[offset++] = flags;

	printd("Opcode: 0x%x\n", data[offset - 2]);
	printd("Flags: 0x%x\n", data[offset - 1]);

	int success;
	switch (opcode) {
	case PING_REQUEST:
		printd("PING OPCODE.\n");
		if (!IS_ACK(flags)) {
			//Add DESTUID
			//srcuid, destuid, srcname, srchomeaddr, srcphone, ttl
			success = formPacketToData(p, data, &offset, false, true,
			false,
			false, false, false, false);
		} else {
			//Add SRCUID
			//Add SRCNAME
			//srcuid, destuid, srcname, srchomeaddr, srcphone, ttl
			success = formPacketToData(p, data, &offset, true, false,
			true,
			false, false, false, false);
		}
		break;

	case HELP_REQUEST:
		printd("HELP REQ OPCODE.\n");
		if (!IS_ACK(flags)) {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
			if ((n = strlen(p->SRCHOMEADDR)) < MAXHOMEADDR - 1) {
				printd("SRCHOMEADDR: %s\nstrlen: %d\n", p->SRCHOMEADDR, n);
				strcpy((char *) &data[offset], p->SRCHOMEADDR); //Add SRCHOMEADDR to packet. TODO Optimize
				offset += n + 1; //String length + null terminator.
			} else {
				printe("Malformed Home Address.\n");
			}
			if ((n = strlen(p->SRCPHONE)) < MAXPHONE - 1) {
				printd("SRCPHONE: %s\nstrlen: %d\n", p->SRCPHONE, n);
				strcpy((char *) &data[offset], p->SRCPHONE); //Add SRCNAME to packet. TODO Optimize
				offset += n + 1; //String length + null terminator.
			} else {
				printe("Malformed Phone Number.\n");
			}
		} else {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
		}
		break;

	case HELP_RESPONSE:
		printd("HELP RESPONSE OPCODE.\n");
		if (!IS_ACK(flags)) {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
		} else {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
		}
		break;

		//TODO:BROADCAST
	case HELP_FROM_ANYONE_REQUEST:
		printd("HELP FROM ANYONE REQUEST OPCODE.\n");
		//Add SRCUID to packet.
		//Add TTL to packet.
		//Add SRCNAME to packet.
		break;

	case HELP_FROM_ANYONE_RESPONSE:
		printd("HELP FROM ANYONE RESPONSE OPCODE.\n");
		if (!IS_ACK(flags)) {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
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
		} else {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
			if ((n = strlen(p->SRCHOMEADDR)) < MAXHOMEADDR - 1) {
				printd("SRCHOMEADDR: %s\nstrlen: %d\n", p->SRCHOMEADDR, n);
				strcpy((char *) &data[offset], p->SRCHOMEADDR); //Add SRCHOMEADDR to packet. TODO Optimize
				offset += n + 1; //String length + null terminator.
			} else {
				printe("Malformed Home Address.\n");
			}
			if ((n = strlen(p->SRCPHONE)) < MAXPHONE - 1) {
				printd("SRCPHONE: %s\nstrlen: %d\n", p->SRCPHONE, n);
				strcpy((char *) &data[offset], p->SRCPHONE); //Add SRCNAME to packet. TODO Optimize
				offset += n + 1; //String length + null terminator.
			} else {
				printe("Malformed Phone Number.\n");
			}
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
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
			if ((n = strlen(p->ORIGINUID)) < MAXUID - 1) {
				printd("ORIGINUID: %s\nstrlen: %d\n", p->ORIGINUID, n);
				strcpy((char *) &data[offset], p->ORIGINUID); //Add ORIGINUID to packet. TODO Optimize
				offset += n + 1; //String length + null terminator.
			} else {
				printe("Malformed Origin UID.\n");
			}
			//TODO Add TTL to packet.
		} else {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
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
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
			if ((n = strlen(p->ORIGINUID)) < MAXUID - 1) {
				printd("ORIGINUID: %s\nstrlen: %d\n", p->ORIGINUID, n);
				strcpy((char *) &data[offset], p->ORIGINUID); //Add ORIGINUID to packet. TODO Optimize
				offset += n + 1; //String length + null terminator.
			} else {
				printe("Malformed Origin UID.\n");
			}
			//TODO Add TTL to packet.
			//
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

		} else {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
		}
		break;

	case FRIEND_REQUEST:
		printd("FRIEND REQUEST OPCODE.\n");
		if (!IS_ACK(flags)) {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

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
		} else {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

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

	case FRIEND_RESPONSE:
		printd("FRIEND RESPONSE OPCODE.\n");
		if (!IS_ACK(flags)) {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
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
		} else {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
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

	case UNFRIEND_REQUEST:
		printd("UNFRIEND REQUEST OPCODE.\n");
		if (!IS_ACK(flags)) {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
		} else {
			printd("Expected SRCUID: 0x%x\n", p->SRCUID);
			data[offset++] = p->SRCUID >> 8; //Add UPPER SRCUID to packet.
			data[offset++] = p->SRCUID; //Add LOWER SRCUID to packet.
			printd("SRCUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);

			printd("Expected DESTUID: 0x%x\n", p->DESTUID);
			data[offset++] = p->DESTUID >> 8; //Add UPPER DESTUID to packet.
			data[offset++] = p->DESTUID; //Add LOWER DESTUID to packet.
			printd("DESTUID: 0x%x 0x%x\n", data[offset - 2], data[offset - 1]);
		}
		break;

	default:
		printe("Unimplemented OPCODE.\n");
		break;
	}

	if (!success) {
		printe("convertFromPacketToData Failed.\n");
		//TODO Do something more important.
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
	 *  //drop packet
	 * }
	 */
	int success = 0;

	switch (opcode) {
	case PING_REQUEST:
		printd("PING OPCODE.\n");
		if (!IS_ACK(flags)) {
			//Add DESTUID
			//srcuid, destuid, originuid, srcname, srchomeaddr, srcphone, ttl
			success = formDataToPacket(p, data, &offset, false, true,
			false,
			false, false, false, false);
		} else {
			//Add SRCUID
			//ADD SRCNAME
			//srcuid, destuid, originuid, srcname, srchomeaddr, srcphone, ttl
			success = formDataToPacket(p, data, &offset, true, false,
			true,
			false, false, false, false);
		}
		break;

	case HELP_REQUEST:
		printd("HELP REQ OPCODE.\n");
		if (!IS_ACK(flags)) {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			if ((n = strlen((char *) &data[offset])) < MAXHOMEADDR - 1) {
				strcpy(p->SRCHOMEADDR, (char *) &data[offset]); //Add SRCHOMEADDR to packet
				offset += n + 1; //String length + null terminator.
				printd("SRCFNAME: %s\nstrlen: %d\n", p->SRCHOMEADDR, n);
			} else {
				printe("Malformed Home Address String.\n");
			}
			if ((n = strlen((char *) &data[offset])) < MAXPHONE - 1) {
				strcpy(p->SRCPHONE, (char *) &data[offset]); //Add SRCPHONE to packet
				offset += n + 1; //String length + null terminator.
				printd("SRCLNAME: %s\nstrlen: %d\n", p->SRCPHONE, n);
			} else {
				printe("Malformed Phone Number String.\n");
			}
		} else {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);

		}
		break;

	case HELP_RESPONSE:
		printd("HELP RESPONSE OPCODE.\n");
		if (!IS_ACK(flags)) {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
		} else {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
		}
		break;

		//TODO:BROADCAST
	case HELP_FROM_ANYONE_REQUEST:
		printd("HELP FROM ANYONE REQUEST OPCODE.\n");
		//Add SRCUID to packet.
		//Add TTL to packet.
		//Add SRCNAME to packet.
		break;

	case HELP_FROM_ANYONE_RESPONSE:
		printd("HELP FROM ANYONE RESPONSE OPCODE.\n");
		if (!IS_ACK(flags)) {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; ///Add DESTUID to packet.
			printd("DESTUID: %u\n", p->DESTUID);
			if ((n = strlen((char *) &data[offset])) < MAXFIRSTNAME - 1) {
				strcpy(p->SRCFIRSTNAME, (char *) &data[offset]); //Add SRCNAME to packet.
				offset += n + 1; //String length + null terminator.
				printd("SRCFNAME: %s\nstrlen: %d\n", p->SRCFIRSTNAME, n);
			} else {
				printe("Malformed First Name String.\n");
			}
			if ((n = strlen((char *) &data[offset])) < MAXLASTNAME - 1) {
				strcpy(p->SRCLASTNAME, (char *) &data[offset]); //Add SRCNAME to packet.
				offset += n + 1; //String length + null terminator.
				printd("SRCLNAME: %s\nstrlen: %d\n", p->SRCLASTNAME, n);
			} else {
				printe("Malformed Last Name String.\n");
			}
		} else {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; ///Add DESTUID to packet.
			if ((n = strlen((char *) &data[offset])) < MAXHOMEADDR - 1) {
				strcpy(p->SRCHOMEADDR, (char *) &data[offset]); //Add SRCHOMEADDR to packet
				offset += n + 1; //String length + null terminator.
				printd("SRCFNAME: %s\nstrlen: %d\n", p->SRCHOMEADDR, n);
			} else {
				printe("Malformed Home Address String.\n");
			}
			if ((n = strlen((char *) &data[offset])) < MAXPHONE - 1) {
				strcpy(p->SRCPHONE, (char *) &data[offset]); //Add SRCPHONE to packet
				offset += n + 1; //String length + null terminator.
				printd("SRCLNAME: %s\nstrlen: %d\n", p->SRCPHONE, n);
			} else {
				printe("Malformed Phone Number String.\n");
			}
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
			if ((n = strlen((char *) &data[offset])) < MAXUID - 1) {
				strcpy(p->ORIGINUID, (char *) &data[offset]); //Add ORIGINUID to packet
				offset += n + 1; //String length + null terminator.
				printd("SRCLNAME: %s\nstrlen: %d\n", p->ORIGINUID, n);
			} else {
				printe("Malformed Origin UID String.\n");
				//Add TTL to packet.
			}
		} else {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; //Add DESTUID to packet.
			printd("DESTUID: %u\n", p->DESTUID);
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
			if ((n = strlen((char *) &data[offset])) < MAXUID - 1) {
				strcpy(p->ORIGINUID, (char *) &data[offset]); //Add ORIGINUID to packet
				offset += n + 1; //String length + null terminator.
				printd("SRCLNAME: %s\nstrlen: %d\n", p->ORIGINUID, n);
			} else {
				printe("Malformed Origin UID String.\n");
			}
			//TODO Add TTL to packet.
			if ((n = strlen((char *) &data[offset])) < MAXFIRSTNAME - 1) {
				strcpy(p->SRCFIRSTNAME, (char *) &data[offset]); //Add SRCNAME to packet.
				offset += n + 1; //String length + null terminator.
				printd("SRCFNAME: %s\nstrlen: %d\n", p->SRCFIRSTNAME, n);
			} else {
				printe("Malformed First Name String.\n");
			}
			if ((n = strlen((char *) &data[offset])) < MAXLASTNAME - 1) {
				strcpy(p->SRCLASTNAME, (char *) &data[offset]); //Add SRCNAME to packet.
				offset += n + 1; //String length + null terminator.
				printd("SRCLNAME: %s\nstrlen: %d\n", p->SRCLASTNAME, n);
			} else {
				printe("Malformed Last Name String.\n");

			}
		} else {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; //Add DESTUID to packet.
			printd("DESTUID: %u\n", p->DESTUID);
		}
		break;

	case FRIEND_REQUEST:
		printd("FRIEND REQUEST OPCODE.\n");
		if (!IS_ACK(flags)) {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; //Add DESTUID to packet.
			printd("DESTUID: %u\n", p->DESTUID);
			if ((n = strlen((char *) &data[offset])) < MAXFIRSTNAME - 1) {
				strcpy(p->SRCFIRSTNAME, (char *) &data[offset]); //Add SRCNAME to packet.
				offset += n + 1; //String length + null terminator.
				printd("SRCFNAME: %s\nstrlen: %d\n", p->SRCFIRSTNAME, n);
			} else {
				printe("Malformed First Name String.\n");
			}
			if ((n = strlen((char *) &data[offset])) < MAXLASTNAME - 1) {
				strcpy(p->SRCLASTNAME, (char *) &data[offset]); //Add SRCNAME to packet.
				offset += n + 1; //String length + null terminator.
				printd("SRCLNAME: %s\nstrlen: %d\n", p->SRCLASTNAME, n);
			} else {
				printe("Malformed Last Name String.\n");
			}
		} else {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; //Add DESTUID to packet.
			printd("DESTUID: %u\n", p->DESTUID);
			if ((n = strlen((char *) &data[offset])) < MAXFIRSTNAME - 1) {
				strcpy(p->SRCFIRSTNAME, (char *) &data[offset]); //Add SRCNAME to packet.
				offset += n + 1; //String length + null terminator.
				printd("SRCFNAME: %s\nstrlen: %d\n", p->SRCFIRSTNAME, n);
			} else {
				printe("Malformed First Name String.\n");
			}
			if ((n = strlen((char *) &data[offset])) < MAXLASTNAME - 1) {
				strcpy(p->SRCLASTNAME, (char *) &data[offset]); //Add SRCNAME to packet.
				offset += n + 1; //String length + null terminator.
				printd("SRCLNAME: %s\nstrlen: %d\n", p->SRCLASTNAME, n);
			} else {
				printe("Malformed Last Name String.\n");

			}
		}
		break;

	case FRIEND_RESPONSE:
		printd("FRIEND RESPONSE OPCODE.\n");
		if (!IS_ACK(flags)) {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; //Add DESTUID to packet.
			printd("DESTUID: %u\n", p->DESTUID);
		} else {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; //Add DESTUID to packet.
			printd("DESTUID: %u\n", p->DESTUID);
		}
		break;

	case UNFRIEND_REQUEST:
		printd("UNFRIEND REQUEST OPCODE.\n");
		if (!IS_ACK(flags)) {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; //Add DESTUID to packet.
			printd("DESTUID: %u\n", p->DESTUID);
		} else {
			p->SRCUID = data[offset++] << 8;
			p->SRCUID += data[offset++]; //Add SRCUID to packet.
			printd("SRCUID: %u\n", p->SRCUID);
			p->DESTUID = data[offset++] << 8;
			p->DESTUID += data[offset++]; //Add DESTUID to packet.
			printd("DESTUID: %u\n", p->DESTUID);
		}
		break;

	default:
		printe("Unhandled OPCODE.\n");
		//TODO Undefined.
		return ERROR;
	}
	if (!success) {
		printe("convertFromPacketToData Failed.\n");
		//TODO Do something more important.
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
