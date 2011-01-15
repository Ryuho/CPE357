/* Ryuho Kudo
 * lab9a strtok
 * program that mimics linux command strtok
 */

#include "strtok.h"

int main(int argc, char* argv[]){
	char* theString;
	char* theDelimiter;
	char* nextToken;
	int index = 1;
	while(1){
		printf("Enter a string: ");
		theString = getLine(stdin);
		if((theString == NULL) || (theString[0] == '\n')){
			break;
		}
		printf("Enter your delimiter: ");
		theDelimiter = getLine(stdin);
		if((theString == NULL) || (theDelimiter[0] == '\n')){
			break;
		}
		while(1){
			nextToken = token(theString,theDelimiter[0]);
			if((strlen(nextToken)-strlen(theString)) == 0){
				nextToken[strlen(nextToken)-1] = '\0';
				printf("%d: \"%s\"\n",index,nextToken);
				break;
			}
			if(strlen(nextToken) != 0){
				printf("%d: \"%s\"\n",index,nextToken);
				index++;
			}
			memmove(theString,theString+strlen(nextToken)+1,
				(strlen(theString)-strlen(nextToken)));
		};
		printf("\n");
		index = 1;
	}
	printf("\nBye-bye.\n");
	return EXIT_SUCCESS;
}

