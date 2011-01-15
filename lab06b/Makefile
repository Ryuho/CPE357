#  CPE 357 Fall 2008
#  Lab 6 c
#  Author: Ryuho Kudo


CC=gcc
CFLAGS=-Wall -g -std=c99 -pedantic
LDFLAGS=


ALL= packbits
	
all:  $(ALL)


packbits: packbits.o
	$(CC) $(LDFLAGS) -o $@ $^

packbits.o: packbits.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)
