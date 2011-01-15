/**
 *  @file
 *  <pre>CPE 357
 *  -------------------
 *
 *  The driver for this lab
 *
 */


#include "strtoi.h"
#include "strtoi.c"

int main(int argc, char* argv[]){
   char* checkNull = (char*)malloc(MAXLEN);
   char* sOne = (char*)malloc(MAXLEN);
   while(1){
      checkNull = fgets(sOne,MAXLEN,stdin);
      if(checkNull == NULL){
         printf("Bye.\n");
         return 0;
      }
      else{
         strtol("%s",sOne);
      }
      
      //sOne[strlen(sOne)-1] = '\0';
      
   }
   return 0;
}

