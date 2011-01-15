/**
 * @file
 *  <pre>CPE 357 Winter 2009
 *  -------------------
 *  This program is a string parser used for
 *  the next project. It won't be able to handle
 *  things that are lacking whitespace</pre>
 *  @author Ryuho Kudo
 */

#include "parseline.h"

/** The main thing.
 * @param argc count of command-line tokens.
 * @param argv array of command-line tokens.
 * @return 0 on success, 1-255 on failure.
 */
int main(int argc, char *argv[]){ 
   printf("line: ");
   //gets the actual command from keyboard
   
   char* commandLine = getLine(stdin);
   
   //in case EOF was set
   if(commandLine == NULL){
      fprintf(stderr,"EOF on stdin\n");
      return EXIT_FAILURE;
   }
   //in case blank was sent
   if(strcmp(commandLine,"") == 0){
      fprintf(stderr,"no data on stdin\n");
      return EXIT_FAILURE;
   }
   
   stageStruct** pStages = parseline(commandLine);
   
   printStages(pStages);
   
   int stageNum = pStages[0]->totalStageNumber;
   int argcNum = 0;
   for(int i = 0; i != stageNum; i++){
      argcNum = pStages[i]->argcc;
      free(pStages[i]->theCommand);
      if(pStages[i]->input != NULL){
         free(pStages[i]->input);
      }
      if(pStages[i]->output != NULL){
         free(pStages[i]->output);
      }
      for(int j = 0; j != argcNum; j++){
         free(pStages[i]->argvv[j]);
      }
      free(pStages[i]);
   }
   free(pStages);
   
   free(commandLine);
   return EXIT_SUCCESS;
}

stageStruct** parseline(char* s){
   pipeStruct* pPipe = parsePipe(s);
   stageStruct** pStages = parseStage(pPipe);
   for(int i = 0; i != pPipe->stageCount; i++){
      free(pPipe->commands[i]);
   }
   free(pPipe);
   return pStages;
}

/**
 * This is the function that prints everything at the end.
 * @param pStages this is the struct that has everything 
 * this function needs to print everything.
 */
void printStages(stageStruct** pStages){
   int totalStages = pStages[0]->totalStageNumber;
   for(int i = 0; i != totalStages; i++){
      printf("\n");
      printf("--------\n");
      printf("Stage %d: \"%s\"\n",i,pStages[i]->theCommand);
      printf("--------\n");
      
      //input printout
      printf("     input: ");
      if(pStages[i]->input == NULL){
         if(i == 0){
            printf("original stdin\n");
         }
         else{
            printf("pipe from stage %d\n",i-1);
         }
      }
      else{
         printf("%s\n",pStages[i]->input);
      }
      
      //output printout
      printf("    output: ");
      if(pStages[i]->output == NULL){
         if((totalStages - 1) == i){
            printf("original stdout\n");
         }
         else{
            printf("pipe to stage %d\n",i+1);
         }
      }
      else{
         printf("%s\n",pStages[i]->output);
      }
      printf("      argc: %d\n",pStages[i]->argcc);
      printf("      argv: ");
      for(int j = 0; j != pStages[i]->argcc; j++){
         printf("\"%s\"",pStages[i]->argvv[j]);
         if(j != pStages[i]->argcc-1){
            printf(",");
         }
            
      }
      printf("\n");
   }
}


/**
 * This is the function that parses a pipe structure, and turn it
 * into a stage struct.
 * @param pipes this is the struct that has everything 
 * this function needs to form a stage struct.
 */
