/* Definitions of Neighbor info */

#include "devtools.h"
#include "base.h"

#define MAXNAME 34
#define MAXFIRST 17
#define MAXLAST 17

#define MAXUID 2
#define MAXDEST 2
#define MAXADDR 80
#define MAXPHONE 16

typedef struct{
   char *firstname;
   char *lastname;
   Base *base; //Neighbors have bases
   //etc
}Neighbor;
