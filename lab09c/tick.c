/**
 * @file
 * <pre> CPE 357 Fall 2008
 * -------------------
 *
 * Program to illustrate embedded assembler code.
 *
 * Last Modified: Fri Nov 21 10:17:29 PST 2008</pre>
 * @author Kevin O'Gorman
 */



#include <stdio.h>

// Get timer value
#define WHEN ({unsigned long long int __when;			\
	asm volatile ( "rdtsc		    \n\t"		\
	    : "=A" (__when)	/* rdtsc output in edx,eax */	\
	    : /* no inputs */					\
	    ) ;							\
	__when; } )


int main(int argc, char *argv[]) {
    long long int CAL;

    CAL = WHEN - WHEN;
    fprintf(stderr,"Minimal timing %lld ticks\n",CAL);
    return 0;

}
/* vim: set et ai sts=2 sw=2: */// tick.c


