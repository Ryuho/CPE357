#  CPE 357 Winter 2009
#  Lab 2 Part a
#  Author: Ryuho Kudo

SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -g -std=c99 -pedantic  $(SUS3) $(HARDEN)
LDFLAGS=

ALL = sigmac sigfun

all: $(ALL)

sigmac:	sigmac.o
	$(CC) $(LDFLAGS) -o $@ $^

sigmac.o: sigmac.c sigmac.h
	$(CC) $(CFLAGS) -c $<

sigfun:	sigfun.o
	$(CC) $(LDFLAGS) -o $@ $^

sigfun.o: sigfun.c sigfun.h sigs.c
	$(CC) $(CFLAGS) -c $<


.PHONY: clean

clean:
	rm -rf *.o *.gch core* $(ALL)

