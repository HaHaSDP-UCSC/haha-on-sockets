/**
 * @file baseopcode.h
 * @brief Base communication opcodes.
 * @author Kevin Lee
 * @version
 * @date 2017-03-14
 *
 * These functions will call the functions in network.h
 * The network.h file is the actual implementation of network comm.
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
