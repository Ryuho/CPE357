#  CPE 357 Fall 2008
#  -------------------
#  makefile for lab7a (ssort).
#
#  @author Ryuho Kudo

CC=gcc
CFLAGS=-Wall -g -std=c99 -pedantic
LDFLAGS=

ALL= ssort

all:	$(ALL)

ssort:  ssort.o 
	$(CC) $(LDFLAGS) -o $@ $^

ssort.o: ssort.c ssort.h
	$(CC) $(CFLAGS) -c $^

.PHONY:	clean

clean:
	rm -rf core* *.o *.gch $(ALL)

