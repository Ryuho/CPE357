#  CPE 357 Winter 2008
#  -------------------
#  makefile for Prject3 (tail implementation).
#
#  @author Ryuho Kudo

CC=gcc
SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -std=c99 -pedantic -g  $(SUS3) $(HARDEN)
LDFLAGS=

ALL = proj3

all:	$(ALL)

proj3:	mytail.o getLine.o
	$(CC) $(LDFLAGS) -o $@ $^

mytail.o:	mytail.c mytail.h
	$(CC) $(CFLAGS) -c $^

getLine.o:	getLine.c getLine.h
	$(CC) $(CFLAGS) -c $^

.PHONY:	clean

clean:
	rm -rf core* *.o *.gch $(ALL)

