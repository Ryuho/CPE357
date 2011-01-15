#Ryuho Kudo
#lab9a 
#Makefile for lab10a

CC = gcc
CFLAGS = -Wall -g -std=c99 -pedantic 
LDFLAGS = -lm
LIBS=-lrt

ALL = qreadr

all: $(ALL)

qreadr.o: qreadr.c qreadr.h
	$(CC) $(CFLAGS) -c $<

qreadr: qreadr.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

.PHONY:	clean

clean:
	rm -rf core* *.o *.gch $(ALL)
