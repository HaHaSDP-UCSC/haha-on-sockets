/**
 * @file server.c
 * @brief Don't use this
 * @author Kevin
 * @version
 * @date 2017-03-03
 */

#include "sys/socket.h"
#include "netinet/in.h"
#include "halib.h"
#include <unistd.h>

#define SA  struct sockaddr
#define CMD 4 //3 ASCII Char + null
#define PORT 6 //16 bit ASCII number and null.
#define MAXLEN 256
#define LISTENQ 1024    /* 2nd argument to listen() */

int listenfd, connfd, destfd;
pid_t pid;
char srcport[PORT], dstport[PORT], command[CMD];
char message[MAXLEN];
int status = 0;

/**
 * TCP Server.
 * The initServer function will initialize the server, and returns true
 * if it successfully launches. It will return false otherwise.
 */
bool initServer(int *listenfd, char *port) {
    struct sockaddr_in servaddr;
    if ((*listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printe("Socket error.\n");
        return FALSE;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(port)); //Port

    if (bind(*listenfd, (SA *) &servaddr, sizeof(servaddr)) == -1) {
        printe("Bind error.\n");
        return FALSE;
    }

    if (listen(*listenfd, LISTENQ) == -1) {
        printe("Listen error.\n");
        return FALSE;
    }
    printf("Server started @ %s\n", port);
    return TRUE;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printe("%s\n", "usage: <port-number>");
        exit(0);
    }

    if (!initServer(&listenfd, argv[1])) {
        exit(0);
    }

    for (;;) {
        connfd = accept(listenfd, (SA *) NULL, NULL);
        if (connfd < 0) {
            printe("Client Connection Attempt Failed.\n");
        } else {
            //Accepted Connection to Server.
            printv("Client Connected to server.\n");
            //Keep socket open until client disappears.
            int socketNotClosed = 1;
            int receiveLength = 0;
            int offset = 0;
            //bzero(receivebuffer, MAXLEN); //Zero array.
            bzero(command, CMD); //Zero array.
            while (socketNotClosed) {
                //Read command from client.
                receiveLength = read(connfd, command + offset, CMD - offset);
                if (receiveLength + offset >= CMD) {
                    printd("Received a command: %s\n", command);

                    offset = 0;
                    if (command[3] != '\0') {
                        status = -1; //Bad command.
                    }

                    if (strcmp(command, "REQ") == 0)
                        status = 1;
                    if (strcmp(command, "SIZ") == 0)
                        status = 2;
                    if (strcmp(command, "ACK") == 0)
                        status = 3;
                    if (strcmp(command, "ERR") == 0)
                        status = -1;

                    //Based on the command received, enter a specific state.
                    switch (status) {
                        //REQuest state.
                        case 1:
                            printd("Entering REQ state.\n")
                                ;
                            break;

                            //SIZe state.
                        case 2:
                            printd("Entering SIZ state.\n")
                                ;
                            break;
                            //ACK state. Undefined
                        case 3:
                            printd("Entering ACK state.\n")
                                ;
                            break;
                            //Error state. Undefined
                        default:
                            printe("Bad command or other.\n")
                                ;
                            close(connfd); //TODO Better way to indicate bad command.
                            break;

                    }
                    bzero(message, MAXLEN); //Zero array.
                    bzero(command, CMD); //Zero array.
                    offset = 0;
                    status = 0;
                } else {
                    //Data too small for command. Buffer more.
                    offset += receiveLength;
                }

                //If receiveLength == 0, client has reached EOF.
                //If receiveLength <= -1, error occurred.
                if (receiveLength <= 0) {
                    printv("Client Disconnected.\n");
                    socketNotClosed = 0;
                }
            }
            close(connfd);
        }
    }
    exit(0);
}
/**
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
