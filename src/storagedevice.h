#ifndef _HA_STORAGEDEVICE
#define _HA_STORAGEDEVICE

#include "devtools.h"
#include "storage.h"

//For sockets this will probably just be some fread /fwrite()
//Still need to define the settings before these can be done completely
bool _write_settings();
bool _read_settings();


#endif
