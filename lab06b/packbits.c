/**
*  CPE 357 Fall 2008
*  -------------------
*  lab7c packbits function
*
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

/* Use this variable to remember original terminal attributes. */

struct termios saved_attributes;

void reset_input_mode (void){
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode (void){
  struct termios tattr;
  //char *name;

  /* Make sure stdin is a terminal. */


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

void packBinary(int binary[8]){
	char answer = 0;


	if(binary[0] == 1){
		answer = (answer | 128);
	}
	if(binary[1] == 1){
		answer = (answer | 64);
	}
	if(binary[2] == 1){
		answer = (answer | 32);
	}
	if(binary[3] == 1){
		answer = (answer | 16);
	}
	if(binary[4] == 1){
		answer = (answer | 8);
	}
	if(binary[5] == 1){
		answer = (answer | 4);
	}
	if(binary[6] == 1){
		answer = (answer | 2);
	}
	if(binary[7] == 1){
		answer = (answer | 1);
	}
   
	//fprintf(stderr,"|packBinary executed|");
	fprintf(stdout, "%c",answer);
	fflush(stdout);
}

int
main (void)
{
	int binary[8] = {0,0,0,0,0,0,0,0};
	char tempChar = '0';
	int binaryCount = 0;
	set_input_mode ();
	while(1){
		read(STDIN_FILENO, &tempChar, 1);
		if(tempChar == '\004'){
			break;
		}
		else if(tempChar == 48){
			binary[binaryCount] = 0;
			binaryCount++;
		}
		else if(tempChar == 49){
			binary[binaryCount] = 1;
			binaryCount++;
		}
		else if((tempChar == 32) || (tempChar == 10)){
			//fprintf(stderr,"|whitespace detected|");
			if(binaryCount != 0){
				packBinary(binary);
				binary[0]=binary[1]=binary[2]=binary[3]=binary[4]=binary[5]=binary[6]=binary[7]=0;
				binaryCount = 0;
			}
		}
		else{
			//fprintf(stderr,"|something else detected|");
			binary[0]=binary[1]=binary[2]=binary[3]=binary[4]=binary[5]=binary[6]=binary[7]=0;
			binaryCount = 0;
		}
		if(binaryCount == 8){
			packBinary(binary);
			binary[0]=binary[1]=binary[2]=binary[3]=binary[4]=binary[5]=binary[6]=binary[7]=0;
			binaryCount = 0;
		}
	}
	return EXIT_SUCCESS;
}

