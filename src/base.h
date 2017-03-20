/**
 * @file base.h
 * @brief Definition of the base
 * @author Kevin Lee
 * @versions
 * @date 2017-03-07
 */

#ifndef _HA_BASE_
#define _HA_BASE_

typedef struct{
    //Base attributes
    char *addr;
    uint16_t UID; //TODO Fix this.
    // Unix storage file, TODO remove when porting to mC
    char *fileName[128];
    // User data, TODO find a better place for this
    char firstName[17];
	char lastName[17];
	char phone[16];
	char homeAddr[75];
    // Friends array, TODO definitely find a different place for this
    uint16_t friends[128]; //TODO fix all of the variables.
    int dying;
    //etc
} Base;


#endif // _HA_BASE_
