 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 * An implementation of a huffman encoder
 * </pre>
 * @author Ryuho Kudo
 */

#include "huff.h"


/** The main thing. 
 * @param argc the number of tokens on the input line.
 * @param argv an array of tokens.
 * @return 0 on success, 1-255 on failure
 */
 
int main(int argc, char* argv[]){
   completeFile* tempFile;
   FILE * pFile = NULL;
   for(int i = 1; i != argc; i++){
      pFile = fopen (argv[i], "r" );
      if(pFile == NULL){
         fprintf(stdout,"huff-e: cannot open `%s' for reading: No such file or directory\n",argv[i]); 
         fflush(stdout);
         return EXIT_FAILURE;
      }
      tempFile = encode(pFile);
      writeFile(tempFile,argv[i]);
   }
   return EXIT_SUCCESS;
}

/** The main thing. 
 * @param tempFile the struct needed to write the file
 * @param original the original file name (this function adds .huff)
 */
 
void writeFile(completeFile* tempFile, char* original){
   char fileName[BINARYCOMBO];
   int i = 0;
   for(; i != strlen(original); i++){
      fileName[i] = original[i];
   }
   fileName[i] = '\0';
   strcat(fileName,".huff");
   
   //open the file to wrtie
   FILE* pFile = fopen(fileName,"w");
   if(pFile == NULL){
      fprintf(stdout,"huff-e: cannot open `%s' for writing\n",fileName); 
      fflush(stdout);
      exit(EXIT_FAILURE);
   }
   
   while(tempFile->linkedList != NULL){
      fprintf(pFile,"%d_%d!",tempFile->linkedList->byte,tempFile->linkedList->freq);
      tempFile->linkedList = tempFile->linkedList->next;
   }
   
   fprintf(pFile,"|");
   
   for(int i = 0; i != tempFile->content->used/BYTE; i++){
      fprintf(pFile,"%c",tempFile->content->theBits[i]);
   }
   
}

/** this is the main encoder function, calls all the helper function to gather all the
 * info needed to write a fiel
 * @param pFile the FILE 
 * @return returns a pointer to a completeFile that is filled out with information 
 * the program needs to write out an encoded file
 */
 
completeFile* encode(FILE* pFile){
   completeFile* answer = (completeFile*)malloc(sizeof(completeFile));
   answer->content = (bits*)malloc(sizeof(bits));
   answer->content->total = 0;
   answer->content->used = 0;
   for(int i = 0; i != BINARYCOMBO; i++){
      answer->ar[i] = 0;
   }
   char ch;
   while(1){
      ch = fgetc (pFile);
      if(ch == EOF){
         break;
      }
      answer->ar[(unsigned int)ch]++;
   }
   
   node* test = createNodes(answer->ar);
   node* theTree = createNodes(answer->ar);
   
   answer->linkedList = createNodes(answer->ar);
   
   theTree = binaryTreeNode(theTree);
   //playTree(theTree);
   while(test != NULL){
      printf("%d\t%d\n",test->byte,test->freq);
      test = test->next;
   }
   
   
   
   bitTable* tempTable = createTable(theTree);
   
   
   
   rewind(pFile);
   
   answer = putBitTable(pFile,tempTable,answer);
   
   return answer;
}

/** This function takes in a struct, and fills the bit information out
 * @param pFile the FILE object
 * @param tempTable the bit table needed to encode the string
 * @param answer the struct that is going to be filled out with bit information
 * @return returns a pointer to a completeFile that is filled out with information 
 * the program needs to write out an encoded file
 */
 
completeFile* putBitTable(FILE* pFile, bitTable* tempTable, completeFile* answer){
   char ch;
   while(1){
      ch = fgetc (pFile);
      if(ch == EOF){
         break;
      }
      fprintf(stdout,"|%d|",(unsigned int)ch);fflush(stdout);
      addBits(answer->content,tempTable->binaryTrans[(unsigned int)ch],tempTable->size[(unsigned int)ch]);      
   }
   return answer;
}

/** This function takes in a binary in the form of int arrays and actually writes
 * them into actual bits
 * @param target the struct that holds the actual bits
 * @param binary the fake binary in the form of int arrays
 * @param size the size of the fake binary int array
 * @return returns a pointer to a bits structure that is filled out with information
 * the program needs to write out the bit portion of the file
 */
 
