# Makefile for CMPE156 Lab 3 by Kevin Lee. 
# Modified: 2/25/2017

# Binary files have already been provided so you don't have to compile it.
# To compile, 
# run "make myclient", "make myserver", and "make test"
# The executables can then be run with 
# "./bin/myserver", "./bin/myclient", "./bin/test_main"
# Use "make clean" to delete object files, executables, clientversion- files
# and stdout.txt if you chose to output to that.

MKFILE		= Makefile

SUPPRESS 	= #-Wno-incompatible-pointer-types
GCC     	= gcc -g -O0 -Wall ${SUPPRESS}#Suppressed

CSOURCE   	= src/myserver.c src/myclient.c src/functions.c src/functions.h
EXECBIN   	= ${EXECBINSERV} ${EXECBINCLIENT} ${EXECBINTEST}
EXECBINSER  = bin/myserver
EXECBINCLI 	= bin/myclient
EXECBINTEST = bin/mytest
SOURCES   	= ${CSOURCE} ${MKFILE}

all:
functions.o: src/functions.c src/functions.h src/devtools.h
	${GCC} -c src/functions.c

myclient.o: src/myclient.c src/functions.h src/devtools.h
	${GCC} -c src/myclient.c

myserver.o: src/myserver.c src/functions.h src/devtools.h
	${GCC} -c src/myserver.c
	
mytest.o: src/test_main.c src/functions.h src/devtools.h
	${GCC} -c src/mytest.c

#%.o : src/%.c
#	${GCC} -c $<
	
myclient: myclient.o functions.o
	${GCC} -o bin/myclient myclient.o functions.o -lpthread

myserver: myserver.o functions.o
	${GCC} -o bin/myserver myserver.o functions.o
	
test: myserver.o functions.o myclient.o test_main.o
	${GCC} -o bin/mytest mytest.o functions.o

clean : 
	rm -f *.o
	rm -f ${EXECBIN}

