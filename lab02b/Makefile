#  CPE 357 Winter 2009
#  Lab 2 Part b
#  Author: Ryuho Kudo

SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -g -std=c99 -pedantic  $(SUS3) $(HARDEN)
LDFLAGS=

ALL = strfind

all: $(ALL)

strfind: strfind.o
	$(CC) $(LDFLAGS) -o $@ $^

strfind.o: strfind.c strfind.h mystrstr.c mystrstr.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o *.gch core* $(ALL)

