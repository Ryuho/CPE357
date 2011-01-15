#Ryuho Kudo
#lab9a 

AR = ar
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g -I ./
LDFLAGS = -lm -L ./
LIBS = -l357

ALL = lib357.a strtok 

all: $(ALL)

getLine.o:	getLine.c getLine.h
	$(CC) $(CFLAGS) -c $<

token.o:	token.c token.h
	$(CC) $(CFLAGS) -c $<

lib357.a:	getLine.o token.o
	$(AR) cru $@ $^

strtok.o: strtok.c strtok.h getLine.h token.h
	$(CC) $(CFLAGS) -c $<

strtok: strtok.o lib357.a
	$(CC) $(LDFLAGS) $< -o $@ $(LIBS)

.PHONY:	clean

clean:
	rm -rf core* sc* posixlist_* cslist_* *.o *.gch $(ALL)
