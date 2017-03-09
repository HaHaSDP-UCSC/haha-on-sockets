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
typedef char* opcode;
typedef uint16_t uid;

typedef struct {
	//Packet params here
	opcode opcode;
	flags flags;
	uid SRCUID;
	uid DESTUID;
	uid ORIGINUID;
	char SRCNAME[MAXNAME];
} Packet;

#endif // _HA_NETDEFS_
