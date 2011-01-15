/* Ryuho Kudo
 * lab10c
 * qreadr.c
 */
 
#include "qreadr.h"

int main(int argc, char *argv[]) {
	mqd_t msgq_id;
	char* msgcontent = (char*)malloc(MAX_MSG_LEN);
	int msgsz;
	unsigned int sender;
	struct mq_attr msgq_attr;
	
	assert(argc == 2);
	if (argv[1][0] != '/') {
		fprintf(stderr, "Queue name must start with '/'\n");
		exit(EXIT_FAILURE);
	}
	
	/* opening the queue		--  mq_open() */
	msgq_id = mq_open(argv[1], O_RDWR);
	if (msgq_id == (mqd_t)-1) {
		perror("In mq_open()");
		exit(1);
	}

	/* getting the attributes from the queue		--  mq_getattr() */
	mq_getattr(msgq_id, &msgq_attr);
	printf("Queue \"%s\":\n\t- stores at most %ld messages\n\t- large at most %ld bytes each\n\t- currently holds %ld messages\n", argv[1], msgq_attr.mq_maxmsg, msgq_attr.mq_msgsize, msgq_attr.mq_curmsgs);

	/* getting a message */
	while(1){
		msgsz = mq_receive(msgq_id, msgcontent, MAX_MSG_LEN, &sender);
		if (msgsz == -1) {
			perror("In mq_receive()");
			exit(1);
		}

		if(msgsz != 0){
			msgcontent[msgsz] = '\0';
			fprintf(stdout,"%d %s\n", sender, msgcontent);
			
		}
		if(sender == 666){
			break;
		}
	}
	/* closing the queue	--  mq_close() */
	mq_close(msgq_id);
	
	
	return 0;
}

