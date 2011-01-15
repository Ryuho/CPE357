#  CPE 357
#  -------------------
#  makefile for solutions
#
#  Last Modified: Tue Jan  6 06:49:17 PST 2009
#  @author Kevin O'Gorman
CC=gcc

# The _POSIX_* symbols only come into play on systems that are POSIX
# but not SUS.
SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -g -std=c99 -pedantic $(SUS3) $(HARDEN)
LDFLAGS=

ALL=lab01b

all:	$(ALL)

lab01b:	driver1b.o lab01b.o
	$(CC) $(LDFLAGS) -o $@ $^

lab01b.o:	lab01b.c lab01b.h
	$(CC) $(CFLAGS) -c $<

driver1b.o:	driver1b.c lab01b.h
	$(CC) $(CFLAGS) -c $<

test:	$(ALL)
	sum driver1b.c lab01b.h Makefile
	./lab01b

clean:
	rm -rf core* *.o *.gch $(ALL)

