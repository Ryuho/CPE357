#  CPE 357 Fall 2008
#  -------------------
#  makefile for Lab 6b (slow).
#
#  @author Ryuho Kudo
CC=gcc
CFLAGS=-Wall -g -std=c99 -pedantic
LDFLAGS=

ALL=slow

all:	$(ALL)

slow:	slow.o
	$(CC) $(LDFLAGS) -o $@ $^

slow.o:	slow.c
	$(CC) $(CFLAGS) -c $^

.PHONY:	clean

clean:
	rm -rf core* *.o *.gch $(ALL)
