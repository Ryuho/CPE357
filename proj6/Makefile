#  CPE 357 Winter 2009
#  -------------------
#  makefile for Prject6 (Parseline).
#
#  @author Ryuho Kudo

CC=gcc
SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -std=c99 -pedantic -g  $(SUS3) $(HARDEN)
LDFLAGS=

ALL= parseline
	
all:  $(ALL)


parseline: parseline.o
	$(CC) $(LDFLAGS) -o $@ $^

parseline.o: parseline.c parseline.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)
