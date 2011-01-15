/**
 * @file
 *  <pre>CPE 357 Winter 2009
 *  -------------------
 *  This program is a kitchen counter using
 *  the signal processing technique. It uses
 *  functions like sigaction, sigprocmask and 
 *  setitimer to achieve this.</pre>
 *  @author Ryuho Kudo
 */


#include "mytimer.h"

///this struct is used to set and save the terminal attributes
struct termios saved_attributes;
///this int is used to tell what time the clock is on in seconds
double time;
///This boolean is used to determin if the clock is currently running or not
bool running;


/** The main thing.
 * @param argc count of command-line tokens.
 * @param argv array of command-line tokens.
 * @return 0 on success, 1-255 on failure.
 */
int main(int argc, char* argv[]){
   if(argc != 2){
      printf("usage: mytimer <seconds>\n");
      return EXIT_FAILURE;
   }
   
   if(sscanf(argv[1], "%lf",&time) != 1){
      printf("\"%s\" is not a number.\n", argv[1]);
      return EXIT_FAILURE;
   }
   if(time <= 0){
      printf("Invalid time(%lf). Must be >= 0.\n",time);
      return EXIT_FAILURE;
   }
   
   running = TRUE;
   
   char c = 'z';
   
   set_input_mode();
   
   //setup the signal stuff
   timerSetup();
   
   while(1){
      read (STDIN_FILENO, &c, 1);
      if(c == 'q'){
         fprintf(stdout,"\n");
         fflush(stdout);
         return EXIT_SUCCESS;
      }
      if(c == 'h' || c == 'H' || c == 'm' ||
      c == 'M' || c == 's' || c == 'S' ||
      c == 'c' || c == 'r'){
         changeTime(c);
         c = 'z';
      }
   }
   return EXIT_SUCCESS;
}


/**
 * Sets the input mode up, such as clearing
 * ICANON and ECHO off, disabling the ctr-c/z
 * commands. This is done by termios and tcsetattr.
 */
void set_input_mode (void){
   struct termios tattr;
   //char *name;

   /* Make sure stdin is a terminal. */
   if (!isatty (STDIN_FILENO)){
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
   tattr.c_cc[VINTR] = 0; //ctrl-c
   tattr.c_cc[VEOF] = 0; //ctrl-d
   tattr.c_cc[VSUSP] = 0; //ctrl-z
   tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

/**
 * Removes the settings set by tcsettar
 * this is run when exeting the program, set up
 * by atexit command.
 */
void reset_input_mode (void){
   tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}


/**
 * This helper function calculates the hour, min, sec
 * then sets the global variable, time, accordingly.
 * It then prints the result by calling printTime();
 * @param c The char value choosing what action to take
 * it can be to just check / stop time.
 * or it can be to add / subtract time.
 */
void changeTime(char c){
   //adding an hour
   if(c == 'h'){
      time += 3600;
   }
   //subtracting an hour
   if(c == 'H'){
      time -= 3600;
   }
   //adding a minute
   if(c == 'm'){
      time += 60;
   }
   //subtracting a minute
   if(c == 'M'){
      time -= 60;
   }
   //adding a second
   if(c == 's'){
      time += 1;
   }
   //subtracting a second
   if(c == 'S'){
      time -= 1;
   }
   
   //clearing the timer
   if(c == 'c'){
      time = 0;
   }
   //starting/stopping the timer
   if(c == 'r'){
      if(running == TRUE){
         running = FALSE;
         alarm(0);
      }
      else{
         running = TRUE;
         timerSetup();
      }
   }
   
   printTime(FALSE);
}

/**
 * This helper function sets up the SIGALRM by using sigaction and
 * setitimer. 
 */
void timerSetup(void){
   //declare signal stuff for spin
   struct sigaction sa;
   struct itimerval timer; 


   // Install alarm_handler as the signal handler for SIGALRM. 
   memset (&sa, 0, sizeof (sa)); 
   sa.sa_handler = &alarm_handler; 
   sigaction (SIGALRM, &sa, NULL); 


   // Configure the timer_spin to expire after MICRO_PER_TICK... 
   timer.it_value.tv_sec = 0; 
   timer.it_value.tv_usec = MICRO_PER_TICK;
   // ... and every MICRO_PER_TICK after that.  
   timer.it_interval.tv_sec = 0; 
   timer.it_interval.tv_usec = MICRO_PER_TICK;
   
   //actually set it
   setitimer (ITIMER_REAL, &timer, NULL); 
}




/**
 * This function is called only when SIGALRM is detected. 
 * This prints out the spinning wheel, and also decrements
 * the time int.
 * @param signum the int corresponding to the signal number
 */
void alarm_handler (int signum){
   printTime(TRUE);
   time = time - (SUBTRACT_CONSTANT);
   signal(SIGALRM,alarm_handler);
}

/**
 * This function is called only when SIGALRM is detected. 
 * This prints out the spinning wheel, and also decrements
 * the time int.
 * @param isAlarm boolean used to signify if the caller was
 * alarm or not
 */ 
void printTime(bool isAlarm){
   fprintf(stdout,"                 \r");
   static int spinCount= 0; 
   int tempTime = abs(time);
   if(time == 0 && isAlarm){
      fprintf(stdout,"\a");
      fprintf(stdout,"\rBeeeep! Time's up!\n");
   }
   //static char spin;
   if(spinCount == 0){
      fprintf(stdout,"\r|");
      spinCount++;
   }
   else if(spinCount == 1){
      fprintf(stdout,"\r/");
      spinCount++;
   }
   else if(spinCount == 2){
      fprintf(stdout,"\r-");
      spinCount++;
   }
   else if(spinCount == 3){
      fprintf(stdout,"\r\\");
      spinCount = 0;
   }
   if(time >= 0){
      printf("  ");      
   }
   else{
      printf(" -");
   }
   printf("%d",tempTime/3600);
   tempTime = tempTime - ((tempTime/3600)*3600);
   printf(":%02d",tempTime/60);
   tempTime = tempTime - ((tempTime/60)*60);
   printf(":%02d",tempTime);
   fflush(stdout);
}

