/* This file can serve as a beginning for the Xbee implementation. For now it
* serves as reference
*/

//Different modes
#define UNICAST 	0
#define BROADCAST 	1
#define CLUSTER 	2

//Different RX frame types
#define _16B 		0 //only for XBee-802.15.4
#define _64B 		1 //only for XBee-802.15.4
#define NORMAL_RX 	2 // Receive packet --> AO=0
#define EXPLICIT_RX	3 // Explicit RX Indicator --> AO=1

//Different Max Sizes Used in Libraries
#define MAX_DATA			300
#define	MAX_PARSE			300
#define	MAX_BROTHERS		5
#define MAX_FINISH_PACKETS	5

//Differents addressing types
#define	MY_TYPE		0
#define	MAC_TYPE	1

//Variable for debugging
#define	DEBUG_XBEE	0

// Replacement Policy
#define	XBEE_LIFO	0
#define	XBEE_FIFO	1
#define	XBEE_OUT	2
/******************* DM **************************/
//Awake Time
#define AWAKE_TIME_DIGIMESH_H	0x00
#define AWAKE_TIME_DIGIMESH_M	0x07
#define AWAKE_TIME_DIGIMESH_L	0xD0
//Sleep Time
#define SLEEP_TIME_DIGIMESH_H	0x00
#define SLEEP_TIME_DIGIMESH_M	0x00
#define SLEEP_TIME_DIGIMESH_L	0xC8
//Scan Time
#define SCAN_TIME_DIGIMESH_H	0x00
#define SCAN_TIME_DIGIMESH_L	0x82
//Encryption Mode
#define ENCRYPT_MODE_DIGIMESH	0x00
//Power Level
#define POWER_LEVEL_DIGIMESH	0x04
//Time RSSI
#define TIME_RSSI_DIGIMESH		0x20
//Sleep Options
#define	SLEEP_OPTIONS_DIGIMESH	0x00

/* Structure : used for storing the information returned by other nodes when a
* Node Discovery is performed
*/
struct Node
{

	uint8_t MY[2];//! Structure Variable : 16b Network Address
	uint8_t SH[4];//! Structure Variable : 32b Lower Mac Source
	uint8_t SL[4];//! Structure Variable : 32b Higher Mac Source
	char NI[21];//! Structure Variable : Node Identifier
	uint8_t RSSI;//! Structure Variable : Receive Signal Strength Indicator
};

//! Structure : used for storing the information needed to send or receive a
//! packet, such as the addresses and data
/*!
 */
struct packetXBee
{
  /************ IN ***********/
	uint8_t macDL[4];	//! Structure Variable : 32b Lower Mac Destination
	uint8_t macDH[4];	//! Structure Variable : 32b Higher Mac Destination
	uint8_t mode;//! Structure Variable : Sending Mode:
               //! 0=UNICAST ; 1=BROADCAST ; 2=CLUSTER
	uint8_t naD[2];	//! Structure Variable : 16b Network Address Destination
	char data[MAX_DATA];	//! Structure Variable : Data. All the data here, even when it is > payload
	uint16_t data_length;//! Structure Variable : Real data length.
	uint8_t MY_known;//! Structure Variable : Specifies if Network Address is known:
                   //! 0=unknown net address ; 1=known net address
	uint8_t opt;//! Structure Variable : Sending options (depends on the XBee module)

	/******** APLICATION *******/
	uint8_t macSL[4];//! Structure Variable : 32b Lower Mac Source
	uint8_t macSH[4];//! Structure Variable : 32b Higher Mac Source
	uint8_t naS[2];	//! Structure Variable : 16b Network Address Source
	uint8_t RSSI;//! Structure Variable : Receive Signal Strength Indicator
	long time;//! Structure Variable : Specifies the time when the first fragment of the
            //! packet was received

	/******** OUT **************/
	uint8_t deliv_status;//! Structure Variable : Delivery Status
	uint8_t discov_status;	//! Structure Variable : Discovery Status
	uint8_t true_naD[2];//! Structure Variable : Network Address where the packet has been set
	uint8_t retries;//! Structure Variable : Retries needed to send the packet
};
