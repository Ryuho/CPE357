/**
 *  @file
 *  <pre>CPE 357
 *  -------------------
 *
 *  Program to compute a signv value via a macro.
 *
 *  @author Kevin O'Gorman
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sigmac.h"

int
main(int argc, char *argv[])
{
   int i = isatty(fileno(stdin));
   double din, dout;
   int r;
   int done = 0;
  do  {
    if(i != 0){
       printf("Enter a number: ");
    }
    r = scanf("%lg", &din);
    if (r != 1) {
      if (feof(stdin)) {
        done = 1;
      } else if (r == 0){
        printf("Junk on the input.  Sorry.\n");
        exit(EXIT_FAILURE);
      } else {
        perror("Input");
        exit(EXIT_FAILURE);
      }
    } else {
      dout = SIG(din);
      printf("In: %g; out: %g\n", din, dout);
    }
  } while (!done);
  if(i != 0){
     printf("\n\nBye-bye\n");
  }
  return EXIT_SUCCESS;
}

/* vim: set et ai sts=2 sw=2: */

