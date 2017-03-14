/**
 * @file neighbor.h
 * @brief Definitions of Neighbor info
 * @author Kevin Lee
 * @version
 * @date 2017-03-07
 */

#ifndef _HA_NEIGHBOR_
#define _HA_NEIGHBOR_

#include "halib.h"
#include "base.h"

//#define MAXNAME 34
#define MAXFIRSTNAME 17  // Null terminated
#define MAXLASTNAME 17   // Null terminated


#define MAXUID 2         // Null terminated
//#define MAXDEST 2
#define MAXHOMEADDR 75   // Null terminated

#define MAXPHONE 16      // Null terminated
#define MAXBUFFER 255 //TODO CORRECT THIS

typedef struct{
    char *firstname;
    char *lastname;
    Base *base; //Neighbors have bases
    //etc
} Neighbor;

#endif // _HA_NEIGHBOR_
