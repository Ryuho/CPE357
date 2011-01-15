#  CPE 357 Winter 2009
#  Lab 2 Part c
#  Author: Ryuho Kudo

SUS3=-D_POSIX_SOURCE -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600
HARDEN=-D_FORTIFY_SOURCE
CFLAGS=-Wall -g -std=c99 -pedantic  $(SUS3) $(HARDEN)
LDFLAGS=

ALL = lab02c

all: $(ALL)

lab02c: lab02c.o
	$(CC) $(LDFLAGS) -o $@ $^

lab02c.o: lab02c.c strtoi.h strtoi.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o *.gch core* $(ALL)

