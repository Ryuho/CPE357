 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 * An implementation of tail with restrictions.
 * This file has the main funtion as well as some helper functions.
 * </pre>
 * @author Ryuho Kudo
 */

#include "mytail.h"
#include "getLine.h"

/** The main thing. This mimics the tail(3) function with
 * only -n <number> and -f and <filename> argument enabled.
 * @param argc the number of tokens on the input line.
 * @param argv an array of tokens.
 * @return 0 on success, 1-255 on failure
 */

int main(int argc, char *argv[]){
   args answer;
   
   if(parseArg(argv,&answer) == 0){
      fprintf(stdout,"Bad Arguments\n"); 
      fflush(stdout);
      return EXIT_FAILURE;
   }
   
   if((answer.fileName == NULL) && answer.follow == 1){
      fprintf(stdout,"proj3: following standard \
input indefinitely is not allowed\n"); 
      fflush(stdout);
      return EXIT_FAILURE;
   }
   if(answer.fileName == NULL){
      stdinTail(answer.lineNumber); 
      return EXIT_SUCCESS;
   }
   
   //a file name is involved
   FILE * pFile = fopen (answer.fileName, "r" );
   
   if(pFile == NULL){
      fprintf(stdout,"proj3: cannot open `fdsa' for \
reading: No such file or directory\n"); 
      fflush(stdout);
      return EXIT_FAILURE;
   }
      
   //means you do follow the file
   if((answer.fileName != NULL) && (answer.follow != 0)){
      fileTail(pFile, answer.lineNumber,true);
   }
   //means you don't follow the file
   else if(answer.fileName != NULL){
      fileTail(pFile, answer.lineNumber,false);
   }
   fclose(pFile);

   return EXIT_SUCCESS;
}

/** This helper function parses the argv that is passed
 * to this program. It fills out the args* structure
 * to tell what kind of argument the argv had.
 * @param argv pointer to multiple arrays of char.
 * @param answer a struct used to return values to the caller.
 * @return 0 on failure, 1 on success
 */
 
int parseArg(char* argv[],args* answer){
   answer->fileName = NULL;
   answer->lineNumber = 10;
   answer->follow = 0;
   
   for(int numberOfArg = 1;argv[numberOfArg] != '\0'; numberOfArg++){
      
      //-f is detected and recorded on args structure
      if(strcmp(argv[numberOfArg],"-f") == 0){
         answer->follow = 1;
      }
      //means it's -n
      else if((strcmp(argv[numberOfArg],"-n") == 0)){
         numberOfArg++;
         //checks if -n is the last arg
         if(argv[numberOfArg] == '\0'){
            return 0;
         }
         //checks to see if it's a digit reads it or quits
         if(sscanf(argv[numberOfArg],"%d",&(answer->lineNumber)) != 1){
            return 0 ;
         }
      }
      //means it's a filename
      else{
         if(answer->fileName != NULL){
            return 0;
         }
         answer->fileName = argv[numberOfArg];
      }
      
   }
   return 1;
}

/** This function is called when a file is involved
 * as opposed to stdin (keyboard). It chooses weather 
 * or not to countinously follow the file based on the bool
 * that's provided by the param.
 * @param pFile the file to output the file and maybe follow.
 * @param lineNumber the number of lines of string to display.
 * @param follow a bool that decides if this function 
 *    follows after it displays the initial lines.
 */
 
void fileTail(FILE *pFile, int lineNumber, bool follow){
   int position = 0;
   int lineCount = 0;
   char ch = '\0';
   int lastLine = 0; 
   
   while(ch = fgetc(pFile), (ch != EOF)){
      if(ch == '\n'){
         lineCount++;
      }
   }
   
   fseek(pFile,0,SEEK_SET);
   
   lastLine = lineCount-lineNumber;
   
   if(lastLine < 0){
      while(ch = fgetc(pFile), (ch != EOF)){
         printf("%c",ch);
      }
      if(follow){
         activeTail(pFile);
      }
      return;
   }
   position = 0;
   
   while(ch = fgetc(pFile), (ch != EOF)){
      if(ch == '\n'){
         position++;
      }
      if(position == lastLine){
         while(ch = fgetc(pFile), (ch != EOF)){
            printf("%c",ch);
         }
         if(follow){
            activeTail(pFile);
         }
         return;
      }
   }
   if(follow){
      activeTail(pFile);
   }
   return;
}

/** This helper function is called by the fileTail function to
 * continously follow the file. It is in an infinite while loop
 * sleeping for a second per loop so that this will not eat up
 * cpu cycles.
 * @param pFile the file follow.
 */

void activeTail(FILE *pFile){
   fseek(pFile,0,SEEK_END);
   char ch = '\0';
   long curPos = ftell(pFile);
   while(1){
      fseek(pFile,0,SEEK_END);
      if(curPos != ftell(pFile)){
         fseek(pFile,curPos,SEEK_SET);
         while(ch = fgetc(pFile), (ch != EOF)){
            printf("%c",ch);
         }
         curPos = ftell(pFile);
      }
      sleep(1);
   }
   return;
}

/** This function is called when the stdin (keyboard) is involved
 * in the tail. It keeps track of the last N row of strings in the
 * buffer to output after the user inputs EOF.
 * @param lineNumber the number of lines of string to display.
 */

void stdinTail(int lineNumber){
   char** buffer = (char**)malloc(sizeof(char*)*lineNumber);
   
   for(int i = 0; i != lineNumber; i++){
      buffer[i] = NULL;
   }
   
   int curBuff = 0;
   int flag = 0;
   char* getBuffer;
   
   while(1){
      getBuffer = getLine(stdin);
      
      if(getBuffer == NULL){
         break;
      }
      
      if(buffer[curBuff] != NULL){
         free(buffer[curBuff]);
      }
      
      buffer[curBuff] = (char*)malloc(strlen(getBuffer)+1);
      
      strcpy(buffer[curBuff],getBuffer);
      free(getBuffer);

      curBuff++;
      
      if(curBuff == lineNumber){
         curBuff = 0;
         flag = 1;
      }
   }
   
   if(flag != 1){
      curBuff = 0;  
   }
   
   while(1){
      if(buffer[curBuff] == NULL){
         break;
      }
      printf("%s\n",buffer[curBuff]);
      
      free(buffer[curBuff]);
      buffer[curBuff] = NULL;
      
      curBuff++;
      if(curBuff == lineNumber){
         curBuff = 0;
      }
   }
   free(buffer);
}

