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
Menu *menu;
char *listenPort;
char *destinationPort;

/**
 * @brief Setup
 */
void initMain() {
	menu = initMenus();
	init_network(listenPort);
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
	destinationPort = argv[2];
	if (argc != 3) {
		printe("usage: <listenport> <destinationport>\n");
		return ERROR;
	}
	
	// Initialize
	initMain();

	// Debug
	menuItemPrintTree(menu->root);

	// Register interrupts
	char buffer[BUFFERSIZE];

	Packet psend;
	psend.opcode = PING_REQUEST;
	psend.flags = NULL;
	SET_ACK(psend.flags);
	psend.SRCUID = (uint16_t) atoi(listenPort);
	psend.DESTUID = (uint16_t) atoi(destinationPort);
	psend.ORIGINUID = NULL;
	strcpy(psend.SRCNAME, "Hello World.");

	printf("psend.SRCUID: %d\n", psend.SRCUID);
	printf("psend.DESTUID: %d\n", psend.DESTUID);
	printf("psend.ORIGINUID: %d\n", psend.ORIGINUID);

	
	Packet phelp;
	phelp.opcode = PING_REQUEST;
	phelp.flags = NULL;
	SET_ACK(phelp.flags);
	phelp.SRCUID = (uint16_t) atoi(listenPort);
	phelp.DESTUID = (uint16_t) atoi(destinationPort);
	phelp.ORIGINUID = NULL;
	strcpy(phelp.SRCNAME, "Hello World.");
	

	Base dest;
	dest.addr = "127.0.0.1"; //Network Address.
	dest.UID = destinationPort; //TODO For some reason, destinationPort FAILS.
	printf("dest.DESTUID: %s\n", dest.UID);

	Packet prec;
	//prec.data = buffer;
	/**
	 Packet psend;
	 psend.src = listenPort;
	 psend.dst = destination;
	 char linebuf[BUFFERSIZE];
	 int count = 0;
	 sprintf(linebuf, "%s %d\n", listenPort, count);
	 psend.data = linebuf;*/

	int pid = 0;
	//int pid = fork();
	if (pid != 0) {
		while (true) {
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
                    // YES GOTOs
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

		int count = 0;
		sendPacket(&psend, &dest);
		Base src;
		for (;;) {
			//Call recvPacket to poll the receive buffer.
			if (recvPacket(&prec, &src) == TRUE) {
				sleep(2);
				sendPacket(&psend, &dest);
				sleep(2);
				count++;
				printf("Count: %d\n", count);
			}
		}
	}

	done: lcdDestroy();
	menuDestroy(menu);

	return error;
}
