/**
 * @file buttondevice.h
 * @brief Include the function prototypes and stuctures
 * @author Jamie
 * @version
 * @date 2017-03-07
 *
 * Uses TCP/IP
 */

#ifndef _HA_BUTTONDEVICE
#define _HA_BUTTONDEVICE

#include "button.h"
#include "buttonnetwork.h"
#include <math.h>

#define LONG_PRESS 3

/* Must Implement for App */
void _init_button();
// bool _recv_alert(char* data); //from sockets
// bool _poll_button(char *b); //

bool _recv_alert(void);
bool _poll_button(void);
int _check_battery_life();
/* Other Functions for device specific networking */
//Socket stuff

typedef enum {
        STANDBY,
        PAIR,
        CONNECTION,
        SLEEP,
        ACTIVE
} button_state;

typedef struct {
        float batteryLife;
} button_data;


#endif
