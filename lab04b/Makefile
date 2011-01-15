#  CPE 357 Fall 2008
#  Lab 4 b
#  Author: Ryuho Kudo


CC=gcc
CFLAGS=-Wall -g -std=c99 -pedantic
LDFLAGS=


ALL= make4mb bufferin1byte bufferin512byte bufferin1000byte bufferin8192byte
	
all:  $(ALL)


make4mb: make4mb.o
	$(CC) $(LDFLAGS) -o $@ $^

make4mb.o: make4mb.c
	$(CC) $(CFLAGS) -c $<


bufferin1byte: bufferin1byte.o
	$(CC) $(LDFLAGS) -o $@ $^

bufferin1byte.o: bufferin1byte.c
	$(CC) $(CFLAGS) -c $<


bufferin512byte: bufferin512byte.o
	$(CC) $(LDFLAGS) -o $@ $^

bufferin512byte.o: bufferin512byte.c 
	$(CC) $(CFLAGS) -c $<


bufferin1000byte: bufferin1000byte.o
	$(CC) $(LDFLAGS) -o $@ $^

bufferin1000byte.o: bufferin1000byte.c 
	$(CC) $(CFLAGS) -c $<


bufferin8192byte: bufferin8192byte.o
	$(CC) $(LDFLAGS) -o $@ $^

bufferin8192byte.o: bufferin8192byte.c 
	$(CC) $(CFLAGS) -c $<


.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)
