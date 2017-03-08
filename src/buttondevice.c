/**
 * @file buttondevice.c
 * @brief Implementation of the button communication
 * @author Jamie
 * @version
 * @date 2017-03-07
 */

#include "halib.h"
#include "buttondevice.h"
//Standard practice is to include all includes if a file uses it. For now the
//other includes needed are in the other headers

static button_state buttonState;
static button_data accessButtonData;

void _init_button() {
	int buttonPress = 0;
} 

/* This function deals with data received from the base station */
bool _recv_alert(void) { 
	int alertSignal = 1;
	return true;
}

/* This function deals with data to be transmitted to the base station */
bool _poll_button(void) {
	int helpSignal = 1;
	return true;
}

/* This function calculates the battery life */
int _check_battery_life(void) {
	float c = 4, d = 7;
	accessButtonData.batteryLife = c / d * 0.70;
        // printf("The battery is low. Please replace.\n");
        return accessButtonData.batteryLife;
}

