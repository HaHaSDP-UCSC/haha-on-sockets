/* Base to base communication
*  Functions here will be called by basecomm.h functions and will be the actual
*  device implementation of network connectivity. By implementing this file for
*  a new device, the base comm. can be changed to a new device
*/
#ifndef _HA_NETWORKDEVICE
#define _HA_NETWORKDEVICE

#include "devtools.h"
#include "network.h"
#include "base.h"

/* Must Implement for App */
void _init_network();
bool _data_send(char* data, char* addr); //actually send the stirng of data
bool _recv_packet(char* data); //from sockets

/* For Later */
void _get_network_errors();

/* Device Specific functions */
//Socket stuff

#endif
