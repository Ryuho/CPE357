#  CPE 357 Winter 2008
#  -------------------
#  makefile for lab04a (copy).
#
#  @author Ryuho Kudo

CC=gcc
SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -std=c99 -pedantic -g  $(SUS3) $(HARDEN)
#LDFLAGS=

ALL = copy1 copy2 copy6

all:	$(ALL)

copy1:	copy1.o
	$(CC) $(LDFLAGS) -o $@ $^

copy1.o:	copy1.c copy1.h
	$(CC) $(CFLAGS) -c $^

copy2:	copy2.o
	$(CC) $(LDFLAGS) -o $@ $^

copy2.o:	copy2.c copy2.h
	$(CC) $(CFLAGS) -c $^

copy6:	copy6.o
	$(CC) $(LDFLAGS) -o $@ $^

copy6.o:	copy6.c copy6.h
	$(CC) $(CFLAGS) -c $^


.PHONY:	clean

clean:
	rm -rf core* *.o *.gch $(ALL)

