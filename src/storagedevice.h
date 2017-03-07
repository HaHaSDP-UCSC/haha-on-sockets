/**
 * @file storagedevice.h
 * @brief
 * @author
 * @version
 * @date 2017-03-07
 */

#ifndef _HA_STORAGEDEVICE_
#define _HA_STORAGEDEVICE_

#include "halib.h"
#include "storage.h"

//For sockets this will probably just be some fread /fwrite()
//Still need to define the settings before these can be done completely
bool _write_settings();
bool _read_settings();


#endif // _HA_STORAGEDEVICE_
