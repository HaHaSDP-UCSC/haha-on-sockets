# HaHaOnSockets

A Linux based proof of concept for the Home Assistance Button project.

## Directory Structure

- bin/
  - base
  - server
- docs/
- Makefile: Makefile for top level dir
- README.md
- src/
  - base.c: Base station code, main of this repo
  - basecomm.c
  - basecomm.h
  - base.h
  - button/
    - button.c
    - buttondevice.c
    - buttondevice.h
    - button.h
  - buttoncomm.c
  - buttoncomm.h
  - buttondevice.c
  - buttondevice.h
  - button.h
    - main.c
  - buttonnetwork.h
  - devtools.h
  - DEV_xbee.h
  - flags.h
  - hahaProgram.h
  - halib.c: stdlib for HAHA project, contains global functions
  - halib.h: stdlib for HAHA project, contains imports and defines
  - lcd.c: LCD application level, given menu, prints to LCD
  - lcd.h: LCD application level, given menu, prints to LCD
  - main.c
  - Makefile: Makefile for src/ dir
  - menu.c: Menu and MenuItem library functions
  - menu.h: Menu and MenuItems library defines
  - neighbor.h
  - networkdevice.c
  - networkdevice.h
  - network.h
  - README
  - server.c
  - storage.c
  - storagedevice.h
  - storage.h