bits* addBits(bits* target, int* binary, int size){   
   int section = 0;
   int subSection = 0;
   int value = 0;
   target->theBits = (unsigned char*)malloc(SMALLSIZE);
   for(int i = 0; i != size; i++){
      if((target->total-target->used) <= size){
         target->theBits = (unsigned char*)realloc(target->theBits,sizeof(target->theBits)+SMALLSIZE);
         target->total = sizeof(target->theBits);
      }
      section = target->used/BYTE;
      subSection = target->used - section*BYTE;
      //bit is 1
      if(binary[i] == 1){
         if(subSection == 0){ value = 128; }
         else if(subSection == 1){ value = 64; }
         else if(subSection == 2){ value = 32; }
         else if(subSection == 3){ value = 16; }
         else if(subSection == 4){ value = 8; }
         else if(subSection == 5){ value = 4; }
         else if(subSection == 6){ value = 2; }
         else if(subSection == 7){ value = 1; }
         target->theBits[section] = target->theBits[section] | value;
      }
      //bit is 0
      else{
         if(subSection == 0){ value = 127; }
         else if(subSection == 1){ value = 191; }
         else if(subSection == 2){ value = 223; }
         else if(subSection == 3){ value = 239; }
         else if(subSection == 4){ value = 247; }
         else if(subSection == 5){ value = 251; }
         else if(subSection == 6){ value = 253; }
         else if(subSection == 7){ value = 254; }
         target->theBits[section] = target->theBits[section] & value;
      }
      target->used++;
   }
   return target;
}

/** This function takes in a tree and produces a bit table that shows
 * how a letter be shown in bits
 * @param tree the tree that is going to be traversed
 * @return returns a pointer to a bitTable that holds all the lookup table
 * to 
 */
 
bitTable* createTable(node* tree){
   bitTable* answer = (bitTable*)malloc(sizeof(bitTable));
   for(int i = 0; i != BINARYCOMBO; i++){
      answer->size[i] = 0;
      for(int j = 0; j != TEN; j++){
         answer->binaryTrans[i][j] = 0;
      }
   }
   
   int tempAr[TEN];
   int tempArIndex = 0;
   node* temp = tree;
   printf("\n");
   while(1){
      if(temp->parent == NULL && temp->left == NULL && temp->right == NULL){
         //printf("bye");
         break;
      }
      while(temp->left != NULL){
         printf("left ");
         tempAr[tempArIndex] = 0;
         tempArIndex++;
         temp = temp->left;
      }
      while(temp->right != NULL){
         printf("right ");
         tempAr[tempArIndex] = 1;
         tempArIndex++;
         temp = temp->right;
      }
      printf("|\n");
      

      
      if(temp->left == NULL && temp->right == NULL && temp->parent != NULL){
         printf("caught one");
         printNode(temp);
         fprintf(stdout,"||size@=%d,tempArIndex=%d||",(unsigned int)temp->byte,tempArIndex);fflush(stdout);
         answer->size[(unsigned char)temp->byte] = tempArIndex;   
         printf("|");
         for(int i = 0; i != tempArIndex; i++){
            printf("%d ",tempAr[i]);
            answer->binaryTrans[(unsigned int)temp->byte][i] = tempAr[i];
         }
         printf("|");
         //now destroy that node
         if(temp->parent->left == temp){
            printf("1gone up");
            tempArIndex--;
            temp = temp->parent;
            temp->left = NULL;
            printNode(temp);
         }
         else if(temp->parent->right == temp){
            printf("1gone up");
            temp = temp->parent;
            tempArIndex--;
            temp->right = NULL;
            printNode(temp);
         }
         else{
            printf("something went wrong\n");fflush(stdout);
         }
         while(temp->left == NULL && temp->right == NULL && temp->byte == 255 && temp->parent != NULL){
            
            if(temp->parent->left == temp){
               printf("2gone up");
               tempArIndex--;
               temp = temp->parent;
               temp->left = NULL;
               printNode(temp);
            }
            else if(temp->parent->right == temp){
               fprintf(stdout,"2gone up");fflush(stdout);
               temp = temp->parent;
               tempArIndex--;
               temp->right = NULL;
               printNode(temp);
               
            }
         }
      }
   }
   return answer;
}



