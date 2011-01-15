/**
 * @file
 *  <pre>CPE 357 Winter 2009
 *  -------------------
 *  The header for mytimer.c</pre>
 *  @author Ryuho Kudo
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h> 
#include <string.h> 
#include <sys/time.h> 
#include <math.h>

///The number of ticks per a single second
#define TICKS_PER_SECOND 16
///Amount of seconds to subtract per tick
#define SUBTRACT_CONSTANT 0.0625
///Measurement of seconds per tick.
#define MICRO_PER_TICK 62500

/** @typedef bool
  * standard bool struct used for signs **/
/** @typedef boolean
  * standard bool struct used for signs **/
typedef enum boolean { FALSE, TRUE } bool;

///resets the terminal settings
void reset_input_mode (void);
///sets the terminal settings
void set_input_mode (void);
///initializes/sets the time
void setTime(int timeValue);
///increments/decrements time
void changeTime(char c);
///called when SIGALAR is detected
void alarm_handler (int signum);

///prints the time
void printTime(bool isAlarm);
///sets up the SIGALAR by setitimer
void timerSetup(void);
