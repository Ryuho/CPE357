 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 * An implementation of a huffman decoder
 * </pre>
 * @author Ryuho Kudo
 */

#include "huff.h"

int decode(char* fileName);
void printChars(unsigned char* chAr,node* tree);

int main(int argc, char* argv[]){
   if(argc > 2){
      fprintf(stdout,"huff-d: too many arguments\n");
      fflush(stdout);
      return EXIT_FAILURE;
   }
   if(argc == 1){
      fprintf(stdout,"huff-d: filter Mode\n");
      fflush(stdout);
      return EXIT_FAILURE;
   }
   if(argc == 2){
      fprintf(stdout,"huff-d: file Mode\n");
      decode(argv[1]);
   }
   return EXIT_SUCCESS;
}

int decode(char* fileName){
   if(strstr(fileName,".huff") == NULL){
      fprintf(stdout,"huff-d: the file `%s' does not end in .huff\n",fileName); 
      fflush(stdout);
      exit(EXIT_FAILURE);
   }
   FILE * pFile = NULL;
   pFile = fopen (fileName, "r" );
   if(pFile == NULL){
      fprintf(stdout,"huff-d: cannot open `%s' for reading: No such file or directory\n",fileName); 
      fflush(stdout);
      exit(EXIT_FAILURE);
   }
   
   int ar[BINARYCOMBO];
   for(int i = 0; i != BINARYCOMBO; i++){
      ar[i] = 0;
   }
   int temp1,temp2;
   while(1){
      if(fscanf(pFile,"%d_%d!",&temp1,&temp2) == 2){
         ar[temp1] = temp2;
      }
      else{
         break;
      }      
   }
   while(fgetc(pFile) != '|'){
   }
   
   node* test = createNodes(ar);
   node* tree = binaryTreeNode(test);
   
   while(test != NULL){
      printf("%d\t%d\n",test->byte,test->freq);
      test = test->next;
   }
   
   unsigned char* chAr = (unsigned char*)malloc(sizeof(unsigned char)*BINARYCOMBO);
   unsigned char ch;
   //bits* bitField = (bits*)malloc(sizeof(bits));
   int index = 0;
   while(1){
      ch = fgetc(pFile);
      if(feof(pFile)){
         break;
      }
      //printf(ch);
      chAr[index] = ch;
      index++;
   }
   
   printChars(chAr,tree);
   
   return 0;
}

void printChars(unsigned char* chAr,node* tree){
   
}



