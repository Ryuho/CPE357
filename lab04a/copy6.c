/**
 *  CPE 357 Winter 2009
 *  -------------------
 *  Program for lab 4a; this one uses fgetc(3) and fputc(3) to
 *  copy the file.
 *
 *   @author Ryuho Kudo
 */

#include "copy6.h"
int
main(int argc, char *argv[])
{
  int ch;
  //int r;
  FILE * inStream, *outStream;

  /* Check the command line */
  if (argc != 3) {
    fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Open files */
  inStream = fopen(argv[1],"r");
  if (inStream == NULL){
     perror ("Error opening file");
     exit(EXIT_FAILURE);
  }

  outStream = fopen(argv[2],"w+");
  if (outStream == NULL){
     perror ("Error opening file");
     exit(EXIT_FAILURE);
  }

  /* copy */
   while(1){
      ch = fgetc (inStream);
      if(ch == EOF){
         break;
      }
      fputc((int)ch, outStream );
   }
   fclose (inStream);
   fclose (outStream);

  
  return EXIT_SUCCESS;
}

/* vim: set et ai sts=2 sw=2: */

