 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 *
 * Program that reimplements unexpand with out 
 * the --tab=LIST and --version commands</pre>
 * @author Ryuho Kudo
 */
 
#include "myunexpand.h"

/** The main thing.  This function reads strings from the
 * standard input, and parses all the options and filenames.
 * It then executes the helper function to unexpand.
 * @param argc the number of tokens on the input line.
 * @param argv an array of tokens.
 * @return 0 on success, 1-255 on failure
 */

int main(int argc, char* argv[]){
   int numberOfArg = 1;
   int positionOfArg = 0;
   char *fileNames[MAXSTRINGNUMBER];
   int currentFileNameNum = 0;
   char junk[MAXSTRINGNUMBER];

   //have tabs N characters apart in stead of 8
   int tabNumber = 8;
   //the all flag
   int allFlag = 0;
   //the first only flag
   int firstOnly = 0;
   
   
   //Starting to read the arguments
   //Looping in the argv[] level of loop until i run out of args to read in
   for(;argv[numberOfArg] != '\0'; numberOfArg++){
      //set an int to zero so you can keep track of which part you are parsing
      positionOfArg = 0;
      
      //for checking comma to give out error
      for(int k = 0; k != strlen(argv[numberOfArg]); k++){
         if(argv[numberOfArg][k] == ','){
            printf("myunexpand: list is not supported\n");
            return EXIT_FAILURE;
         }
      }
      if(strcmp(argv[numberOfArg],"-") == 0){
         fileNames[currentFileNameNum] = (char*)malloc(MAXSTRINGNUMBER);
         strcpy (fileNames[currentFileNameNum],argv[numberOfArg]);
         currentFileNameNum++;
      }
      //means it's -a or --all, valid option
      else if((strcmp(argv[numberOfArg],"--all") == 0) ||
         strcmp(argv[numberOfArg],"-a") == 0){
         allFlag = 1;
      }
      //means it's --first-only, valid option
      else if(strcmp(argv[numberOfArg],"--first-only") == 0){
         firstOnly = 1;
      }
      //means it's --help, valid option
      else if(strcmp(argv[numberOfArg],"--help") == 0){
         printhelp();
         return EXIT_SUCCESS;
      }
      //means it's -t, valid option
      else if((strcmp(argv[numberOfArg],"-t") == 0)){
         numberOfArg++;
         //checks if -t is the last argv given
         if(argc <= numberOfArg){
            printf("myunexpand: option requires an argument -- 't'\n");
            printf("Try `myunexpand --help' for more information.\n");
            return EXIT_FAILURE;
         }
         //checks to see if it's a digit reads it or quits
         if(sscanf(argv[numberOfArg],"%d%s",&tabNumber,junk) == 2){
            printf("myunexpand: tab size contains invalid character(s): `%s'\n",
               argv[numberOfArg]);
            return EXIT_FAILURE;
         }
         else{
            allFlag = 1;
         }
      }
      //means it's -t%d, valid option
      else if(sscanf(argv[numberOfArg],"-t%d%s",&tabNumber,junk) == 1){
         allFlag = 1;
      }
      //means it's -tabs=%d, valid option
      else if(sscanf(argv[numberOfArg],"--tab=%d%s",&tabNumber,junk) == 1){
         allFlag = 1;
      }

      //this means that it is an invalid options
      else if (argv[numberOfArg][0] == '-') {
         printf("myunexpand: invalid option '%s'\n",
                 argv[numberOfArg]);
         printf("Try `myunexpand --help' for more information.\n");
         return EXIT_FAILURE;
      }
      //this is a filename for sure
      else {
         fileNames[currentFileNameNum] = (char*)malloc(strlen(argv[numberOfArg]));
         strcpy (fileNames[currentFileNameNum],argv[numberOfArg]);
         currentFileNameNum++;
      }
   }
   //report error for tabnumber being 0
   if(tabNumber == 0){
      printf("myunexpand: tab size cannot be 0\n");
      return EXIT_FAILURE;
   }
   if(tabNumber < 0){
      printf("myunexpand: tab size contains invalid character(s): `%d'\n",tabNumber);
      return EXIT_FAILURE;
   }


   tabUnexpand(fileNames,currentFileNameNum,tabNumber,allFlag,firstOnly);

   return EXIT_SUCCESS;
}

/**
 * This is called by the main function. It opens files according to the file
 * list, if there are none, stdin is automatically opened.
 *
 * @param fileName A pointer to the head of the file names.
 * @param totalFileNameNum Number of files that's being passed
 * @param tabNum The specified tab stop specification.
 * @param allFlag Used to find out if the -a flag is set, 1 is true and 0 is false
 * @param firstOnly Used to find out if the --first-only flag is set, 1 is true and 0 is false
 */

