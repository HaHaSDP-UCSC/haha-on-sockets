## @file Makefile
#  @brief Makefile for src/ dir
#  @author August Valera (avalera)
#  @version
#  @date 2017-02-28
#

GCC=gcc -g -O0 -std=gnu99
# Uncomment below to enable stricter warnings
# GCC=gcc -g -O0 -Wall -Wextra -std=gnu99

EXECBIN=base
CSOURCE=${EXECBIN:=.c}
COBJECT=${CSOURCE:.c=.o}
ISOURCE=hahalib.c menu.c
IOBJECT=${ISOURCE:.c=.o}
EXECDIR=../bin

all: ${EXECBIN}
	make clean

${EXECBIN}: ${IOBJECT}
	make $@.o
	${GCC} -o $@ $@.o $^
	[ ! -e ${EXECDIR} ] && mkdir ${EXECDIR} || true
	cp $@ ${EXECDIR}
	rm -rf $@

%.o: %.c ${ISOURCE}
	${GCC} -c $^ ${ISOURCE}

clean:
	rm -f ${COBJECT} ${IOBJECT}

spotless: clean
	rm -f ${EXECDIR}/${EXECBIN}

ci:
	cd .. && make ci

.PHONY: ci clean spotless ${EXECBIN}
