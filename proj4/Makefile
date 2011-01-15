#  CPE 357 Winter 2008
#  -------------------
#  makefile for Prject4 (Huffman Coding).
#
#  @author Ryuho Kudo

CC=gcc
SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -std=c99 -pedantic -g  $(SUS3) $(HARDEN)
LDFLAGS=

ALL = huff-e huff-d

all:	$(ALL)

huff-e:	huff-e.o  huff.o
	$(CC) $(LDFLAGS) -o $@ $^

huff-e.o:	huff-e.c huff.h
	$(CC) $(CFLAGS) -c $^

huff-d:	huff-d.o huff.o
	$(CC) $(LDFLAGS) -o $@ $^

huff-d.o:	huff-d.c huff.h
	$(CC) $(CFLAGS) -c $^

huff.o:	huff.c huff.h
	$(CC) $(CFLAGS) -c $^
	
.PHONY:	clean

clean:
	rm -rf core* *.o *.gch $(ALL)

