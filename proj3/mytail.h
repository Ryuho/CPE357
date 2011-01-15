 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 * Header for the main function.
 * </pre>
 * @author Ryuho Kudo
 */
 
#ifndef MYTAIL_H_
#define MYTAIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
   
struct arguments{
   char* fileName;
   int lineNumber;
   int follow;
};

typedef struct arguments args;

typedef int bool;
enum { false, true };


int parseArg(char* argv[],args* answer);
void fileTail(FILE *pFile, int lineNumber, bool follow);
void stdinTail(int lineNumber);
void printEnd(FILE *pFile, long position);
void activeTail(FILE *pFile);

#define BUFFSIZE 1024

#endif

