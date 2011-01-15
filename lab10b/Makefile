#Ryuho Kudo
#lab9a 
#Makefile for lab10a

CC=gcc
SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -std=c99 -pedantic -g  $(SUS3) $(HARDEN)
LIBS=-lrt

ALL = adder

all: $(ALL)

adder.o: adder.c adder.h
	$(CC) $(CFLAGS) -c $<

adder: adder.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

.PHONY:	clean

clean:
	rm -rf core* *.o *.gch $(ALL)
