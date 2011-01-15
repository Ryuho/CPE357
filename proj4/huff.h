 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 * A header for the huffman encoder and decoder
 * </pre>
 * @author Ryuho Kudo
 */

#ifndef HUFF_H_
#define HUFF_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/**the max binary number**/
#define BINARYCOMBO 256
/**the max buffersize**/
#define BUFFERSIZE 512
/**the max smaller buffer size**/
#define SMALLSIZE 32
/**tthe array size for bit arrays**/
#define TEN 10
/**how many bit in a byte**/
#define BYTE 8

//! boolean structure
typedef enum boolean { FALSE, TRUE } bool;


typedef struct bits{
   int total;
   int used;
   unsigned char* theBits;
}bits;

typedef struct bitTable{
   int size[BINARYCOMBO];
   int binaryTrans[BINARYCOMBO][TEN];
}bitTable;

typedef struct node{
   struct node* left;
   struct node* right;
   struct node* next;
   struct node* parent;
   int freq;
   unsigned char byte;
}node;

typedef struct completeFile{
   node* linkedList;
   int ar[BINARYCOMBO];
   bits* content;
}completeFile;

completeFile* encode(FILE* pFile);
node* attachNode(node* head, node* new);
bool findNode(node* head, int target);
node* createNodes(int* ar);
node* binaryTreeNode(node* head);
void freeNode(node* head);
node* stringToList(char* s);
bits* addBits(bits* target, int* binary, int size);
int findDepth(node* tree);
void playTree(node* tree);
bitTable* createTable(node* tree);
void printNode(node* tree);
completeFile* putBitTable(FILE* pFile,bitTable* tempTable,completeFile* answer);
void writeFile(completeFile* tempFile, char* argv);

#endif

