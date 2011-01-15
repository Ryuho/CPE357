#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

typedef enum {START, STOP, INIT} thread_action_e;

void thread_action(thread_action_e act, void *(*start_routine)(void*), void *restrict arg);
void *plusser(void *arg);
void *minuser(void *arg);

// Be a good citizen -- don't fork bomb (threads count as forks)
#define THREAD_LIMIT 10

// How many action pairs to generate
#define ACTION_LIMIT 100

// Range of values to be plussed/minused
#define RANGE 100
