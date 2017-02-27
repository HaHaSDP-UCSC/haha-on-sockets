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
EXECBINCLI 	= bin/client
EXECBINTEST 	= bin/test
SOURCES   	= ${CSOURCE} ${MKFILE}

all:
functions.o: src/functions.c src/functions.h src/devtools.h
	${GCC} -c src/functions.c

client.o: src/client.c src/functions.h src/devtools.h
	${GCC} -c src/client.c

server.o: src/server.c src/functions.h src/devtools.h
	${GCC} -c src/server.c
	
test.o: src/test.c src/functions.h src/devtools.h
	${GCC} -c src/test.c

#%.o : src/%.c
#	${GCC} -c $<
	
client: client.o functions.o
	${GCC} -o bin/client client.o functions.o #-lpthread

server: server.o functions.o
	${GCC} -o bin/server server.o functions.o
	
test: server.o functions.o client.o test.o
	${GCC} -o bin/test test.o functions.o

clean : 
	rm -f *.o
	rm -f ${EXECBIN}

