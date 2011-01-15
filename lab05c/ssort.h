/* Ryuho Kudo
 * CPE357 - lab7a 
 * Header for the main .c file
 */

#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define START_LEN 512
#define STRAR 5000

char* getLineFromFile(FILE * infile);
void removeNewLine(char* c);
char* stringResize(char* c);
static int cmpstringp(const void *p1, const void *p2);
int myQsort(char* listOfStrings[],char* fileName);
int fileLess(char* listOfStrings[]);
