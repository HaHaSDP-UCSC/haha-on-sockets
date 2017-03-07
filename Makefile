## @file Makefile
#  @brief Makefile for top level dir
#  @author August Valera (avalera)
#  @version
#  @date 2017-02-28
#

COMMANDS=clean default spotless
EXTRA=ci edit README.md

default:
	@ cd src && make

ci: default
	@ make README.md
	@ make clean
	@ git commit -av
	@ git push

clean:
	@ cd src && make clean

edit: clean
	@ vim -p src/*
	@ make default

spotless:
	@ cd src && make spotless

README.md:
	@ echo "# HaHaOnSockets" >$@
	@ echo >>$@
	@ echo "A Linux based proof of concept for the Home Assistance Button \
		project." >>$@
	@ echo >>$@
	@ echo "## Directory Structure" >>$@
	@ echo "" >>$@
	@ for File in $$(find | sort -snf | grep -v '/\.' | tail -n +2); do \
		FileBullet=$$(echo $$File | sed 's#[^/]*/# |#g;s#| #  #g;s# |#- #g') && \
		[ ! -d "$$File"  ] && \
		( FileDesc=$$(cat $$File | grep "@brief" | head -n 1 | cut -d '@' -f 2 | \
		cut -d ' ' -f 2-) && [ ! -z "$$FileDesc" ] && \
		[ "$$FileDesc" != "brief" ] && \
		echo "$$FileBullet: $$FileDesc" >>$@ || \
		echo "$$FileBullet" >>$@ ) || echo "$$FileBullet/" >>$@; \
		done
	@ cat $@

.PHONY: ${COMMANDS} ${EXTRA}

