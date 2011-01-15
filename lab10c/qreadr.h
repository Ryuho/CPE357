/* Ryuho Kudo
 * lab10b
 * qreadr.c
 */


#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199506L
#define _XOPEN_SOURCE 600

#define START_LEN 1024
#define MAX_MSG_LEN     10000



#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>
#include <mqueue.h>

#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

char* getline(FILE * infile);
