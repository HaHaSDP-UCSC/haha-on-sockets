## @file Makefile
#  @brief Makefile for src/ dir
#  @author August Valera, Kevin
#  @version
#  @date 2017-03-07
#

# To compile,
# run "make"
# The executables can then be run with
# "./bin/main" "./bin/base "./bin/server""
# in the top level folder.
# Use "make clean" to delete object files,
# Use "make spotless" to also delete executables files

# Uncomment below to enable stricter warnings
# GCC=gcc -g -O0 -Wall -Wextra # -std=gnu99
SUPPRES = #-Wno-incompatible-pointer-types
GCC     = gcc -g -O0 -Wall ${SUPPRESS} #-lrt realtime timer
#GCC     = gcc -g -O0 ${SUPPRESS}

EXECBIN	=server main
CSOURCE	=${EXECBIN:=.c}
COBJECT	=${CSOURCE:.c=.o}
ISOURCE	=basecomm.c buttoncomm.c halib.c init.c lcd.c menu.c networkdevice.c storage.c
IOBJECT	=${ISOURCE:.c=.o}
EXECDIR	=../bin

all: ${EXECBIN}
	make clean

${EXECBIN}: ${IOBJECT}
	@ make $@.o
	@ ${GCC} -o $@ $@.o $^
	@ [ ! -e ${EXECDIR} ] && mkdir ${EXECDIR} || true
	@ cp $@ ${EXECDIR}
	@ rm -rf $@

%.o: %.c ${ISOURCE}
	@ ${GCC} -c $^ ${ISOURCE}

clean:
	rm -f ${COBJECT} ${IOBJECT}

spotless: clean
	for File in ${EXECBIN}; do rm -f ${EXECDIR}/$$File; done

ci:
	cd .. && make ci

.PHONY: ci clean spotless ${EXECBIN}
