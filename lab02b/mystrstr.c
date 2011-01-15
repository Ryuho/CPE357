/**
 *  @file
 *  <pre>CPE 357
 *  -------------------
 *
 *  Program to find a substring given the string to look in and what to look for.
 *
 */
#include <unistd.h>

char* mystrstr(const char *haystack, const char *needle){
   //char* answer = NULL;
   int strlength = strlen(needle);
   int boolean;
   for (int i = 0; haystack[i]; i++) {
      boolean = 1;
      if (needle[0] == haystack[i]) {
         //printf("i hit at i = %d\n",i);
         for(int j = 0; j != strlength; j++){
            if(needle[j] != haystack[i+j]){
               boolean = 0;
               //printf("i broke at j= %d and i = %d \n",j,i);
               break;
            }
         }
         if(boolean == 1){
               //printf("i succeeded at i = %d \n",i);
               return (char *) & haystack[i];
         }
      }
   }
   return NULL;
}
