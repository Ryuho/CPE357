/* Ryuho Kudo */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int 
main(int argc, char *argv[])
{
	int vals[] = {2,4,6,7,0,1,3,5,7,9};
	int i;

	for(i=0; i<10; i++){
		vals[i] = vals[vals[i]];
	}

	for(i=0; i<10; i++){
		printf("%d",vals[i]);
	}

	printf("\n");

	return EXIT_SUCCESS;
}

