#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>

int main(void){

	struct rlimit limit;

	getrlimit(RLIMIT_AS,&limit);
	printf("RLIMIT_AS:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_CORE,&limit);
	printf("RLIMIT_CORE:	Soft=%d,		",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_CPU,&limit);
	printf("RLIMIT_CPU:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_DATA,&limit);
	printf("RLIMIT_DATA:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_FSIZE,&limit);
	printf("RLIMIT_FSIZE:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);
#if __linux__
	getrlimit(RLIMIT_LOCKS,&limit);
	printf("RLIMIT_LOCKS:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_MEMLOCK,&limit);
	printf("RLIMIT_MEMLOCK:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_MSGQUEUE,&limit);
	printf("RLIMIT_MSGQUEUE:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_NICE,&limit);
	printf("RLIMIT_NICE:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_MSGQUEUE,&limit);
	printf("RLIMIT_MSGQUEUE:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);
#endif
	getrlimit(RLIMIT_NOFILE,&limit);
	printf("RLIMIT_NOFILE:	Soft=%d,		",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);
#if __linux__
	getrlimit(RLIMIT_NPROC,&limit);
	printf("RLIMIT_NPROC:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_RSS,&limit);
	printf("RLIMIT_RSS:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_RTPRIO,&limit);
	printf("RLIMIT_RTPRIO:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

	getrlimit(RLIMIT_SIGPENDING,&limit);
	printf("RLIMIT_SIGPENDING:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);
#endif
	getrlimit(RLIMIT_STACK,&limit);
	printf("RLIMIT_STACK:	Soft=%d,		",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);

#ifndef __amd64
	getrlimit(RLIM_INFINITY,&limit);
	printf("RLIMIT_INFINITY:	Soft=%d,	",(int)limit.rlim_cur);
	printf("Hard=%d\n",(int)limit.rlim_max);
#endif
	return 0;
}

