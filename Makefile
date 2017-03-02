## @file Makefile
#  @brief Makefile for top level dir
#  @author August Valera (avalera)
#  @version
#  @date 2017-02-28
#

COMMANDS=clean default spotless
EXTRA=ci edit

default:
	@ cd src && make

ci: default
	@ git commit -av
	@ git push

clean:
	@ cd src && make clean

edit: clean
	@ vim -p src/*
	@ make default

spotless:
	@ cd src && make spotless

.PHONY: ${COMMANDS} ${EXTRA}
