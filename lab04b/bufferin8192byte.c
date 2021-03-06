#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

void copy(char *from, char *to, int buffsize);

  
int main(){
  printf("Starting 8192 byte buffer copy\n");
  copy("4MBFile","junk",8192);
  printf("Finished 8192 byte buffer");
  return 0;
}

void copy(char *from, char *to, int buffsize){
  int fromfd = -1, tofd = -1;
  ssize_t nread, nwrite, n;
  char buf[buffsize];

  fromfd = open(from, O_RDONLY);
  tofd = open(to, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
  while ((nread = read(fromfd, buf, sizeof(buf))) > 0) {
    nwrite = 0;
    do{
       n = write( tofd, &buf[nwrite], nread - nwrite);
       nwrite += n;
    } while (nwrite < nread);
  }

  close(fromfd);
  close(tofd);
}


