/**
 * @file
 *  <pre>CPE 357 Winter 2009
 *  -------------------
 *  This is the header for parseline.c</pre>
 *  @author Ryuho Kudo
 */

#ifndef PARSELINE_H_
#define PARSELINE_H_


///max number of temp string
#define MAXTEMPSTRING 100

///starting length of string for getLine function
#define START_LEN 256


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

///enum used for the state machine style function
typedef enum {START,BLANK,WORDS,INPUT,OUTPUT,INOUTNAME} error_e;

///struct used for breaking the input into pipes
typedef struct {
   ///the number of stages this struct has
   int stageCount;
   ///array of strings, which are the commands broken by pipe symbol
   char** commands;
}pipeStruct;

///struct used for breaking pipes into actual stages
typedef struct {
   ///array of strings, which are the commands broken by pipe symbol
   int totalStageNumber;
   ///the current stage number
   int stageNumber;
   ///the current stage number
   char* theCommand;
   ///the string for input, if NULL then it's default
   char* input;
   ///the string for output, if NULL then it's default
   char* output;
   ///int that's holding how many arguments there are
   int argcc;
   ///array of string, the array's length is argc
   char** argvv;
}stageStruct;

void freeStage(stageStruct** pStages,pipeStruct* pPipe);
stageStruct** parseline(char* s);
int charCounter(char* s, char c);
pipeStruct* parsePipe(char* s);
stageStruct** parseStage(pipeStruct* pipes);
char * getLine(FILE * infile);
void testInOut(char* s,int stageNow, int totalStage);
void printStages(stageStruct** pStages);
int argcCounter(char* s);

#endif
