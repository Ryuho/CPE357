/**
 * @file
 *  <pre>CPE 357 Winter 2009
 *  -------------------
 *  This is an implementation of MUSH,
 *  minimally useful shell.</pre>
 *  @author Ryuho Kudo
 */

#include "mush.h"
#include "parseline.h"


///global variable needed to keep track of what is running
bool* running;
///this keeps track of all the PID number
pid_t* pid;
///this keeps track of how many processes are running
int numOfPid;


/** The main thing.
 * @param argc count of command-line tokens.
 * @param argv array of command-line tokens.
 * @return 0 on success, 1-255 on failure.
 */
int main(int argc, char* argv[]){
   struct stat stattemp;
   int fd;
   bool done = FALSE;
   char* commandLine;
   int* status;
   stageStruct** pStages;
   int** pipefd = NULL;
   
   numOfPid = 0;
   pid = NULL;
   running = NULL;
   status = NULL;
   
   struct sigaction my_act;    //new signal response
   struct sigaction old_act;   //old signal response
    
   //signal stuff
   if(sigemptyset(&(my_act.sa_mask)) == -1){
        fprintf(stderr, "mush: sigemptyset\n");
        _exit(EXIT_FAILURE);
    }
    /*behavior modification of signals*/
    my_act.sa_flags = 0;

    my_act.sa_handler = sighandler;
    if(sigaction(SIGINT, &my_act, &old_act) == -1){
        fprintf(stderr, "mush: sigaction\n");
        _exit(EXIT_FAILURE);
    }

   //handles arguments
   if(argc >= 3){
      fprintf(stderr, "Usage: mush [file]\n");
   }
   else if(argc == 2){
      fd = open(argv[1], O_RDONLY);
      if(fd == -1){
         fprintf(stderr,"error on open(%s, O_RDONLY)\n",argv[1]);
      }
      if(dup2(fd, STDIN_FILENO) == -1){
         fprintf(stderr,"error on dup2(fd, STDIN_FILENO)\n");
         _exit(EXIT_FAILURE);
      }
      close(fd);
   }
   
   //THE while loop
   while(!done){
      //prompt
      if(isatty(fileno(stdin)) && isatty(fileno(stdout))){
         printf("8-P ");
         fflush(stdout);
      }
      
      //get the command
      commandLine = getLine(stdin);
      

      //exit if EOF is sent
      if(feof(stdin)){
         break;
      }
      
      if((commandLine == NULL) || (strlen(commandLine) == 0)){
         continue;
      }
      
      //parse the command into stage structs
      pStages = parseline(commandLine);
      
      
      if(pStages == NULL){
         continue;
      }
      
      
      
      
      //checking to see if it's a cd command
      if(strcmp(pStages[0]->argvv[0], "cd") == 0){
         if(pStages[0]->argcc == 1){
            if(chdir(getenv("HOME")) == -1){
               fprintf(stderr,"chdir failed (chdir(HOME))\n");
            }
         }
         else{
            if(chdir(pStages[0]->argvv[1]) == -1){
               fprintf(stderr,"chdir failed\n");
            }
         }
         freeStage(pStages,NULL);
         continue;
      }
      
      //copy the number of stages
      numOfPid = pStages[0]->totalStageNumber;
      //start mallocing everything
      

      pid = (pid_t*)malloc(sizeof(pid_t)*numOfPid);
      

      running = (bool*)malloc(sizeof(bool)*numOfPid);

      status = (int*)malloc(sizeof(int)*numOfPid);

      pipefd = (int**)malloc(sizeof(int*)*(numOfPid));

      
      //mallocing each file descriptors, in and out
      for(int i = 0; i < numOfPid; i++){
         pipefd[i] = (int*)malloc(sizeof(int)*2);
      }
      
      //setting each of the running state to false
      for(int i = 0; i < numOfPid; i++){
         running[i] = FALSE;
      }
      
      for(int i = 0; i < numOfPid; i++){
         if(pipe(pipefd[i]) == -1){
               fprintf(stderr,"mush: pipe errer");
               close(pipefd[i][0]);
               close(pipefd[i][1]);
               continue;
         }
      }
      
      
      //special case for first pipe in
      if(pStages[0]->input != NULL){
         pipefd[0][0] = open(pStages[0]->input, O_RDONLY);
         fprintf(stderr,"pipefd[0][0] == %d\n",pipefd[0][0]);
         if(pipefd[0][0] == -1){
            fprintf(stderr,"mush: %s: No such file or directory\n",pStages[0]->input);
            freeStuff(status,pipefd,running,pid,numOfPid);
            freeStage(pStages,NULL);
            continue;
         }
      }
      else{
         pipefd[0][0] = STDIN_FILENO;
      }
      //special case for last pipe for out
      if(pStages[numOfPid-1]->output != NULL){
         if((stat(pStages[numOfPid-1]->output, &stattemp) == 0 && !(S_ISDIR(stattemp.st_mode))) || errno == ENOENT){
            pipefd[numOfPid-1][1] = open(pStages[numOfPid-1]->output, (O_WRONLY|O_CREAT|O_TRUNC), S_IRUSR|S_IWUSR);
            fprintf(stderr,"pipefd[numOfPid-1][1] == %d\n",pipefd[numOfPid-1][1]);
            if(pipefd[numOfPid-1][1] == -1){
               fprintf(stderr,"file open failed with : %s",pStages[numOfPid-1]->output);
               close(pipefd[numOfPid-1][0]);
               freeStuff(status,pipefd,running,pid,numOfPid);
               freeStage(pStages,NULL);
               continue;
            }
         }
         else{
            //file is a directory
            fprintf(stderr,"This is a directory\n");
            close(pipefd[numOfPid-1][0]);
            freeStuff(status,pipefd,running,pid,numOfPid);
            freeStage(pStages,NULL);
            continue;
         }
      }
      else{
         pipefd[numOfPid-1][1] = STDOUT_FILENO;
      }
      
      
      for(int i = 0; i < numOfPid; i++){

         //now start duping and closing the file descriptors
         running[i] = TRUE;
         pid[i] = fork();
         //something went wrong
         if(pid[i] == -1){
            fprintf(stderr,"mush: fork error\n");
            close(pipefd[i][0]);
            close(pipefd[i][1]);
            freeStuff(status,pipefd,running,pid,numOfPid);
            freeStage(pStages,NULL);
            continue;
         }
         //this is the child 
         else if(pid[i] == 0){
            //make mushit killable by SIGINT
            if(sigaction(SIGINT, &old_act, NULL) == -1){
            }
            
            
            if(i == 0 && numOfPid == 1){
            }
            
            
            if(numOfPid != 1){
               dup2(pipefd[i][1],STDIN_FILENO);
               if(i == (numOfPid-1)){
                  //fprintf(stderr,"STDOUT_FILENO=%d\n",STDOUT_FILENO);
                  //dup2(1,STDOUT_FILENO);
               }
               else{
                  dup2(pipefd[i+1][0],STDOUT_FILENO);
               }
            }
            
            
            if(execvp(pStages[i]->argvv[0], pStages[i]->argvv) == -1){
               fprintf(stderr,"execvp failed with : %s\n",pStages[i]->argvv[0]);
               freeStuff(status,pipefd,running,pid,numOfPid);
               freeStage(pStages,NULL);
               _exit(EXIT_FAILURE);
            }
            fprintf(stderr,"------------------\n");
         }
         

         //close if not std
         if(i != 0){
            close(pipefd[i][0]);
         }
         if(i != numOfPid-1){
            close(pipefd[i][1]);
         }
         
         
      }
      //end of the for loop

      //and now we wait for all the child to come back
      for(int i = 0; i < numOfPid; i++){
         if(waitpid(pid[i], &status[i], 0) == -1){
            if(WIFSIGNALED(status[i])){
               if(WTERMSIG(status[i]) != SIGINT){
                  //fprintf(stderr, "mush: waitpid signaled error %d\n", WTERMSIG(status[i]));
               }
            }
         }
         running[i] = FALSE;
      }
      
      freeStage(pStages,NULL);
      freeStuff(status,pipefd,running,pid,numOfPid);
   }
   //the very long while loop ends here
   
   free(commandLine);
   fprintf(stdout,"Good Bye.\n");
   return EXIT_SUCCESS;
}

/** Used to fee stuff
 * @param status int array needed to be freed
 * @param pipefd file descriptor, array of array that needed to be freed
 * @param running bool array needed to be freed
 * @param pid pid_t array needed to be freed
 * @param numOfPid needed in measuring how large an array of array is
 */
void freeStuff(int* status, int** pipefd, bool* running, pid_t* pid, int numOfPid){
   if(status != NULL){
      free(status);
   }
   if(pid != NULL){
      free(pid);
   }
   if(running != NULL){
      free(running);
   }
   if(pipefd != NULL){
      for(int i = 0; i < numOfPid; i++){
         free(pipefd[i]);
      }
      free(pipefd);
   }
}


/** Sig handler, kills stuff
 * @param sig the signal number
 */
void sighandler(int sig){
   for(int i = 0; i < numOfPid; i++){
      if(pid[i] != -1){
         kill(pid[i], SIGINT);
         pid[i] = -1;
      }
   }
}


