#Ryuho Kudo
#lab9a 

AR = ar
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

ALL = tick ctimer

all: $(ALL)

tick.o: tick.c
	$(CC) $(CFLAGS) -c $<

tick: tick.o
	$(CC) $(LDFLAGS) -o $@ $^

ctimer.o: ctimer.c
	$(CC) $(CFLAGS) -c $<

ctimer: ctimer.o
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY:	clean

clean:
	rm -rf core* sc* posixlist_* cslist_* *.o *.gch $(ALL)
