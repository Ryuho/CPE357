#  CPE 357 Fall 2008
#  Project 2
#  Author: Ryuho Kudo


CC=gcc
CFLAGS=-Wall -g -std=c99 -pedantic
LDFLAGS=


ALL= partOne partTwo partThree
	
	
all:  $(ALL)

partOne: partOne.o
	$(CC) $(LDFLAGS) -o $@ $^

partOne.o: partOne.c survey.h 
	$(CC) $(CFLAGS) -c $<
	
partTwo: partTwo.o
	$(CC) $(LDFLAGS) -o $@ $^

partTwo.o: partTwo.c survey.h 
	$(CC) $(CFLAGS) -c $<
	
partThree: partThree.o
	$(CC) $(LDFLAGS) -o $@ $^

partThree.o: partThree.c survey.h 
	$(CC) $(CFLAGS) -c $<



.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)
