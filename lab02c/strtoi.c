/**
 *  @file
 *  <pre>CPE 357
 *  -------------------
 *
 *  Has the function strtoi
 *
 */

#include "strtoi.h"

long int strtol(const char *nptr, char **endptr, int base){
   char* TP = (char*)nptr;
   long int answer = 0;
   int digit = 0;
   while(TP != (char*)endptr){
      if(isdigit(TP)){
         printf("detected a num!=%d\n",*TP);
      }
      TP++;
   }
   return answer;
}

