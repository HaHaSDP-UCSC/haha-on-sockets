/**
 * @file main.c
 * @brief Main program of the base station
 * @author Brian, Kevin, August
 * @version
 * @date 2017-03-07
 */


/* Main program */
#include "halib.h"
#include "init.h"
/* Base */
#include "basecomm.h"
#include "networkdevice.h"
/* Button */
#include "buttoncomm.h"
#include "buttondevice.h"
/* Other */
#include "storage.h"
#include "storagedevice.h"

// Global variables
Menu* menu;
char* listenPort;
char* destination;

/**
 * @brief Setup
 */
void initMain() {
    menu = initMenus();
    init_network(listen);
    lcdInit();
}

/**
 * @brief Main of the program
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return Error code
 */
int main(int argc, char** argv) {
    int error = FALSE; //correct this later

    // Get command line arguments
    listenPort = argv[1];
    destination = argv[2];
    if (argc != 3) {
        printe("usage: <listenport> <destinationport>\n");
        return ERROR;
    }

    // Initialize
    initMain();

    // Register interrupts
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

    if(fork() != 0) {
        while(true) {
            char input = getchar();
            int move = -1;
            switch(input) {
                case 'w':
                    move = menuMove(menu, MENU_UP);
                    break;
                case 'a':
                    move = menuMove(menu, MENU_LEFT);
                    break;
                case 's':
                    move = menuMove(menu, MENU_DOWN);
                    break;
                case 'd':
                    move = menuMove(menu, MENU_RIGHT);
                    break;
                case 'h':
                    printv("HELP BUTTON PRESSED\n");
                    break;
                case 't':
                    menuItemPrintTree(menu->root);
                    break;
                case 'q':
                    goto done;
                    break;
                case '\n':
                    break;
            }
            if(move != -1) {
                menuSetLcd(menu);
                lcdUpdate();
            }
        }
    } else {
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
    }

done:
    lcdDestroy();
    menuDestroy(menu);

    return error;
}
