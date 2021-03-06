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
#include <pthread.h>

// Global variables
Menu *menu;
char *listenPort;
char *destinationPort;

Packet psend;
Packet phelp;
int inHelpMode = false; //TODO need signal from menu interface.
// pthread_mutex_t acceptReqMtx;

int tid = 0;

void listenthread();

/**
 * @brief Setup
 */
void initMain() {
    menu = initMenus();
    init_network(listenPort);
    lcdInit();
    acceptReq = ERROR;
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
    int err = FALSE; //TODO correct this later
    if (argc != 3) {
        printe("usage: %s PORT FILE\n"
                "\tPORT\tListening port\n"
                "\tFILE\tStorage file\n", argv[0]);
        exit(0);
        //printex("usage: <listenport> <destinationport>\n");
    }

    // Get command line arguments
    listenPort = argv[1];
    self.UID = (uid) atoi(argv[1]);
    char* inputFile = argv[2];
    destinationPort = "8000"; // DO NOT USE
    // Destination should be based on Base.friends[]

    // Initialize
    initMain();
    initBase(&self, inputFile);

    // Register interrupts

    //Create a generic packet to send.
    psend.opcode = PING_REQUEST;
    psend.flags = 0; //Toggle these flags to trigger different things.
    //SET_ACK(psend.flags);
    psend.SRCUID = (uint16_t) atoi(listenPort); //This machines UID.
    psend.DESTUID = (uint16_t) atoi(destinationPort); //Destination machines UID.
    psend.ORIGINUID = 65535; //Original Machines UID.
    strcpy(psend.SRCFIRSTNAME, "HaHa"); //First Name
    strcpy(psend.SRCLASTNAME, "Button"); //Last Name
    strcpy(psend.SRCHOMEADDR, "4657 Where the Sidewalk Ends St. Apartment 23\n"
            "Santa Cruz, CA 12345-9876");
    strcpy(psend.SRCPHONE, "123-456-7890"); //TODO Should actually be unformatted.
    psend.ttl = 0;

    printd("psend.SRCUID:       %d\n", psend.SRCUID);
    printd("psend.DESTUID:      %d\n", psend.DESTUID);
    printd("psend.ORIGINUID:    %d\n", psend.ORIGINUID);
    printd("psend.SRCFIRSTNAME: %s\n", psend.SRCFIRSTNAME);
    printd("psend.SRCLASTNAME:  %s\n", psend.SRCLASTNAME);
    printd("phelp.SRCHOMEADDR:\n%s\n", psend.SRCHOMEADDR);
    printd("phelp.SRCPHONE:     %s\n", psend.SRCPHONE);
    printd("phelp.ttl: %d\n", psend.ttl);

    //Create a HELP packet to send.
    phelp.opcode = HELP_REQUEST;
    phelp.flags = 0; //Toggle these flags to trigger different things.
    phelp.SRCUID = (uint16_t) atoi(listenPort);
    phelp.DESTUID = (uint16_t) atoi(destinationPort);
    phelp.ORIGINUID = 65535;
    strcpy(phelp.SRCFIRSTNAME, self.firstName);
    strcpy(phelp.SRCLASTNAME, self.lastName);
    strcpy(phelp.SRCPHONE, self.phone); //TODO Should actually be unformatted.
    strcpy(phelp.SRCHOMEADDR, self.homeAddr);
    phelp.ttl = 0;

    printd("\n");
    printd("phelp.SRCUID:       %d\n", phelp.SRCUID);
    printd("phelp.DESTUID:      %d\n", phelp.DESTUID);
    printd("phelp.ORIGINUID:    %d\n", phelp.ORIGINUID);
    printd("phelp.SRCFIRSTNAME: %s\n", phelp.SRCFIRSTNAME);
    printd("phelp.SRCLASTNAME:  %s\n", phelp.SRCLASTNAME);
    printd("phelp.SRCHOMEADDR:\n%s\n", phelp.SRCHOMEADDR);
    printd("phelp.SRCPHONE:     %s\n", phelp.SRCPHONE);
    printd("phelp.ttl: %d\n", phelp.ttl);

    printf("Creating thread\n");
    if (pthread_create(&tid, NULL, listenthread, NULL)) {
        //TODO something
        printe("Failed to open pthread.\n");
    }

    int pid = 1;
    //pid = fork(); //Turn this off and set the PID to use only MENU or PACKETs
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
                    phelp.SRCUID = (uint16_t) atoi(listenPort);
                    strcpy(phelp.SRCFIRSTNAME, self.firstName);
                    strcpy(phelp.SRCLASTNAME, self.lastName);
                    strcpy(phelp.SRCHOMEADDR, self.homeAddr);
                    strcpy(phelp.SRCPHONE, self.phone); //TODO Should actually be unformatted.
                    sendPacket(&phelp, self.friends[0]);
                    printf("Sending packet to %u\n", self.friends[0]);
                    inHelpMode = true;
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
        }
    } else {
    }
