#Ryuho Kudo
#lab9a 
#Makefile for lab10a

CC = gcc
CFLAGS = -Wall -g -std=c99 -pedantic 
LDFLAGS = -lm
LIBS=-lrt

ALL = threadlets

all: $(ALL)

threadlets.o: threadlets.c threadlets.h
	$(CC) $(CFLAGS) -c $<

threadlets: threadlets.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

.PHONY:	clean

clean:
	rm -rf core* *.o *.gch $(ALL)
