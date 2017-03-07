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

/* BASE COMMUNICATION */
typedef char* opcode;

typedef struct {
	//Packet params here
	opcode opcode;
	flags flags;
	char* src;
	char* dst;
	char* data;
} Packet;

#endif // _HA_NETDEFS_
