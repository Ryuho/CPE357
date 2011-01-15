#  CPE 357 Fall 2008
#  Lab 8 a
#  Author: Ryuho Kudo


CC=gcc
CFLAGS=-Wall -g -std=c99 -pedantic
LDFLAGS=


ALL= wordgrep
	
all:  $(ALL)


wordgrep: wordgrep.o
	$(CC) $(LDFLAGS) -o $@ $^

wordgrep.o: wordgrep.c wordgrep.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)
