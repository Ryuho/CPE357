/**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 *
 * Source file for Lab 1 B.
 *
 */
 
#include <sys/types.h>
#include <unistd.h>
#include "lab01b.h"

char *mystrchr(char *s, char c){
   for (int i = 0; s[i]; i++){
      if (c == s[i]){
         return (&s[i]);
      }
   }
   return NULL;
}

int intindex(int target, int intp[], int size){
   int *max = &intp[0] + size;
   int *current = intp;

   while (current < max){
      if (target == *current){
         return current - intp;
      }
      current++;
   }
   return -1;
}

