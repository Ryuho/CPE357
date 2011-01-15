#  CPE 357 Winter 2008
#  -------------------
#  makefile for lab05a (myls).
#
#  @author Ryuho Kudo

CC=gcc
SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -std=c99 -pedantic -g  $(SUS3) $(HARDEN)
#LDFLAGS=

ALL = myls

all:	$(ALL)

myls:	myls.o
	$(CC) $(LDFLAGS) -o $@ $^

myls.o:	myls.c myls.h
	$(CC) $(CFLAGS) -c $^

.PHONY:	clean

clean:
	rm -rf core* *.o *.gch $(ALL)