stageStruct** parseStage(pipeStruct* pipes){
   stageStruct** answer = (stageStruct**)malloc(sizeof(stageStruct*)*pipes->stageCount);
   
   for(int i = 0; pipes->stageCount != i; i++){
      //testing for redirection related errors
      testInOut(pipes->commands[i], i, pipes->stageCount);
      
      //allocating the stage struct for this level
      answer[i] = (stageStruct*)malloc(sizeof(stageStruct));
      
      //setting the stage number
      answer[i]->stageNumber = i;
      answer[i]->totalStageNumber = pipes->stageCount;
      //setting the command string
      answer[i]->theCommand = strdup(pipes->commands[i]);
      
      //getting the number of white spaces
      //getting the argc, # of argv
      answer[i]->argcc = argcCounter(answer[i]->theCommand);
      
      //mallocing the argv
      answer[i]->argvv = (char**)malloc(answer[i]->argcc*(sizeof(char*)));
      int argvCount = 0;
      
      //setting it null
      answer[i]->input = NULL;
      answer[i]->output = NULL;
      
      //getting all of the argv, long because we have to avoid redirections
      //and their files
      int inArrowFound = 0;
      int outArrowFound = 0;
      char* tempCheck = strdup(answer[i]->theCommand);
      char* tempCheck2 = strtok(tempCheck," ");
      while(tempCheck2 != NULL){
         if(strcmp(tempCheck2,"<") == 0){
            inArrowFound = 1;
         }
         else if(strcmp(tempCheck2,">") == 0){
            outArrowFound = 1;
         }
         else if(inArrowFound){
            answer[i]->input = strdup(tempCheck2);
            answer[i]->argcc -= 2;
            inArrowFound = 0;
         }
         else if(outArrowFound){
            answer[i]->output = strdup(tempCheck2);
            answer[i]->argcc -= 2;
            outArrowFound = 0;
         }
         else{
            answer[i]->argvv[argvCount] = strdup(tempCheck2);
            argvCount++;
         }
         tempCheck2 = strtok(NULL," ");
      }
      free(tempCheck);
      free(tempCheck2);
   }
   return answer;
}

/**
 * This is the function that parses command input string, and turn it
 * into a pipe struct.
 * @param s this is the string that was given from the user.
 */
pipeStruct* parsePipe(char* s){
   if(strcmp(s,"|") == 0){
      fprintf(stderr,"Stage %d: invalid null command\n",0);
      exit(1);
   }
   if(s[0] == '|'){
      fprintf(stderr,"Stage %d: invalid null command\n",0);
      exit(1);
   }
      
   pipeStruct* answer = (pipeStruct*)malloc(sizeof(pipeStruct));
   answer->stageCount = charCounter(s,'|');
   answer->stageCount++;
   answer->commands = (char**)malloc(answer->stageCount*sizeof(char*));
   
   char* temp;

   temp = strtok(s,"|");
   
   //if blank pipe on first
   if(strcmp(temp," ") == 0){
      fprintf(stderr,"Stage %d: invalid null command\n",0);
      exit(1);
   }
   //if valid command on first
   else{
      answer->commands[0] = strdup(temp);
   }

   //while pipes exist
   for(int i = 1; i != answer->stageCount; i++ ){
      temp = strtok(NULL,"|"); 
      //stage 
      if(temp == NULL){
         fprintf(stderr,"Stage %d: invalid null command\n",i);
         exit(1);
      }
      //the stage is blank
      else if(strcmp(temp," ") == 0){
         fprintf(stderr,"Stage %d: invalid null command\n",i);
         exit(1);
      }
      else{
         //everything went fine and this is parsing
         answer->commands[i] = strdup(temp);
      }
   }
   return answer;
}

/**
 * This is a helper function that counts a specified character.
 * @param s this is the string that is going to be searched
 * @param c the char that is going to be looked for
 * @return int this is the number of chatacters specified that was detected
 */
int charCounter(char* s, char c){
   int answer = 0;
   int i;
   int resetMe = 0;
   for(i = 0; s[i] == c; i++){}

   for(; i != strlen(s); i++){
      if((s[i] == c)){
         if(resetMe == 0){
            answer++;
            resetMe = 1;
         }
      }
      else{
         resetMe = 0;
      }
   }
   return answer;
}

/**
 * This is a helper function that counts the number of args, this is
 * including <, > and the file name that follows those.
 * @param s this is the string that is going to be searched
 * @return int this is the number of args that the string has
 */
int argcCounter(char* s){
   int answer = 0;
   int i = 0;
   
   while(1){
      if(!isspace(s[i])){
         answer++;
         while(!isspace(s[i])){
            i++;
            if(i >= strlen(s)){break;}
         }
      }
      else{
         while(isspace(s[i])){
            i++;
            if(i >= strlen(s)){break;}
         }
         
      }
      if(i >= strlen(s)){break;}
   }
   return answer;
}

