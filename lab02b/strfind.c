/**
 *  @file
 *  <pre>CPE 357
 *  -------------------
 *
 *  Main program that takes in two strings at a time and finds 
 *  the substring specified.
 *
 */

#include "strfind.h"
#include "mystrstr.c"
#include <string.h>
#include <unistd.h>


int main(int argc, char* argv[]){
   char* sOne = (char*)malloc(MAXLEN);
   char* sTwo = (char*)malloc(MAXLEN);
   char* sAnswer = (char*)malloc(MAXLEN);
   char* checkNull = (char*)malloc(MAXLEN);
   
   while(1){
      printf("Enter a string: ");
      checkNull = fgets(sOne,MAXLEN,stdin);
      if(checkNull == NULL){
         printf("Bye.\n");
         return EXIT_SUCCESS;
      }
      
      sOne[strlen(sOne)-1] = '\0';
      
      printf("Enter a possible substring: ");
      checkNull = fgets(sTwo,MAXLEN,stdin);
      if(checkNull == NULL){
         printf("Bye.\n");
         return EXIT_SUCCESS;
      }
      
      sTwo[strlen(sTwo)-1] = '\0';
      
      sAnswer = mystrstr(sOne,sTwo);
      
      if(sAnswer == NULL){
         printf("No substring found.\n");
      }
      else{
         printf("The substring occurs at position %d\n",sAnswer-sOne);
      }
   }
   return 0;
}

