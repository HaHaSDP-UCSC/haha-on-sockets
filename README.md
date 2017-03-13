# HaHaOnSockets

A Linux based proof of concept for the Home Assistance Button 	project.

## Directory Structure

- **[docs/](docs)**
   - **Makefile**
- **README.md**
- **[bin/](bin)**
   - **base**
   - **server**
   - **main**
- **[src/](src)**
   - **menu.h**: Menu and MenuItems library defines
   - **networkdevice.h**: Base to base communication
   - **buttoncomm.c**
   - **buttondevice.h**: Include the function prototypes and stuctures
   - **menu.c**: Menu and MenuItem library functions
   - **basecomm.h**: Base communication
   - **neighbor.h**: Definitions of Neighbor info
   - **network.h**: Definitions of network types
   - **buttondevice.c**: Implementation of the button communication
   - **server.c**: Don't use this
   - **buttoncomm.h**
   - **baseopcode.h**
   - **networkdevice.c**: Implementation of network specific communication
   - **DEV_xbee.h**: A beginning for Xbee implementation, reference
   - **halib.c**: stdlib for HAHA project, contains global functions
   - **init.h**: Initialization headers
   - **[button/](src/button)**
      - **buttondevice.h**
      - **buttondevice.c**
      - **button.h**
      - **button.c**
      - **main.c**
   - **button.h**
   - **init.c**: Initialization file
   - **lcd.c**: LCD application level, given menu, prints to LCD
   - **storagedevice.h**
   - **basecomm.c**: Application layer implementation
   - **storage.h**
   - **README**
   - **storage.c**
   - **halib.h**: stdlib for HAHA project, contains imports and defines
   - **main.h**
   - **Makefile**: Makefile for src/ dir
   - **lcd.h**: LCD application level, given menu, prints to LCD
   - **base.h**: Definition of the base
   - **flags.h**
   - **main.c**: Main program of the base station
   - **buttonnetwork.h**
- **Makefile**: Makefile for top level dir
