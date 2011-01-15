/**
 *   CPE 357 Fall 2008
 *   -------------------
 *   Program for lab 4a; this one uses read(2) and write(2) to
 *   copy the file with buffer size of 1024 bytes.
 *
 *   @author Ryuho Kudo
 */

#include "copy2.h"

int main(int argc, char *argv[]){
   char* ch = (char*)malloc(sizeof(char)*BUFFERSIZE);
   int r;
   int infd, outfd;

   /* Check the command line */
   if (argc != 3) {
      exit(EXIT_FAILURE);
   }

   /* Open files */
   infd = open(argv[1], O_RDONLY);
   if (infd == -1) {
      perror(argv[1]);
      exit(EXIT_FAILURE);
   }
   outfd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
   if (outfd == -1) {
      perror(argv[2]);
      exit(EXIT_FAILURE);
   }
   /* copy */
   while ((r = read(infd, ch, BUFFERSIZE)) > 0) {
      if ((r = write(outfd, ch, r)) == -1) {
         perror(argv[2]);
         exit(EXIT_FAILURE);
      }
   }
   
   if (r == -1) {
      perror(argv[1]);
      exit(EXIT_FAILURE);
   }

   /* close files */
   if (close(infd) == -1) {
      perror(argv[1]);
      exit(EXIT_FAILURE);
   }
   if (close(outfd) == -1) {
      perror(argv[2]);
      exit(EXIT_FAILURE);
   }
   return EXIT_SUCCESS;
}

