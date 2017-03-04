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
void _init_network(char *port);
bool _send_packet(char *buffer, int size, char *dstaddr, char* dstport);
bool _recv_packet(char *buffer, int buffersize);

/* For Later */
void _get_network_errors();

/* Device Specific functions */
//Socket stuff

#include "sys/socket.h"
#include "netinet/in.h"
#include <fcntl.h>
#define	SA	struct sockaddr
#define	LISTENQ	1024	/* 2nd argument to listen() */

#endif
