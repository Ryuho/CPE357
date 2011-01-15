#  CPE 357 Fall 2008
#  Lab 4 b
#  Author: Ryuho Kudo


CC=gcc
CFLAGS=-Wall -g -std=c99 -pedantic
LDFLAGS=


ALL= museum
	
all:  $(ALL)


museum: museum.o
	$(CC) $(LDFLAGS) -o $@ $^

museum.o: museum.c
	$(CC) $(CFLAGS) -c $<



.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)