void tabUnexpand(char* fileName[], int totalFileNameNum, int tabNum, int allFlag, int firstOnly) {
   int currentFileNameNum = 0;
   FILE *istream;
   
   //read in the file
   for(; currentFileNameNum != totalFileNameNum; currentFileNameNum++) {
      // '-' so
      if(strcmp(fileName[currentFileNameNum],"-") == 0){
         tabUnexpandEcho(tabNum, allFlag, firstOnly,stdin);
      }
      else{
         // actual filenames
         if ( (istream = fopen (fileName[currentFileNameNum], "r" ) ) == NULL ) {
            printf ( "myexpand: %s: No such file or directory\n",
            fileName[currentFileNameNum]);
         } else {
            tabUnexpandEcho(tabNum, allFlag, firstOnly,istream);
            fclose ( istream );
         }
      }
   }
   if(totalFileNameNum == 0){
      tabUnexpandEcho(tabNum, allFlag, firstOnly,stdin);
   }
}


/**
 * This is called by the tabUnexpand function. It accepts file streams
 * and actually parses the characters to do the unexpand function.
 *
 * @param tabNum The specified tab stop specification.
 * @param allFlag Used to find out if the -a flag is set, 1 is true and 0 is false
 * @param firstOnly Used to find out if the --first-only flag is set, 1 is true and 0 is false
 * @param istream A file struct used to get stream of char from.
 */

void tabUnexpandEcho(int tabNum, int allFlag, int firstOnly, FILE* istream) {
	int temp;
   int tabMe = 1;
   int tabPosition = 0;
   int spaceCount = 0;
   int allTabFlag = allFlag;
   if(firstOnly == 1){
      allTabFlag = 0;
   }
   


	while(1){
      //reads a char
      temp=getc(istream);
      if(temp == ASCIINEWLINE){
            tabPosition = 0;
      }
      //breaks if it is EOF
      if(temp == EOF){
         break;
      }
      
      //no space before
      if(spaceCount == 0){
         if(temp == ASCIINEWLINE){
            putc(temp,stdout);
            tabPosition = 0;
            tabMe = 1;
            //printf("[TP=%d/SC=%d]\n",tabPosition,spaceCount);
         }
         else if(temp == ASCIISPACE){
            spaceCount++;
            tabPosition++;
            //printf("[TP=%d/SC=%d]\n",tabPosition,spaceCount);
         }
         else{
            putc(temp,stdout);
            tabPosition++;
            //printf("[TP=%d/SC=%d]\n",tabPosition,spaceCount);
            if(allTabFlag == 0){
               tabMe = 0;
            }
         }
      }
      //space before
      else{
         if(temp == ASCIINEWLINE){
            for(int i = 0; i != spaceCount; i++){
               putc(ASCIISPACE,stdout);
            }
            putc(temp,stdout);
            tabPosition = 0;
            spaceCount = 0;
            tabMe = 1;
            //printf("[TP=%d/SC=%d]\n",tabPosition,spaceCount);
         }
         else if(temp == ASCIISPACE){
            spaceCount++;
            tabPosition++;
            //printf("[TP=%d/SC=%d]\n",tabPosition,spaceCount);
         }
         else{
            for(int i = 0; i != spaceCount; i++){
               putc(ASCIISPACE,stdout);
               //printf("[TP=%d/SC=%d]\n",tabPosition,spaceCount);
            }
            putc(temp,stdout);
            tabPosition++;
            spaceCount = 0;
            //printf("[TP=%d/SC=%d]\n",tabPosition,spaceCount);
            if(allTabFlag == 0){
               tabMe = 0;
            }
         }
      }
      
      //if tabPosition is at a place where tab should be
      if(tabPosition == tabNum){
         //if there is a space before
         if(spaceCount > 1){
            if(tabMe == 1){
               putc(ASCIITAB,stdout);
               tabPosition = 0;
               spaceCount = 0;
               //printf("[TP=%d/SC=%d]\n",tabPosition,spaceCount);
            }
            else{
               for(int i = 0; i != spaceCount; i++){
                  putc(ASCIISPACE,stdout);
                  //printf("[TP=%d/SC=%d]\n",tabPosition,spaceCount);
               }
               tabPosition = 0;
               spaceCount = 0;
            }
         }
         else if(spaceCount == 1){
            //printf("space only one");
            putc(ASCIISPACE,stdout);
            tabPosition = 0;
            spaceCount = 0;
         }
         //if not, just reset the tab position
         else{
            tabPosition = 0;
            //printf("[TP=%d/SC=%d]\n",tabPosition,spaceCount);
         }
      }
         
   }
}


/**
 * Used for --help option. Just prints the help text
 */
void printhelp(){
   printf("Usage: unexpand [OPTION]... [FILE]...\n");
   printf("Convert blanks in each FILE to tabs, writing to standard output.\n");
   printf("With no FILE, or when FILE is -, read standard input.\n");
   printf("\n");
   printf("Mandatory arguments to long options are mandatory for short options too.\n");
   printf("  -a, --all        convert all blanks, instead of just initial blanks\n");
   printf("      --first-only  convert only leading sequences of blanks (overrides -a)\n");
   printf("  -t, --tabs=N     have tabs N characters apart instead of 8 (enables -a)\n");
   printf("      --help     display this help and exit\n");
   printf("\n");
   printf("Report bugs to <rkudo@calpoly.edu>.\n");
}



