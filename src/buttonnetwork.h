/**
 * @file buttonnetwork.h
 * @brief
 * @author
 * @version
 * @date 2017-03-07
 */

/* Define the types of the button comm */
#ifndef _HA_BUTTONNET
#define _HA_BUTTONNET

#include "flags.h"

/* BUTTON COMMUNICATION */
//Struct for future dev of multiple buttons
typedef struct{
   //Button messages
   int batteryLevel;
   flags flags;
   char* message; //last message?
}Beacon;

#endif
