/**
*  CPE 357 Fall 2008
*  -------------------
*  lab7b unpackbits function
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

void unpackBinary(char c){
  int intRep = (int)c;
  //fprintf(stderr,"   original intRep=%d\n",intRep);
  //1 2 4 8 16 32 64 128
  int binary[8] = {0,0,0,0,0,0,0,0};
  

  if(intRep >= 128){
    binary[7] = 1; 
    intRep = intRep-128;
    //fprintf(stderr,"128 tripped, =%d\n",intRep);
  }
  if(intRep >= 64){
    binary[6] = 1; 
    intRep = intRep-64;
    //fprintf(stderr,"64 tripped, =%d\n",intRep);
  }
  if(intRep >= 32){
    binary[5] = 1; 
    intRep = intRep-32;
    //fprintf(stderr,"32 tripped, =%d\n",intRep);
  }
  if(intRep >= 16){
    binary[4] = 1; 
    intRep = intRep-16;
    //fprintf(stderr,"16 tripped, =%d\n",intRep);
  }
  if(intRep >= 8){
    binary[3] = 1; 
    intRep = intRep-8;
    //fprintf(stderr,"8 tripped, =%d\n",intRep);
  }
  if(intRep >= 4){
    binary[2] = 1; 
    intRep = intRep-4;
    //fprintf(stderr,"4 tripped, =%d\n",intRep);
  }
  if(intRep >= 2){
    binary[1] = 1; 
    intRep = intRep-2;
    //fprintf(stderr,"1 tripped, =%d\n",intRep);
  }
  if(intRep == 1){
    binary[0] = 1; 
    intRep = intRep-1;
    //fprintf(stderr,"1 tripped, =%d\n",intRep);
  }

  if(intRep != 0){
    fprintf(stderr,"  unpackBinary error, intRep=%d\n",intRep);
  }

   if(!(binary[7] || binary[6] || binary[5] || binary[4] || binary[3] || binary[1] || binary[0]) && binary[2]){
      exit(1);
   }
   
  //fprintf(stderr,"  done intRep=%d\n",intRep);
  fprintf(stdout, "%d%d%d%d%d%d%d%d",binary[7],binary[6],binary[5],
          binary[4],binary[3],binary[2],binary[1],binary[0]);
}

int
main (void)
{
  unsigned char c;
  int loop = 0;
  set_input_mode ();

  while (1)
    {
      read (STDIN_FILENO, &c, 1);
      if(loop == 7){
		unpackBinary(c);
                fflush(stdout);
		printf(" \n");
		loop = 0;
      }
      else{
		unpackBinary(c);
		printf(" ");
                fflush(stdout);
		loop++;
      }
    }
  return EXIT_SUCCESS;
}

