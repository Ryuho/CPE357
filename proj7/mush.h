/**
 * @file
 *  <pre>CPE 357 Winter 2009
 *  -------------------
 *  This is the header for parseline.c</pre>
 *  @author Ryuho Kudo
 */

#ifndef MUSH_H_
#define MUSH_H_

#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

/** @typedef bool
  * standard bool struct used for signs **/
/** @typedef boolean
  * standard bool struct used for signs **/
typedef enum boolean { FALSE, TRUE } bool;

void sighandler(int sig);
void freeStuff(int* status, int** pipefd, bool* running, pid_t* pid, int numOfPid);
#endif
