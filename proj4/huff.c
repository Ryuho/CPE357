 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 * A file with functions for both encoder and decoder
 * </pre>
 * @author Ryuho Kudo
 */

#include "huff.h"

/** This function takes in a struct, and fills the bit information out
 * @param pFile the FILE object
 * @param tempTable the bit table needed to encode the string
 * @param answer the struct that is going to be filled out with bit information
 * @return returns a pointer to a completeFile that is filled out with information 
 * the program needs to write out an encoded file
 */

node* createNodes(int* ar){
   node* head = NULL;
   //creates a single line of linked nodes decending in frequency
   for(int i = 0; i != BINARYCOMBO; i++){
      if(ar[i] != 0){
         node* temp = (node*)malloc(sizeof(node));
         temp->freq = ar[i];
         temp->byte = i;
         temp->left = NULL;
         temp->right = NULL;
         temp->parent = NULL;
         temp->next = NULL;
         head = attachNode(head,temp);
      }
   }
   return head;
}

/** This function takes in a struct, and fills the bit information out
 * @param head pointer for a node to the head
 * @param new pointer for a node to the one that's being added
 * @param answer the struct that is going to be filled out with bit information
 * @return returns a pointer to a node
 */
 
node* attachNode(node* head, node* new){
   if(head == NULL){
      return new;
   }
   //the new comes before the current head
   if(head->freq > new->freq){  
      new->next = head;
      return new;
   }
   //new needs to be added to an already existing head
   node* temp = head;
   while(1){
      //the line is at the end
      if(temp->next == NULL){
         break;
      }
      //new found a spot between the line
      if(temp->next->freq > new->freq){
         break;
      }
      temp = temp->next;
   }
   //the new node should be added at the end of / in between the list
   node* restOfList = temp->next;
   temp->next = new;
   new->next = restOfList;
   return head;
}

/** This function creates a binary tree out of a linked list
 * @param head pointer for a node to the head
 * @return returns a pointer to a node
 */
 
node* binaryTreeNode(node* head){
   node* answer = head;
   while(1){
      //only one node left in linked list
      if(answer->next == NULL){
         break;
      }
      node* temp = (node*)malloc(sizeof(node));
      temp->freq = (answer->freq + answer->next->freq);
      temp->byte = -1;
      temp->left = answer;
      temp->left->parent = temp;
      temp->right = answer->next;
      temp->right->parent = temp;
      temp->next = NULL;
      temp->parent = NULL;
      answer = answer->next->next;
      answer = attachNode(answer,temp);
   }
   return answer;
}

/** This function lets you traverse the tree created interactively
 * @param tree pointer for a node to the head
 * @return returns a pointer to a node
 */
 
void playTree(node* tree){
   char ch = '\0';
   char junk;
   while(1){
      if(tree == NULL){
         break;
      }
      fprintf(stdout,"|freq=%d,byte=%d|",tree->freq,tree->byte);
      if(tree->parent != NULL){
         fprintf(stdout,"|parent|freq=%d,byte=%d|",tree->parent->freq,tree->parent->byte);
      }
      else{
         fprintf(stdout,"|NO parent|");
      }
      if(tree->left != NULL){
         fprintf(stdout,"|left|freq=%d,byte=%d|",tree->left->freq,tree->left->byte);
      }
      else{
         fprintf(stdout,"|NO left|");
      }
      if(tree->right != NULL){
         fprintf(stdout,"|right|freq=%d,byte=%d|",tree->right->freq,tree->right->byte);
      }
      else{
         fprintf(stdout,"|NO right|");
      }
      fprintf(stdout,"\n");
      scanf("%c",&ch);
      scanf("%c",&junk);
      if(ch == 'p'){
         fprintf(stdout,"moving to parent");
         tree = tree->parent;
      }
      else if(ch == 'l'){
         fprintf(stdout,"moving to left");
         tree = tree->left;
      }
      else if(ch == 'r'){
         fprintf(stdout,"moving to right");
         tree = tree->right;
      }
      else{
         fprintf(stdout,"moving nowhere!");
      }
      
   }
}

/** This function lets you traverse the tree created interactively
 * @param tree pointer for a node to the head
 */
 
void printNode(node* tree){
      fprintf(stdout,"|freq=%d,byte=%d|",tree->freq,tree->byte);
      if(tree->parent != NULL){
         fprintf(stdout,"|parent|freq=%d,byte=%d|",tree->parent->freq,tree->parent->byte);
      }
      else{
         fprintf(stdout,"|NO parent|");
      }
      if(tree->left != NULL){
         fprintf(stdout,"|left|freq=%d,byte=%d|",tree->left->freq,tree->left->byte);
      }
      else{
         fprintf(stdout,"|NO left|");
      }
      if(tree->right != NULL){
         fprintf(stdout,"|right|freq=%d,byte=%d|",tree->right->freq,tree->right->byte);
      }
      else{
         fprintf(stdout,"|NO right|");
      }
      fprintf(stdout,"\n");
      fflush(stdout);
}



