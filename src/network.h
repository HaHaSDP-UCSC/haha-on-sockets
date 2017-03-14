/**
 * @file network.h
 * @brief Definitions of network types
 * @author
 * @version
 * @date 2017-03-07
 */

#ifndef _HA_NETDEFS
#define _HA_NETDEFS

#include "halib.h"
#include "flags.h"
#include "neighbor.h"

/* BASE COMMUNICATION */
typedef unsigned char opcode;
typedef unsigned char ttl;
typedef uint16_t uid;

typedef struct {
	//Packet params here
	//opcode opcode;
	opcode opcode;
	flags flags;
	uid SRCUID;
	uid DESTUID;
	uid ORIGINUID;
	char SRCFIRSTNAME[MAXFIRSTNAME]; //TODO optimize for space.
	char SRCLASTNAME[MAXFIRSTNAME]; //TODO optimize for space.
	char SRCPHONE[MAXPHONE]; //TODO optimize for space.
	char SRCHOMEADDR[MAXHOMEADDR]; //TODO optimize for space.
	ttl ttl;
} Packet;

#endif // _HA_NETDEFS_
