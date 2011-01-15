#  CPE 357 Winter 2009
#  Lab 1 Part c
#  Author: Ryuho Kudo

SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -g -std=c99 -pedantic $(SUS3) $(HARDEN)
LDFLAGS=

ALL=lab01c

all:  $(ALL)

lab01c: lab01c.o
	$(CC) $(LDFLAGS) -o $@ $^

lab01c.o: lab01c.c lab01c.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)

