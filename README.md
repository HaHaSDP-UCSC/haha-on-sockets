# HaHaOnSockets

A Linux based proof of concept for the Home Assistance Button 	project.

## Directory Structure

- Makefile: Makefile for top level dir
- README.md
- bin/
  - base
  - server
- docs/
- src/
  - DEV_xbee.h: A beginning for Xbee implementation, reference
  - Makefile: Makefile for src/ dir
  - README
  - base.c: Base station code, main of this repo
  - base.h: Definition of the base
  - basecomm.c: Application layer implementation
  - basecomm.h: Base communication
  - button/
    - button.c
    - button.h
    - buttondevice.c
    - buttondevice.h
    - main.c
  - button.h
  - buttoncomm.c
  - buttoncomm.h
  - buttondevice.c
  - buttondevice.h: Implementation of the button communication
  - buttonnetwork.h
  - devtools.h: DEPRECIATED, move into halib.h
  - flags.h
  - hahaProgram.h
  - halib.c: stdlib for HAHA project, contains global functions
  - halib.h: stdlib for HAHA project, contains imports and defines
  - lcd.c: LCD application level, given menu, prints to LCD
  - lcd.h: LCD application level, given menu, prints to LCD
  - main.c: Main program of the base station
  - menu.c: Menu and MenuItem library functions
  - menu.h: Menu and MenuItems library defines
  - neighbor.h: Definitions of Neighbor info
  - network.h: Definitions of network types
  - networkdevice.c: Implementation of network specific communication
  - networkdevice.h: Base to base communication
  - server.c: Don't use this
  - storage.c
  - storage.h
  - storagedevice.h
