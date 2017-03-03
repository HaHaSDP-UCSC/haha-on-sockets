/* Definitions of network types */
#ifndef _HA_NETDEFS
#define _HA_NETDEFS

#include "devtools.h"
#include "flags.h"

/* BASE COMMUNICATION */
typedef opcode char*;
typdef struct{
   //Packet params here
   opcode opcode;
   flags flags;
   char* dest;
   char* data;
}Packet;

#endif
