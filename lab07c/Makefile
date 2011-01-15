#  CPE 357 Winter 2009
#  lab07c
#  Author: Ryuho Kudo

CC=gcc
SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -std=c99 -pedantic -g  $(SUS3) $(HARDEN)
#LDFLAGS=

ALL = sleeper

all: $(ALL)

sleeper: sleeper.o
	$(CC) $(LDFLAGS) -o $@ $^

sleeper.o: sleeper.c sleeper.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o *.gch core* $(ALL)

