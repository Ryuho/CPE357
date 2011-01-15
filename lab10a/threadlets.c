/* Ryuho Kudo
 * lab10a strtok
 * program that uses threads
 */

#include "threadlets.h"


int threadNumber = 0;

void *thread_function(void *arg)
{
  //pid_t mypid = getpid();
  int original = (int)malloc(sizeof(int));
  original = (int)arg;
  int i = original;
  fprintf(stdout,"got into thread %d\n",original);
  fflush(stdout);
  while(i <= threadNumber) {
    //printf("thread 2 (%d) says %ld\n", mypid, ++x);
      fprintf(stdout,"thread %d says %d\n",original, i);
      fflush(stdout);
      i++;
      
  }
  //sleep(1);
  return NULL;
}


int
main(int argc, char *argv[])
{
  if(argc != 2){
    printf("threadlets: needs exactly one argument\n");
    exit(1);
  }
  char* pEnd;
  threadNumber = strtol (argv[1],&pEnd,10);

  if(threadNumber > 10 || threadNumber < 1){
    printf("threadlets: argument needs to be between 1 and 10\n");
    exit(1);
  }
  
  pthread_t tid[11];
  pthread_attr_t attrs;
  //pid_t mypid = getpid();
  int r;

  r = pthread_attr_init(&attrs);
  if (r != 0) {
    fprintf(stderr, "pthread_attr_init: %s\n", strerror(r));
    exit(EXIT_FAILURE);
  }
  
  for(int i = 1; i <= threadNumber; i++){
    fprintf(stdout,"starting thread #%d\n",i);
    fflush(stdout);
    r = pthread_create(&tid[i],  // thread ID
        &attrs,               // attributes (or NULL)
        thread_function,      // thread function
        (void *)i);                // arg to pass
    if (r != 0) {
      fprintf(stderr, "pthread_create: %s\n", strerror(r));
      exit(EXIT_FAILURE);
    }

  }

  for(int i = 1; i <= threadNumber; i++){
    if(pthread_join(tid[i], NULL) == 0){
      fprintf(stdout,"thread %d ended.\n",i);
    }
    else{
      fprintf(stderr,"error thread %d\n",i);
    }    
  }
  fflush(stdout);
  fflush(stderr);

  
  return EXIT_SUCCESS;
}

