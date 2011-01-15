/**
*  CPE 357 Winter 2008
*  -------------------
*  lab6c
*
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

/* Use this variable to remember original terminal attributes. */

struct termios saved_attributes;

void 
reset_input_mode (void)
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void 
set_input_mode (void)
{
  struct termios tattr;
  //char *name;

  /* Make sure stdin is a terminal. */
  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
  }
  if (!isatty (STDOUT_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
  }

  /* Save the terminal attributes so we can restore them later. */
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);

  /* Set the funny terminal modes. */
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

void endec(unsigned c){
   if((c >= 65) && (c <= 90)){
      c = c+13;
      if(c > 90){
         c = c-26;
      }
   }
   else if((c >= 97) && (c <= 122)){
      c = c+13;
      if(c > 122){
         c = c-26;
      }
   }
   fprintf(stdout,"%c",c);
}

int
main (void)
{
  unsigned char c;
  set_input_mode ();
  while ((c = getchar()) != '\004'){
		endec(c);
  }
   //fprintf(stdout,"\n");
   fflush(stdout);
  return EXIT_SUCCESS;
}

