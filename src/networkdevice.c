/**
 * @file networkdevice.c
 * @brief Implementation of network specific communication
 * @author
 * @version
 * @date 2017-03-07
 *
 * Functions to call in upper layer:
 * bool recvPacket(Packet *p);
 */

#include "networkdevice.h"

int connfd, listenfd = 0;
//int outboundfd, inboundfd = 0;

/**
 * Initialize the network device.
 * The port is the listening port.
 */
ebool _init_network(char *listenport) {
    struct sockaddr_in servaddr;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printe("Socket error.\n");
        return FALSE;
    }
    //TODO this is non-blocking now.
    int status = fcntl(listenfd, F_SETFL,
            fcntl(listenfd, F_GETFL, 0) | O_NONBLOCK);

    if (status == -1) {
        printe("fcntl error.\n");
        return FALSE;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(listenport)); //Port

    if (bind(listenfd, (SA *) &servaddr, sizeof(servaddr)) == -1) {
        printe("Bind error.\n");
        return FALSE;
    }

    printv("Listen port started @ %s\n", listenport);
    if (listen(listenfd, LISTENQ) == -1) {
        printe("Listen error.\n");
        return FALSE;
    }
    return TRUE;
}

/**
 * Use this method to connect to a device.
 */
ebool connectTo(char *server, char *port) {
    //if (connfd) {
    //  return FALSE; //This means already connected to a socket.
    //}
    struct sockaddr_in servaddr;
    if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printe("Socket error.\n");
        return FALSE;
    }
    fcntl(connfd, F_SETFL, O_NONBLOCK);  // set to non-blocking

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(port)); //Port

    if (inet_pton(AF_INET, server, &servaddr.sin_addr) <= 0) {
        printe("inet pton error for, %s\n", server);
        return FALSE;
    }

    if (connect(connfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
        printe("Connect error.\n"); //TODO may error because non-block or timeout
        return FALSE;
    }
    return TRUE;
}

/**
 * Accept connection on listen port.
 */
ebool acceptFrom() {
    connfd = accept(listenfd, (SA *) NULL, NULL); //TODO Nonblocking
    if (connfd <= 0) {
        return FALSE;
    }
    return TRUE;
}

/**
 *  Send the data to the address specified
 *  Return <= 0 for failure, otherwise good.
 */
ebool _send_packet(char *buffer, int size, char *dstaddr, char *dstport) {
	printd("Starting _send_packet.\n");
    if (connectTo(dstaddr, dstport) == FALSE) {
        printe("Connect error. TODO WHY\n"); //TODO may error because non-block or timeout
    }
    int n = write(connfd, buffer, size); //TODO iterate in loop to write full.
	printd("Write data. n: %d\n", n);
    close(connfd);
    if (n < 0) {
    	printe("Connection write failed. n: %d\n", n);
        return ERROR;
    }
    printv("Packet Sent.\n");
    return TRUE;
}

/**
 *  Take a packet from the network layer and construct a Packet and populate
 *  send to recvPacket() in the upper layer. If the packet parses correctly
 *  the return is number of bytes. TODO
 *  If the data buffer is too small, the rest of the message is discarded. TODO
 */
int _recv_packet(char *buffer, int buffersize) {
	//Do stuff network specific
    if (acceptFrom() == FALSE) {
        return FALSE; //No packet to see. No connection accepted.
    }
    int receiveLength = 0;
    //bzero(buffer, buffersize); //TODO do we need to clear buffer.
    int offset = 0;

    //If receiveLength == 0, client has reached EOF.
    //If receiveLength <= -1, error occurred.
    while ((receiveLength = read(connfd, buffer + offset, buffersize - offset))
            > 0) {
        offset += receiveLength;
    }
    if (receiveLength == ERROR) {
        printe("Read Packet Error.\n");
        return ERROR;
    }

    printv("Device Disconnected.\n");
    close(connfd);
    return offset;
}

