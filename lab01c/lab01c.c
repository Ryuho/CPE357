/**
*  CPE 357 Winter 2008
*  -------------------
*  Program that accepts a string and print the string backwards.
*
*  @author Ryuho Kudo
*/

#include <stdio.h>
#include <stdlib.h>
#include "lab01c.h"



int main(int argc, char *argv[]){
   int input_char;
   int notDone = 1;
   chain_t *temp;
   
   do{
      //allocattes
      chain_t *first = (chain_t*)malloc(sizeof(chain_t));
      first->pointerToChain = NULL;
      first->theLetter = '\0';
      while((input_char = getc(stdin)) != '\n' && input_char  != EOF){ 
         first->theLetter = input_char;
         chain_t *last = (chain_t*)malloc(sizeof(chain_t));
         last->pointerToChain = first;
         last->theLetter = '\0';
         first = last;
      }
      if(input_char == EOF){
         notDone = 0;
         while(first != NULL){
            temp = first->pointerToChain;
            free(first);
            first = temp;
         }
      }
      else{
         while(first != NULL){
            printf("%c",first->theLetter);
            temp = first->pointerToChain;
            free(first);
            first = temp;
         }
      }
      printf("\n");
   } while (notDone);
   printf("Bye-bye\n");
   return 0;
}

