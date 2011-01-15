 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 * Function to read arbitrarily-long lines.
 * </pre>
 * @author Ryuho Kudo
 */

#include "getLine.h"

/**
* Read an arbitrarily-long line from the given input stream.   Return
* NULL on end-of-file or error.   Otherwise, the return value is a
* pointer to static memory which is valid only until the next call
* to this function.
*
* Precondition: the input file ends with a newline, or is empty.
*
* @param infile an input stream.
* @return a pointer to a string read from the input, or NULL on error.
*/

char *
getLine(FILE * infile)
{
   static char *buf =NULL;
   static int len = 0;
   char *newbuf = NULL;
   int newlen = 0;
   int last = 0;
   char c = '\0'; //temp char variable

   if(len == 0){
      len = START_LEN;
   }

   buf = (char *)malloc(len);

   while ((c = fgetc(infile))) {
      if(c == EOF){
         return NULL;
      }
      if(c == '\n'){
         buf[last] = '\0';
         return buf;
      }
      
      buf[last] = c;
      last++;

      if((last == len)){
         newlen = len * 2;
         newbuf = (char *)realloc(buf, newlen);
         if (!newbuf) {
	         return NULL;
         }
         len = newlen;
         buf = newbuf;
      }
   }
   return NULL;
}

