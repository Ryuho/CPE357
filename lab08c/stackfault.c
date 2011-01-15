/* Ryuho Kudo
 * lab8b
 * stackfault - calls it's self until it runs out of stack
 */

#include <stdio.h>
#include <stdlib.h>

#define MALLOCSIZE 65536

void recursiveFunction(int i){
	int static callCount = 0; // only set to 0 once
	callCount++;
	printf("%d\n",i);
	recursiveFunction(i+1);
}

int main(void){
	recursiveFunction(0);
	return 0;
}


