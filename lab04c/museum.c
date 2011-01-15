#include "museum.h"


int main(int argc, char* argv[]){
   FILE * pFile;
   pFile = fopen ("boxes.rec","r+");
   int boxNumber = 0;
   int valueCheck = 0;
   char stringValue[100];
   char readValue[100];
   
   if (pFile!=NULL){
      while(1){
         printf("Please Enter a Positive Integer: ");
         valueCheck = scanf ("%d",&boxNumber);
         if(valueCheck == 0){
            printf("That's not an integer, exiting\n");
            fclose (pFile);
            return EXIT_FAILURE;
         }
         if(boxNumber < 0){
            printf("That's a negative integer, exiting\n");
            fclose (pFile);
            return EXIT_FAILURE;
         }
         fseek (pFile,boxNumber*100,SEEK_SET);
         fgets (readValue , 100 , pFile);
         printf("Current String: %s\n",readValue);
         printf("please enter a new string: ");
         scanf ("%s",stringValue);
         fseek (pFile,boxNumber*100,SEEK_SET);
         fputs (stringValue,pFile);
      }
      
      fclose (pFile);
   }
   
   return EXIT_SUCCESS;
}

