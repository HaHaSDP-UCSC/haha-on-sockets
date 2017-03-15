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

#include <time.h>
#include <signal.h>

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
  time_t timerid;

  void timer_start(int timervalue) {
  struct itimerspec timval;
  timval.it_value.tv_sec = 1; //Wait before sending signal
  timval.it_value.tv_nsec = 0;
  timval.it_interval.tv_sec = timervalue; //Timer interval.
  timval.it_interval.tv_nsec = 0;

  if (timer_create(CLOCK_REALTIME, NULL, &timerid)) {
  printe("Error creating timer.\n");
  }

  struct itimerspec oldval; //Old value of timer. TODO remove.
  if (timer_settime(timerid, 0, &timval, &oldval)) {
  printe("Error setting timer.\n");
  }
  }

  void stop_timer(void) {
  struct itimerspec timval;
  timval.it_value.tv_sec = 0;
  timval.it_value.tv_nsec = 0;
  timval.it_interval.tv_sec = 0;
  timval.it_interval.tv_nsec = 0;
  struct itimerspec oldval; //Old value of timer. TODO remove.
  if (!timer_settime(timerid, 0, &timval, &oldval))
  printd("Timer stopped.\n");
  else
  printe("Timer failed to stop.\n");
  }

  void timer_callback(int timsig) {
  printd("Timer went off.\n");
  }*/

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

    // Register interrupts

    //Create a generic packet to send.
    Packet psend;
    psend.opcode = PING_REQUEST;
    psend.flags = 0; //Toggle these flags to trigger different things.
    //SET_ACK(psend.flags);
    psend.SRCUID = (uint16_t) atoi(listenPort); //This machines UID.
    psend.DESTUID = (uint16_t) atoi(destinationPort); //Destination machines UID.
    psend.ORIGINUID = 65535; //Original Machines UID.
    strcpy(psend.SRCFIRSTNAME, "HaHa"); //First Name
    strcpy(psend.SRCLASTNAME, "Button"); //Last Name
    strcpy(psend.SRCPHONE, "123-456-7890"); //TODO Should actually be unformatted.
    strcpy(psend.SRCHOMEADDR, "4657 Where the Sidewalk Ends St. Apartment 23\n"
            "Santa Cruz, CA 12345-9876");
    psend.ttl = 0;

    printf("psend.SRCUID:       %d\n", psend.SRCUID);
    printf("psend.DESTUID:      %d\n", psend.DESTUID);
    printf("psend.ORIGINUID:    %d\n", psend.ORIGINUID);
    printf("psend.SRCFIRSTNAME: %s\n", psend.SRCFIRSTNAME);
    printf("psend.SRCLASTNAME:  %s\n", psend.SRCLASTNAME);
    printf("phelp.SRCPHONE:     %s\n", psend.SRCPHONE);
    printf("phelp.SRCHOMEADDR:\n%s\n", psend.SRCHOMEADDR);
    printf("phelp.ttl: %d\n", psend.ttl);

    //Create a HELP packet to send.
    Packet phelp;
    phelp.opcode = HELP_REQUEST;
    phelp.flags = 0; //Toggle these flags to trigger different things.
    SET_ACK(phelp.flags);
    phelp.SRCUID = (uint16_t) atoi(listenPort);
    phelp.DESTUID = (uint16_t) atoi(destinationPort);
    phelp.ORIGINUID = 65535;
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

    Base dest;
    dest.addr = "127.0.0.1"; //Network Address.
    dest.UID = destinationPort;
    printf("dest.DESTUID: %s\n", dest.UID);

    int pid = 0;
    pid = fork(); //Turn this off and set the PID to use only MENU or PACKETs
    if (pid != 0) {
        //Menu
        printd("Waiting for input. WASD H Q\n");
        while (true) {
            char input = getchar();
            int move = -1;
            switch (input) {
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
                    // YES GOTOs TODO Why are we even exiting main.
                    goto done;
                    break;
                case '\n':
                    break;
            }
            if (move != -1) {
                menuSetLcd(menu);
                lcdUpdate();
            }
        }
    } else {
        /**
        //Packets
        int count = 0;
        sendPacket(&psend, &dest);
        Packet prec; //Receive Packet.
        Base src; //Receive Base Source Packet. //TODO implement

        for (;;) {
        //Call recvPacket to poll the receive buffer.
        if (recvPacket(&prec, &src) == TRUE) {
        printf("Count: %d\n", count++);
        sendPacket(&psend, &dest);
        sleep(4);
        }
        }
        */
        int inHelpMode = false; //TODO need signal from menu interface.
        Packet prec; //Receive Packet.
        Base src; //Receive Base Source Packet.

        while (1) {
            if (inHelpMode) {
                time_t begin, end;
                begin = time(NULL);
                int friendsLeft = 0;
                int numFriends = 4;
                int timeinterval = 5; //Seconds before calling next person.
                bool rejected = 0;

                while (friendsLeft < numFriends) {
                    if (recvPacket(&prec, &src) == TRUE) {
                        printf("Received Packet.\n");
                        if (prec.opcode == HELP_REQUEST && (IS_ACK(prec.flags))) {
                            //This friend is connected to network. TODO do stuff later
                        }

                        if (prec.opcode == HELP_RESPONSE
                                && (!IS_ACK(psend.flags))) {
                            //Check if this is the friend we are looking for.
                            //TODO compares the source with whom we current friend check.
                            if (prec.SRCUID == atoi(dest.UID)) {
                                if (IS_ACCEPT(prec.flags)) {
                                    printv("Here comes the cavalry.\n");
                                } else {
                                    printv("Rejected.\n");
                                    //immediately go to next person.
                                    rejected = true;
                                }
                            } else {
                                //Not the SRCUID we were expecting. TODO probably drop this.
                            }
                        } else {
                            //Not a help response.
                            //TODO a different type of packet.
                        }
                    }
                    end = time(NULL);
                    if (difftime(end, begin) >= timeinterval || rejected) {
                        printd("Time: %.1f\n", difftime(end, begin));
                        begin = time(NULL);
                        //Start going down a list of friends.
                        printv("Current Friend %d @ %s didn't answer.\n",
                                friendsLeft, dest.UID);
                        //TODO load in next friend. Needs that storage thing.
                        sendPacket(&phelp, &dest);
                        friendsLeft++;
                        rejected = false;
                    }
                }

                if (friendsLeft >= numFriends) {
                    //Out of friends
                    printe("No friends left to save you.\n");
                }
                while (1) {
                    //Burn trees.
                }
            } else {
                //Listening mode.
                if (recvPacket(&prec, &src) == TRUE) {
                    printf("Received Packet.\n");
                    if (prec.opcode == HELP_REQUEST
                            && (!IS_ACK(phelp.flags))) {
                        uid myFriend = 0; //TODO compares the source with friends list.
                        if (prec.SRCUID == myFriend) {
                            bool accept = false; //TODO user input needs to block.
                            if (accept) {
                                printv("I am going to help you.\n");
                                //TODO generate the help response packet for accepting.
                            } else {
                                printv("Do not help.\n");
                                //TODO generate the help response packet for canceling.
                            }
                        } else {
                            //Not the SRCUID we were expecting. TODO
                        }
                    } else {
                        if (prec.opcode == HELP_REQUEST && (!IS_ACK(phelp.flags))) {

                        }
                        //Not a help request.
                    }
                }
            }
        }
        /**
          int timervalue;
          (void) signal(SIGALRM, timer_callback);
          timer_start(timervalue);
          while (1) {

          }
          */
    }
done: lcdDestroy();
      menuDestroy(menu);

      return error;
}
