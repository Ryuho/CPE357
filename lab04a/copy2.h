/**
 *  CPE 357 Fall 2008
 *  -------------------
 *  Header for:
 *  Program for lab 4a; this one uses read(2) and write(2) to
 *  copy the file with buffer size of 1024 bytes.
 *
 *  @author Ryuho Kudo
 */

#ifndef COPY2_H
#define COPY2_H

//#define _POSIX_SOURCE
//#define _POSIX_C_SOURCE 199506L
//#define _XOPEN_SOURCE 600

#define BUFFERSIZE 1024

#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#endif
