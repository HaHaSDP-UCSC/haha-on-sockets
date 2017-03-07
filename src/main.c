/**
 * @file main.c
 * @brief Main program of the base station
 * @author Brian, Kevin
 * @version
 * @date 2017-03-07
 */


/* Main program */
#include "devtools.h"
#include "hahaProgram.h"
/* Base */
#include "basecomm.h"
#include "networkdevice.h"
/* Button */
#include "buttoncomm.h"
#include "buttondevice.h"
/* Other */
#include "storage.h"
#include "storagedevice.h"

/* The specifics of this part of the program will be different on the uC
 *  We will probably register some interrupts and interrupt timers. For the
 *  socket version we will have to poll.
 */

void init() {
    //Setup everything
    //Load stored information
    //
}

int main(int argc, char** argv) {
    int error = FALSE; //correct this later

    char *listen = argv[1];
    char *destination = argv[2];

    if (argc != 3) {
        printe("usage: <listenport> <destinationport>\n");
        return ERROR;
    }
    //Initialize
    init_network(listen);
    //Register interrupts

    char buffer[BUFFERSIZE];

    Packet prec;
    prec.data = buffer;

    Packet psend;
    psend.src = listen;
    psend.dst = destination;
    char linebuf[BUFFERSIZE];
    int count = 0;
    sprintf(linebuf, "%s %d\n", listen, count);
    psend.data = linebuf;
    sendPacket(&psend, destination);

    for (;;) {
        //Call recvPacket to poll the receive buffer.
        if (recvPacket(&prec) == TRUE) {
            printf("%s", prec.data);
            sleep(2);
            sprintf(linebuf, "%s %d\n", listen, count);
            psend.data = linebuf;
            sendPacket(&psend, destination);
            sleep(2);
            count++;
        }
    }

    return error;
}
