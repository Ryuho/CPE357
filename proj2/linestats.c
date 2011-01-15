 /**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 * The main function reports the number of lines read 
 * and the length of the longest line that was seen.
 * </pre>
 * @author Ryuho Kudo
 */

#include "linestats.h"

/** The main thing.   This function reads strings from the
 * standard input or a file specified by the first argument.
 * It then counts the numbers of lines the input had, and
 * what was the length of the longest line.
 * @param argc the number of tokens on the input line.
 * @param argv an array of tokens.
 * @return 0 on success, 1-255 on failure
 */
 
int main(int argc, char *argv[]){
   FILE * infile = NULL;
   int lines = 0;
   int length = 0;
   int maxline = -1;
   char static * theLine = NULL;

   if (argc == 1) {
      infile = stdin;
   }
   else if (argc == 2) {
      infile = fopen(argv[1], "r");
      if (!infile) {
         perror(argv[1]);
         return EXIT_FAILURE;
      }
   }
   else{
      fprintf(stderr, "Usage: %s [inputfile]\n", argv[0]);
      return EXIT_FAILURE;
   }

   while (1) {
      theLine = getLine(infile);
      if(theLine == NULL){
         break;
      }
      
      lines++;
      length = strlen(theLine);
      if (length > maxline) {
         maxline = length;
      }
      free(theLine);
   }

   if (ferror(infile)) {
      perror("infile error");
      fprintf(stderr, "%d lines seen\n", lines);
      return EXIT_FAILURE;
   }

   printf("Number of lines read: %d\n", lines);
   if (lines) {
      printf("Length of the longest line that was seen: %d\n", maxline);
   }

   return EXIT_SUCCESS;
}

