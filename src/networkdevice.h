#ifndef _HA_NETWORKDEVICE
#define _HA_NETWORKDEVICE
/* Functions here will be called by basecomm.h functions and will be the actual
*  device implementation of network connectivity. By implementing this file for
*  a new device, the base comm. can be changed to a new device
*/
#include "network.h"
#include "base.h"

/* Base to Base */
void init();
bool _send_Packet(Packet *p, baseaddr *dest); //prepare for send
bool _data_send(char* data); //actually send the stirng of data
void _recv_packet(char* data);





/* For Later */
void getNetworkErrors();

#endif