done:

    writeBase(&self);
    lcdDestroy();
    menuDestroy(menu);

    return err;
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
}

void listenthread() {
    Packet prec; //Receive Packet.
    Base unused1; //Receive Base Source Packet.

    while (1) {
        if (inHelpMode) {
            time_t begin, end;
            begin = time(NULL);
            int friendsLeft = 0;
            int numFriends = 4;
            int timeinterval = 10; //Seconds before calling next person.
            bool rejected = 0;

            while (self.friends[friendsLeft] > 0) {
                end = time(NULL);
                if (difftime(end, begin) >= timeinterval || rejected) {
                    printd("Time: %.1f\n", difftime(end, begin));
                    begin = time(NULL);
                    //Start going down a list of friends.
                    printv("Current Friend %d @ %d not viable.\n",
                            friendsLeft, self.friends[friendsLeft]);
                    //Load in next friend.
                    friendsLeft++;
                    sendPacket(&phelp, self.friends[friendsLeft]);
                    rejected = false;
                }
                if (recvPacket(&prec, &unused1) == TRUE) {
                    printv("Received Packet in help mode.\n");
                    if (prec.opcode == HELP_REQUEST && (IS_ACK(prec.flags))) {
                        //This friend is connected to network. TODO do stuff later
                        printv("Friend is on the network.\n");
                    }

                    if (prec.opcode == HELP_RESPONSE
                            && (!IS_ACK(psend.flags))) {
                        //Check if this is the friend we are looking for.
                        //TODO compares the source with whom we current friend check.
                        if (prec.SRCUID == self.friends[friendsLeft]) {
                            if (IS_ACCEPT(prec.flags)) {
                                printv("Here comes the cavalry.\n");
                                friendsLeft = 0;
                                inHelpMode = false;
                                break; //Go back into normal state //TODO this should be different alarm mode.
                            } else {
                                printv("Your friend rejected your Request.\n");
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
            }

            if (inHelpMode == true && self.friends[friendsLeft] <= 0) {
                //Out of friends
                printe("No friends left to save you.\n");
                friendsLeft = 0;
                inHelpMode = false;
                printe("Resetting state.\n");
            }
        } else {
            //Normal send mode.

            //Listening mode.
            if (recvPacket(&prec, &unused1) == TRUE) {
                printf("Received Packet in Listen mode.\n");
                if (prec.opcode == HELP_REQUEST && (!IS_ACK(prec.flags))) {
                    printd("Not ACK found.\n");
                    uid myFriend; //TODO compare the source with friends list.
                    int numFriends = 4;
                    int i = 0;
                    while (i < numFriends) {
                        myFriend = self.friends[i];
                        if (prec.SRCUID == myFriend) {
                            printv("My friend is in need @ %d\n", prec.SRCUID);
                            jumpToEvent(&menu);
                            self.dying = prec.SRCUID;
                            //Send ACK packet.
                            SET_ACK(prec.flags);
                            prec.SRCUID = self.UID;
                            sendPacket(&prec, myFriend);

                            time_t begin, end;
                            begin = time(NULL);
                            end = time(NULL);
                            int timeinterval = 10; //Seconds before calling next person.
                            while (difftime(end, begin) < timeinterval) {
                                end = time(NULL);
                                if (acceptReq == TRUE) {
                                    printv("I am going to help you.\n");
                                    //TODO generate the help response packet for accepting.
                                    prec.opcode = HELP_RESPONSE;
                                    CLR_ACK(prec.flags);
                                    SET_ACCEPT(prec.flags);
                                    prec.SRCUID = self.UID;
                                    sendPacket(&prec, myFriend);
                                    break;
                                } else if (acceptReq == FALSE) {
                                    printv("I am unwilling to help my friend in need.\n");
                                    //TODO generate the help response packet for canceling.
                                    prec.opcode = HELP_RESPONSE;
                                    CLR_ACCEPT(prec.flags);
                                    sendPacket(&prec, myFriend);
                                    break;
                                }
                            }
                            printd("Time: %.1f\n", difftime(end, begin));
                            if (acceptReq == ERROR) {
                                printe("Timed out on HELP_REQUEST @ %d\n",
                                        prec.SRCUID);
                            }
                            acceptReq = ERROR;
                            break;
                        }
                        i++;
                    }
                } else {
                    if (prec.opcode == PING_REQUEST && (!IS_ACK(prec.flags))) {
                        printd("PING REQ.\n");
                    }
                    //Not a help request.
                    printd("A request was sent at the wrong time.\n");
                }
            }
        }
    }
}
/**
  int timervalue;
  (void) signal(SIGALRM, timer_callback);
  timer_start(timervalue);
  while (1) {

  }*/
