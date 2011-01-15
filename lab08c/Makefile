#  CPE 357 Fall 2008
#  Lab 8 b
#  Author: Ryuho Kudo


CC=gcc
CFLAGS=-Wall -g -std=c99 -pedantic
LDFLAGS=


ALL= stackfault segfault
	
all:  $(ALL)


segfault: segfault.o
	$(CC) $(LDFLAGS) -o $@ $^

segfault.o: segfault.c
	$(CC) $(CFLAGS) -c $<

stackfault: stackfault.o
	$(CC) $(LDFLAGS) -o $@ $^

stackfault.o: stackfault.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)
