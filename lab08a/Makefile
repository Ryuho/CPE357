#  CPE 357 Fall 2008
#  Lab 8 a
#  Author: Ryuho Kudo


CC=gcc
CFLAGS=-Wall -g -std=c99 -pedantic
LDFLAGS=


ALL= mylimits
	
all:  $(ALL)

mylimits: mylimits.o
	$(CC) $(LDFLAGS) -o $@ $^

mylimits.o: mylimits.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)
