 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 * Header file for getLine.h
 * </pre>
 * @author Ryuho Kudo
 */

#ifndef GETLINE_H_
#define GETLINE_H_

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

