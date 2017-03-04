/**
 *  Implementation of network device specific communication */
/*  Functions to call in upper layer:
 *  bool recvPacket(Packet *p);
 *
 */
#include "networkdevice.h"
#include "basecomm.h"

int connfd, listenfd = 0;

/**
 * Initialize the network device.
 * The port is the listening port.
 */
bool _init_network(char *port) {
	struct sockaddr_in servaddr;
	if ((*listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printe("Socket error.\n");
		return FALSE;
	}
	//TODO this is non-blocking now.
	int status = fcntl(listenfd, F_SETFL,
			fcntl(listenfd, F_GETFL, 0) | O_NONBLOCK);

	if (status == -1) {
		printe("fcntl error.\n");
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(port)); //Port

	if (bind(*listenfd, (SA *) &servaddr, sizeof(servaddr)) == -1) {
		printe("Bind error.\n");
		return FALSE;
	}

	printf("Server started @ %s\n", port);
	if (listen(*listenfd, LISTENQ) == -1) {
		printe("Listen error.\n");
		return FALSE;
	}
	return TRUE;
}

/**
 * Use this method to connect to a device.
 */
bool connectTo(char *server, char *port) {
	//if (connfd) {
	//	return FALSE; //This means already connected to a socket.
	//}
	struct sockaddr_in servaddr;
	if ((*connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printe("Socket error.\n");
		return FALSE;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(port)); //Port

	if (inet_pton(AF_INET, server, &servaddr.sin_addr) <= 0) {
		printe("inet pton error for, %s\n", server);
		return FALSE;
	}

	if (connect(connfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
		printe("Connect error.\n");
		return FALSE;
	}
	return TRUE;
}

/**
 * Accept connection on listen port.
 */
bool acceptFrom() {
	connfd = accept(listenfd, (SA *) NULL, SOCK_NONBLOCK); //TODO Nonblocking
	if (connfd <= 0) {
		return FALSE;
	}
	return TRUE;
}

/**
 *  Receiving side of basecomm.c
 *  Send the data to the address specified
 *  Return <= 0 for failure, otherwise good.
 */
bool _data_send(char *buffer, int size, char *dstaddr, char *dstport) {
	connectTo(dstaddr, dstport);
	int n = write(connfd, buffer, size); //TODO iterate in loop to write full.
	close(connfd);
	if (n < 0) {
		return ERROR;
	}
	printv("Packet Sent.\n");
	return TRUE;
}

/**
 *  Take a packet from the network layer and construct a Packet and populate
 *  send to recvPacket() in the upper layer. If the packet parses correctly
 *  the return is != 0, otherwise there was an error and we need to not ack
 *  the packet so that it is sent again (assumption made about how network works)
 *  If the data buffer is too small, the rest of the message is discarded.
 */
bool _recv_packet(char * buffer, int buffersize) {
	if (acceptFrom() == FALSE) {
		return FALSE; //No packet to see.
	}
	int receiveLength = 0;
	bzero(buffer, buffersize); //TODO do we need to clear buffer.
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
	return TRUE;
}

