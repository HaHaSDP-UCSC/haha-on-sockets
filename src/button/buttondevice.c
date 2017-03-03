/* Implementation of network device specific communication */
/* Functions to call in upper layer:
*  bool recvMessage(char* msg);
*
*/
#include "../devtools.h"
#include "buttondevice.h"
#include "button.h"

//Like the others parse and send up to the next layer
//This is likely incorrect, the bluetooth will have different specifics.
//but it will only be necessary to parse the message and send it up to the next
//layer.
void _recv_beacon(char* msg){

}

bool _send_beacon(char* msg){

}
