# HaHaOnSockets

A Linux based proof of concept for the Home Assistance Button 	project.

## Directory Structure

- **Makefile**: Makefile for top level dir
- **README.md**
- **[bin/](bin)**
   - **base**
   - **main**
   - **server**
- **[docs/](docs)**
   - **Makefile**
- **[src/](src)**
   - **DEV_xbee.h**: A beginning for Xbee implementation, reference
   - **Makefile**: Makefile for src/ dir
   - **README**
   - **base.h**: Definition of the base
   - **basecomm.c**: Application layer implementation
   - **basecomm.h**: Base communication
   - **baseopcode.h**: Base communication opcodes.
   - **[button/](src/button)**
      - **button.c**
      - **button.h**
      - **buttondevice.c**
      - **buttondevice.h**
      - **main.c**
   - **button.h**
   - **buttoncomm.c**
   - **buttoncomm.h**
   - **buttondevice.c**: Implementation of the button communication
   - **buttondevice.h**: Include the function prototypes and stuctures
   - **buttonnetwork.h**
   - **flags.h**: Flags to be set in packets.
   - **halib.c**: stdlib for HAHA project, contains global functions
   - **halib.h**: stdlib for HAHA project, contains imports and defines
   - **init.c**: Initialization file
   - **init.h**: Initialization headers
   - **lcd.c**: LCD application level, given menu, prints to LCD
   - **lcd.h**: LCD application level, given menu, prints to LCD
   - **main.c**: Main program of the base station
   - **main.h**
   - **menu.c**: Menu and MenuItem library functions
   - **menu.h**: Menu and MenuItems library defines
   - **neighbor.h**: Definitions of Neighbor info
   - **network.h**: Definitions of network types
   - **networkdevice.c**: Implementation of network specific communication
   - **networkdevice.h**: Base to base communication
   - **server.c**: Don't use this
   - **storage.c**
   - **storage.h**
   - **storagedevice.h**
- **test.base**
