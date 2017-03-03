#ifndef _HA_BUTTON
#define _HA_BUTTON
#include "devtools.h"
#include "buttondevice.h"
//TODO: Need to define the button message specification between button->base
typedef enum PressType{
   HELP,
   HELPALL,
   IMMEDIATE,
   CANCEL
} PressType;

bool sendAlert(char* alert);
bool sendMessage(char* msg);
bool battLow();
void buttonPress(PressType type);

//There are goign to be other things needed, but hard to say until Bluetooth
//implementation details are known
#endif
