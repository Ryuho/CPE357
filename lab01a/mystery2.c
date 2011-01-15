/* Ryuho Kudo
 * lab1a */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

void
mystery2(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;

}

int
main(int argc, char *argv[])
{
	int x = 4, y = 2;

	printf("x = %d, y = %d\n\n",x,y);
	mystery2(&x,&y);
	printf("x = %d, y = %d\n\n",x,y);

	return EXIT_SUCCESS;
}

