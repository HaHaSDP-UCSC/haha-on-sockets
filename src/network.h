/* Definitions of network types */
#ifndef _HA_NETDEFS
#define _HA_NETDEFS

#include "devtools.h"

/* Packet */
typdef basedest char*; //most likely any network.h can implement with char*
typedef opcode char*;
typedef flags BYTE;
typedef data char*;
typdef struct{
   //Packet params here
   opcode opcode;
   flags flags;
   basedest dest;
   data data;
}Packet;

#endif
