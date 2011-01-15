/**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 *
 * A program with race conditions.
 *
 * Last Modified: Tue Mar 10 10:29:00 PDT 2009</pre>
 * @author Kevin O'Gorman
 */


#include "adder.h"


static int threads_running;
static int threads_started = 0;
static int sum = 0;

pthread_mutex_t mutexThreadCount = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexSum = PTHREAD_MUTEX_INITIALIZER;

void *plusser(void *arg){
  int val = (int)arg;
  pthread_mutex_lock(&mutexSum);
  sum += val;
  pthread_mutex_unlock(&mutexSum);
  thread_action(STOP, NULL, NULL);
  return NULL;  // NOT REACHED
}
  
void *minuser(void *arg){
  int val = (int)arg;
  pthread_mutex_lock(&mutexSum);
  sum -= val;
  pthread_mutex_unlock(&mutexSum);
  thread_action(STOP, NULL, NULL);
  return NULL;  // NOT REACHED
}

void thread_action(
    thread_action_e action,
    void *(*start_routine)(void*),
    void *restrict arg){
  
  pthread_mutex_lock(&mutexThreadCount);
  static int thread_count = 0;;
  static int initSeen = 0;
  pthread_mutex_unlock(&mutexThreadCount);
  int r;
  pthread_t tid;
  struct timespec waittime = {0,00000000}; // 100 milliseconds

  if (action != INIT && !initSeen ) {
    fprintf(stderr, "Not initialized.\n");
    exit(EXIT_FAILURE);
  }

  switch(action) {

  case START:
    if (thread_count >= THREAD_LIMIT) {
      pthread_mutex_lock(&mutexThreadCount);
      fprintf(stderr, ">Throttling thread creation\n");
      while (thread_count >= THREAD_LIMIT) {
        nanosleep(&waittime, NULL);
      }
      fprintf(stderr, "Restarting thread creation\n");
      pthread_mutex_unlock(&mutexThreadCount);
    }
    
    
    do {
      r = pthread_create(&tid, NULL, start_routine, arg);
    } while (r == -1 && errno == EAGAIN);
    
    pthread_mutex_lock(&mutexThreadCount);
    thread_count = thread_count + 1;
    threads_started = threads_started + 1;
    pthread_mutex_unlock(&mutexThreadCount);
    break;

  case STOP:
    pthread_mutex_lock(&mutexThreadCount);
    thread_count = thread_count - 1;
    pthread_mutex_unlock(&mutexThreadCount);
    pthread_exit(arg);
    break;

  case INIT:
    pthread_mutex_lock(&mutexThreadCount);
    thread_count = 0;
    initSeen = 1;
    pthread_mutex_unlock(&mutexThreadCount);
    break;

  default:
    fprintf(stderr, "Bad thread action");
    exit(EXIT_FAILURE);
  }
}

/** The main thing.
 * @param argc the number of tokens on the input line.
 * @param argv an array of tokens.
 * @return 0 on success, 1-255 on failure
 */
int
main(int argc, char *argv[])
{
  long int seedval;
  int i;
  double drand;
  int val;

  if (argc != 1) {
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  srand48(seedval);
  thread_action(INIT, NULL, NULL);
  sum = 0;

  for (i = 0; i < ACTION_LIMIT; i++) {
    drand = drand48() * RANGE;
    val = (int)drand;
    thread_action(START, plusser, (void *)val);
    thread_action(START, minuser, (void *)val);
  }
  sleep(2);
  printf("After a suitable delay, there are %d threads and the sum is %d.\n",
      threads_running, sum);
  printf("There were %d total threads started.\n",threads_started);

  if (threads_running == 0 && sum == 0) {
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

/* vim: set et ai sts=2 sw=2: */

