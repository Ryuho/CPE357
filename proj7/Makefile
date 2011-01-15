#  CPE 357 Winter 2009
#  -------------------
#  makefile for Prject7 (mush).
#
#  @author Ryuho Kudo

CC=gcc
SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -std=c99 -pedantic -g  $(SUS3) $(HARDEN)
LDFLAGS=

ALL= mush
	
all:  $(ALL)

mush: mush.o parseline.o
	$(CC) $(LDFLAGS) -o $@ $^

mush.o: mush.c mush.h 
	$(CC) $(CFLAGS) -c $<

parseline.o: parseline.c parseline.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)
