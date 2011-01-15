/* Ryuho Kudo
 * lab8c
 * pipeline program
 */

#include "wordgrep.h"

int main(int argc, char* argv[]){
	if(argc != 2){
		fprintf(stderr,"usage: wordgrep <word>\n");
		fflush(stderr);
		return 2;
	}

	int fd[2], status, status2;
	pid_t childpid, childpid2, wpid, wpid2;
	pipe(fd);	
	
	//first child created
	if((childpid = fork()) == -1){
		fprintf(stderr,"first fork failed");
		fflush(stderr);
		return 3;
	}
	if(childpid == 0){
		if(dup2(fd[1], 1) == -1){
			fprintf(stderr,"first dup2 failed");
			fflush(stderr);
		   return 4;
		}
		close(fd[0]);
		close(fd[1]);
		//first process
		execl("/bin/ls", "ls", "-l", NULL);
	}
	else{
		//start the second child for grep
		if((childpid2 = fork()) == -1){
			fprintf(stderr,"second fork failed");
			fflush(stderr);
			return 5;
		}
		if(dup2(fd[0], 0) == -1){
			fprintf(stderr,"second dup2 failed");
			fflush(stderr);
		   return 6;
		}
		close(fd[0]);
		close(fd[1]);
		execlp("/bin/grep", "grep", argv[1], NULL);

		//now wait till the first child ls process is done
		do{
			wpid = waitpid(childpid, &status, 0);
			if (wpid == -1) {
				fprintf(stderr,"first waitpid gave -1");
				fflush(stderr);
				return 7;
			}
			if (WIFEXITED(status)) {
				//this is good, the child exited properly
			}
			else if (WIFSIGNALED(status)) {
				fprintf(stderr,"child killed (signal %d)\n", WTERMSIG(status));
				fflush(stderr);
				return 8;
			}
			else if (WIFSTOPPED(status))  {
				fprintf(stderr,"child stopped (signal %d)\n", WSTOPSIG(status));
				fflush(stderr);
				return 9;
			}
			else{
				fprintf(stderr,"Unexpected status (0x%x)\n", status);
				fflush(stderr);
				return 10;
			}
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
			   
		do{
			wpid2 = waitpid(childpid2, &status2, 0);
			if (wpid2 == -1) {
				fprintf(stderr,"first waitpid gave -1");
				fflush(stderr);
				return 11;
			}
			if (WIFEXITED(status2)) {
				//this is good, the child exited properly
			}
			else if (WIFSIGNALED(status2)) {
				fprintf(stderr,"child killed (signal %d)\n", WTERMSIG(status));
				fflush(stderr);
				return 12;
			}
			else if (WIFSTOPPED(status2))  {
				fprintf(stderr,"child stopped (signal %d)\n", WSTOPSIG(status));
				fflush(stderr);
				return 13;
			}
			else{
				fprintf(stderr,"Unexpected status (0x%x)\n", status);
				fflush(stderr);
				return 14;
			}
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));		
	}
}

