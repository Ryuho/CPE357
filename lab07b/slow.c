/* Ryuho Kudo
 * rkudo 9:00am
 * lab6b slow program
 * main and helper void program
 */

#include "slow.h"

void spin(char c){
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [100];

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	strftime (buffer,100,"%a %b %d %X %Z %Y",timeinfo);
	printf(buffer);
	printf(" %c",c);
	fflush(stdout);
	printf("\r");
	sleep(1);
}

int main(void){
	while (1){
		spin('|');
		spin('/');
		spin('-');
		spin('\\');
	}
}

