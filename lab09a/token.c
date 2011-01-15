/* Ryuho Kudo
 * lab9a
 * returns the next token seperated by delimiter char.
 * Also traverses the string given string.
 * part of a simple library
 */

#include "token.h"

char* token(char* theString,char delimiter){
	if(theString == NULL){
		return NULL;
	}
	//temp now gets a pointer to the first char occoured
	char* temp = strchr(theString,(int)delimiter);
	//null means there were no delimiters found
	if(temp == NULL){
		return theString;
	}
	//delimiters found... need to set restOfString to the new one
	//the length is (total string length - delimiter found)
	char* answer = (char*)malloc((strlen(theString)-strlen(temp)));
	memmove(answer,theString,(strlen(theString)-strlen(temp)));
	return answer;
}