/**
* Read an arbitrarily-long line from the given input stream.   Return
* NULL on end-of-file or error.   Otherwise, the return value is a
* pointer to static memory which is valid only until the next call
* to this function.
*
* Precondition: the input file ends with a newline, or is empty.
*
* @param infile an input stream.
* @return a pointer to a string read from the input, or NULL on error.
*/
char *getLine(FILE * infile){
   static char *buf =NULL;
   static int len = 0;
   char *newbuf = NULL;
   int newlen = 0;
   int last = 0;
   char c = '\0';

   if(len == 0){
      len = START_LEN;
   }

   buf = (char *)malloc(len);

   while ((c = fgetc(infile))) {
      if(c == EOF){
         free(buf);
         return NULL;
      }
      if(c == '\n'){
         buf[last] = '\0';
         return buf;
      }
      
      buf[last] = c;
      last++;

      if((last == len)){
         newlen = len * 2;
         newbuf = (char *)realloc(buf, newlen);
         if (!newbuf) {
            return NULL;
         }
         len = newlen;
         buf = newbuf;
      }
   }
   free(buf);
   return NULL;
}

/**
* This function is based on the delimiter state machine like
* approach of finding errors in a command. I'm actually happy 
* that this worked. I worked on other way of doing the same thing
* and this took a lot less time, and cleanly worked.
*
* @param s the string that has the stage command
* @param stageNow the stage number that is currently
* @param totalStage the number of total stage
*/
void testInOut(char* s,int stageNow, int totalStage){
   int i = 0;
   error_e state = START;
   int in = 0;
   int out = 0;
   int command = 0;
   
   while(i != strlen(s)) {
      //printf("i=%d",i);
      switch (state) {
         case START:
            //printf("|start\n");
            if (s[i] == ' ') {
               state = BLANK;
            } else if (s[i] == '>') {
               state = OUTPUT;
            } else if (s[i] == '<') {  // begin character quote
               state = INPUT;
               
            } else {
               state = WORDS;  // everything else just gets copied
               command = 1;
            }
         break;

         case WORDS:
            //printf("|words\n");
            if (!isspace(s[i])) {        // start block comment
               
            }
            else{
               state = START;
            }
         break;

         case BLANK:
            //printf("|blank\n");
            if (s[i] == ' ') {
               state = BLANK;
            } else if (s[i] == '>') {
               state = OUTPUT;
            } else if (s[i] == '<') {  // begin character quote
               state = INPUT;
            } else {
               state = WORDS;  // everything else just gets copied
               command = 1;
            }
         break;

         case OUTPUT:
            if (s[i] == ' ') {        // start block comment
              
            }
            else if((stageNow == 0) && (totalStage != 1)){
               fprintf(stderr,"bad output redirection\n");
               exit(1);
            }else if((stageNow != 0) && (stageNow != totalStage-1)){
               fprintf(stderr,"bad output redirection\n");
               exit(1);
            }else if (s[i] == '>'){
               fprintf(stderr,"bad output redirection\n");
               exit(1);
            }else if (s[i] == '<'){
               fprintf(stderr,"bad output redirection\n");
               exit(1);
            }
            else if(out){
               fprintf(stderr,"bad output redirection\n");
               exit(1);
            }else{
               state = INOUTNAME;
               out = 1;
            }
         break;

         case INPUT:
            //printf("|input\n");
            if (s[i] == ' ') {        // start block comment
               
            }else if((stageNow != 0)){
               fprintf(stderr,"ambiguous input\n");
               exit(1);
            }else if((stageNow != 0) && (stageNow != totalStage-1)){
               fprintf(stderr,"bad input redirection\n");
               exit(1);
            }else if (s[i] == '>'){
               fprintf(stderr,"bad input redirection\n");
               exit(1);
            }else if (s[i] == '<'){
               fprintf(stderr,"bad input redirection\n");
               exit(1);
            }
            else if(in){
               fprintf(stderr,"bad input redirection\n");
               exit(1);
            }else{
               state = INOUTNAME;
               in = 1;
            }
         break;
         
         case INOUTNAME:
            //printf("|inoutname\n");
            if (!isspace(s[i])) {        // start block comment
               
            }
            else{
               state = START;
            }
         break;

         default:
            fprintf(stderr, "Never happen -- bad state\n\n");
            fflush(stderr);
            exit(1);
         break;
      }
      i++;
   }
   if(state == INPUT){
      fprintf(stderr,"bad input redirection\n");
      exit(1);
   }
   if(state == OUTPUT){
      fprintf(stderr,"bad output redirection\n");
      exit(1);
   }
   if(command == 0){
      fprintf(stderr,"Stage %d: invalid null command\n",stageNow);
      exit(1);
   }
}

