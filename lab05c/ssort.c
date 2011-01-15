/* Ryuho Kudo
 * CPE357 - lab7a (ssort)
 * The source code for ssort method.
 * It uses a quicksort algorythm and strcmp function to do the actual
 * compareing. It was made to do reverse lexical order. 
 */

#include "ssort.h"

int main(int argc, char* argv[]){
	char* listOfStrings[5000];
	if(argc == 1){
	   fileLess(listOfStrings);
	}
	else if(argc == 2) {
		myQsort(listOfStrings,argv[1]);
	}
	return EXIT_SUCCESS;
}

static int cmpstringp(const void *p1, const void *p2){
	return -(strcmp(* (char * const *) p1, * (char * const *) p2));
}


int fileLess(char* listOfStrings[]){
	char* tempString;
	int indexOfStrings = 0;
	FILE* istream = stdin;
   while((tempString = getLineFromFile(istream))) {
	   if(tempString == NULL){
			break;
		}
		listOfStrings[indexOfStrings] = tempString;
		indexOfStrings++;
		if(feof(istream) || ferror(istream)){
			break;
		}
	}
	qsort(listOfStrings, indexOfStrings, sizeof(char*), cmpstringp);

	for(int i = 0; i != indexOfStrings; i++){
		printf("%s",listOfStrings[i]);
	}
	for(int i = 0; i != indexOfStrings; i++){
		free(listOfStrings[i]);
	}	
	return EXIT_SUCCESS;
}

int myQsort(char* listOfStrings[],char* fileName){
	char* tempString;
	int indexOfStrings = 0;
	FILE* istream;
	if ((istream = fopen(fileName, "r")) != NULL) {
		while((tempString = getLineFromFile(istream))) {
			if(tempString == NULL){
				break;
			}
			listOfStrings[indexOfStrings] = tempString;
			indexOfStrings++;
			if(feof(istream) || ferror(istream)){
				break;
			}
		}
		qsort(listOfStrings, indexOfStrings, sizeof(char*), cmpstringp);

		for(int i = 0; i != indexOfStrings; i++){
			printf("%s",listOfStrings[i]);
		}
		for(int i = 0; i != indexOfStrings; i++){
			free(listOfStrings[i]);
		}
		fclose(istream);
		return EXIT_SUCCESS;
	}		
	else{
		fprintf(stderr,"ssort: %s: No such file or directory\n",fileName);
		return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}



char* stringResize(char* c){
	char* newString = (char*)malloc(strlen(c));
	for(int i = 0; i != strlen(c); i++){
		newString[i] = c[i];
	}
	free(c);
	return newString;
}
		
	

void removeNewLine(char* c){
	int i = 0;
	while(c[i] != '\n'){
		i++;
	
	}
	c[i] = '\0';
}



char* getLineFromFile(FILE * infile) {
	static int len = 0;
	char *newbuf;
	int newlen;
	int last = 0; // Initialized on every call
	if (len == 0) {
		len = START_LEN;
	}
	char *buf = (char *) malloc(len);

	while (buf[len - 1] = '?', fgets(buf + last, len - last, infile)) 
{
		if (buf[len - 1] == '?' || buf[len - 2] == '\n') {
			return buf;
		}
		last = len - 1;
		newlen = len * 2;
		newbuf = (char *) realloc(buf, newlen);
		if (!newbuf) {
			printf("ERROR: char* getLine(FILE * infile){");
			return NULL;
		}
		len = newlen;
		buf = newbuf;
	}
	free(buf);
	return NULL;
}

