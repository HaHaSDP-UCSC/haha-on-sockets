/**
 * @file neighbor.h
 * @brief Definitions of Neighbor info
 * @author
 * @version
 * @date 2017-03-07
 */

#ifndef _HA_NEIGHBOR_
#define _HA_NEIGHBOR_

#include "halib.h"
#include "base.h"

#define MAXNAME 34
#define MAXFIRST 17
#define MAXLAST 17

#define MAXUID 2
//#define MAXDEST 2
#define MAXADDR 75
#define MAXPHONE 16

typedef struct{
    char *firstname;
    char *lastname;
    Base *base; //Neighbors have bases
    //etc
} Neighbor;

#endif // _HA_NEIGHBOR_
