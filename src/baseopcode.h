/*
 * baseopcode.h
 *
 *  Created on: Mar 8, 2017
 *      Author: kevin
 */

#ifndef SRC_BASEOPCODE_H_
#define SRC_BASEOPCODE_H_

typedef enum {
	PING_REQUEST = 0x01,
	HELP_REQUEST,
	HELP_RESPONSE,
	HELP_FROM_ANYONE_REQUEST,
	HELP_FROM_ANYONE_RESPONSE,
	FIND_HOPS_REQUEST,
	FIND_HOPS_RESPONSE,
	FIND_NEIGHBORS_REQUEST,
	FIND_NEIGHBORS_RESPONSE,
	FRIEND_REQUEST,
	FRIEND_RESPONSE,
	UNFRIEND_REQUEST
} op;

#endif /* SRC_BASEOPCODE_H_ */
