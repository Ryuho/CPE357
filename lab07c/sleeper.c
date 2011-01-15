//Ryuho Kudo
//lab07c - sleeper

#include "sleeper.h"

int main(int argc, char* argv[]){
   signal(SIGINT,sighandler);
   while(1){
      sleep(1);
   }
   return 0;
}

void sighandler(int sig){
   fprintf(stdout,"I'm sleeping...\n");
   fflush(stdout);
   (void) signal(SIGINT,sighandler);
}

