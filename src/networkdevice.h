/**
 * @file networkdevice.h
 * @brief Base to base communication
 * @author
 * @version
 * @date 2017-03-07
 *
 *  Functions here will be called by basecomm.h functions and will be the actual
 *  device implementation of network connectivity. By implementing this file for
 *  a new device, the base comm. can be changed to a new device
 */

#ifndef _HA_NETWORKDEVICE_
#define _HA_NETWORKDEVICE_

#include "halib.h"
#include "network.h"
#include "base.h"

/* Must Implement for App */
bool _init_network(char *listenport);
bool _send_packet(char *buffer, int size, char *dstaddr, uid dstport);
int _recv_packet(char *buffer, int buffersize);

/* For Later */
void _get_network_errors();

/* Device Specific functions */
//Socket stuff
#include "sys/socket.h"
#include "netinet/in.h"
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>

#define SA  struct sockaddr
#define LISTENQ 1024    /* 2nd argument to listen() */

#endif // _HA_NETWORKDEVICE_
