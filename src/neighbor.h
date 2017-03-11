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
#define MAXFIRSTNAME 17
#define MAXLASTNAME 17

#define MAXUID 2
//#define MAXDEST 2
#define MAXHOMEADDR 75
#define MAXPHONE 16

#define MAXBUFFER 255 //TODO CORRECT THIS

typedef struct{
    char *firstname;
    char *lastname;
    Base *base; //Neighbors have bases
    //etc
} Neighbor;

#endif // _HA_NEIGHBOR_
