

#ifndef GETLINE_H
#define GETLINE_H

/** Local define for the starting buffer size */
#define START_LEN 256


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>


char * getLine(FILE * infile);
#endif

