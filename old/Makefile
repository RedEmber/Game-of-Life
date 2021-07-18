# This Makefile is set up for Towers
# NOTE: All indented lines are indented with a tab character.

CC=g++
# flag all warnings. default optimization level.
CFLAGS=-Wall -Og
# set up for use in gdb
DFLAGS=-g
PROGS=Life
EXTRA=Cell

all: $(PROGS)

%: %.cpp
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@

clean:
	rm -f $(PROGS) *.o ~*
