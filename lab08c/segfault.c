/* Ryuho Kudo
 * lab8b
 * segfault - mallocs until it runs out of space
 */

#include <stdio.h>
#include <stdlib.h>

#define MALLOCSIZE 65536

int main(void){
	int mallocCount = 0;
	char* foo;
	while(foo = (char*)malloc(MALLOCSIZE), foo != NULL){
		mallocCount++;
	}
	printf("Exiting with %d x 64KB malloced\n",mallocCount);
	return 0;
}
