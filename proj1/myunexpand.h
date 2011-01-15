 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 *
 * Includes the main function as well as tab conversion.</pre>
 * @author Ryuho Kudo
 */


#ifndef MYUNEXPAND_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEFAULTTAB 8
#define MAXSTRINGNUMBER 256
#define ASCIISPACE 32
#define ASCIINEWLINE 10
#define ASCIITAB 9

void tabUnexpandEcho(int tabNum, int allFlag, int firstOnly,FILE* istream);
void printhelp();
void tabUnexpand(char* fileName[], int tabNum, int totalFileNameNum, int allFlag, int firstOnly);

#endif /*MYUNEXPAND_H_*/

