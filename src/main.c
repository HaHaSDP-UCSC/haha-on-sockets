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
    if (argc != 3) {
        printe(
                "usage: %s PORT FILE\n"
                "\tPORT\tListening port\n"
                "\tFILE\tStorage file\n",
                argv[0]
              );
        exit(0);
        //printex("usage: <listenport> <destinationport>\n");
    }

    // Get command line arguments
    listenPort = argv[1];
    char* inputFile = argv[2];
    destinationPort = "8000"; // DO NOT USE
    // Destination should be based on Base.friends[]

    // Initialize
    initMain();
    initBase(&self, inputFile);

    menuItemPrintTree(menu->root);

    Base dest;
    dest.addr = "127.0.0.1"; //Network Address.
    dest.UID = destinationPort; //TODO For some reason, destinationPort FAILS.

    printf("dest.DESTUID: %s\n", dest.UID);

    int pid = 0;
    pid = fork(); //Turn this off and set the PID to use only MENU or PACKETs
    if (pid != 0) {

        //Create a HELP packet to send.
        Packet phelp;
        phelp.opcode = HELP_REQUEST;
        phelp.flags = 0; //Toggle these flags to trigger different things.
        SET_ACK(phelp.flags);
        phelp.SRCUID = (uint16_t) atoi(listenPort);
        phelp.DESTUID = (uint16_t) atoi(destinationPort);
        phelp.ORIGINUID = 0;
        strcpy(phelp.SRCFIRSTNAME, "Foo");
        strcpy(phelp.SRCLASTNAME, "Bar");
        strcpy(phelp.SRCPHONE, "123-456-7890"); //TODO Should actually be unformatted.
        strcpy(phelp.SRCHOMEADDR, "4657 Where the Sidewalk Ends St. Apartment 23\n"
                "Santa Cruz, CA 12345-9876");
        phelp.ttl = 0;

        printf("\n");
        printf("phelp.SRCUID:       %d\n", phelp.SRCUID);
        printf("phelp.DESTUID:      %d\n", phelp.DESTUID);
        printf("phelp.ORIGINUID:    %d\n", phelp.ORIGINUID);
        printf("phelp.SRCFIRSTNAME: %s\n", phelp.SRCFIRSTNAME);
        printf("phelp.SRCLASTNAME:  %s\n", phelp.SRCLASTNAME);
        printf("phelp.SRCPHONE:     %s\n", phelp.SRCPHONE);
        printf("phelp.SRCHOMEADDR:\n%s\n", phelp.SRCHOMEADDR);
        printf("phelp.ttl: %d\n", phelp.ttl);

        //Menu
        printd("Waiting for input. WASD H Q\n");
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
                    sendPacket(&phelp, &dest);
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
                lcdUpdate();
            }
        }
    } else {

        //Create a PING packet to send.
        Packet psend;
        psend.opcode = PING_REQUEST;
        psend.flags = 0; //Toggle these flags to trigger different things.
        //SET_ACK(psend.flags);
        psend.SRCUID = (uint16_t) atoi(listenPort); //This machines UID.
        psend.DESTUID = (uint16_t) atoi(destinationPort); //Destination machines UID.
        psend.ORIGINUID = 0; //Original Machines UID.
        strcpy(psend.SRCFIRSTNAME, "HaHa"); //First Name
        strcpy(psend.SRCLASTNAME, "Button"); //Last Name

        printf("psend.SRCUID:       %d\n", psend.SRCUID);
        printf("psend.DESTUID:      %d\n", psend.DESTUID);
        printf("psend.ORIGINUID:    %d\n", psend.ORIGINUID);
        printf("psend.SRCFIRSTNAME: %s\n", psend.SRCFIRSTNAME);
        printf("psend.SRCLASTNAME:  %s\n", psend.SRCLASTNAME);


        //Packets
        int count = 0;
        //sendPacket(&psend, &dest);
        Packet prec; //Receive Packet.
        Base src; //Receive Base Source Packet. //TODO implement

        for (;;) {
            //Call recvPacket to poll the receive buffer.
            if (recvPacket(&prec, &src) == TRUE) {
                printf("Count: %d\n", count++);
                sleep(2);
                sendPacket(&psend, &dest);
                sleep(2);
            }
        }
    }

done: lcdDestroy();
      menuDestroy(menu);

      return error;
}
