#ifndef _HA_STORAGE
#define _HA_STORAGEDEVICE

#include "devtools.h"

//Need to specify the datatypes and how we will store data.
//If we are using minimal data, JSON might be a good idea.

//Need to store:
//User Info (name, addr, etc)
//Neighbor(Friends) data
//Bluetooth information (addr, etc)
//Network settings

//Depending on memory we may want to store these in structs, or read in settings
//as necessary (from flash/disk);
bool writeSettings();
bool readSettings();

#endif
