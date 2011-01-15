/**
 *  @file
 *  <pre>CPE 357
 *  -------------------
 *
 *  Header for strtoi.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#define MAXLEN 255

long int strtol(const char *nptr, char **endptr, int base);
