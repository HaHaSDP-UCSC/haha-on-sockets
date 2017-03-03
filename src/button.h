#ifndef _HA_BUTTON
#define _HA_BUTTON

typedef char* buttonaddr;
typedef struct{
   //Button attributes
   buttonaddr dest;
   int batterylevel;
}Button;

#endif
