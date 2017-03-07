# Makefile by Kevin Lee. 
# Modified: 2/27/2017

# To compile, 
# run "make client", "make server", and "make test"
# The executables can then be run with 
# "./bin/server", "./bin/client", "./bin/test"
# Use "make clean" to delete object files, executables files

MKFILE		= Makefile

SUPPRESS 	= #-Wno-incompatible-pointer-types
GCC     	= gcc -g -O0 -Wall ${SUPPRESS}#Suppressed

CSOURCE   	= src/server.c src/client.c src/functions.c src/functions.h
EXECBIN   	= ${EXECBINSERV} ${EXECBINCLIENT} ${EXECBINTEST}
EXECBINSER  	= bin/server
EXECBINCLI 	= bin/main
EXECBINTEST 	= bin/test
SOURCES   	= ${CSOURCE} ${MKFILE}

all:
#%.o : src/%.c
#	${GCC} -c $<

server.o: src/server.c src/devtools.h
	${GCC} -c src/server.c
	
basecomm.o: src/basecomm.c src/basecomm.h src/devtools.h src/networkdevice.h
	${GCC} -c src/basecomm.c
	
networkdevice.o: src/networkdevice.c src/networkdevice.h src/devtools.h
	${GCC} -c src/networkdevice.c
	
#test.o: src/test.c src/functions.h src/devtools.h
#	${GCC} -c src/test.c

main.o: src/hahaProgram.h src/devtools.h src/basecomm.c src/networkdevice.c src/storage.c src/buttoncomm.c
	${GCC} -c src/main.c

main: networkdevice.o basecomm.o main.o 
	${GCC} -o bin/main main.o basecomm.o networkdevice.o 
#client: client.o functions.o
#	${GCC} -o bin/client client.o functions.o #-lpthread

server: server.o functions.o
	${GCC} -o bin/server server.o functions.o
	
test: server.o functions.o client.o test.o
	${GCC} -o bin/test test.o functions.o

clean : 
	rm -f *.o
	rm -f ${EXECBIN}

