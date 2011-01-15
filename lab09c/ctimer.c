#include <stdio.h>
#include <math.h>

// Get timer value
#define WHEN ({unsigned long long int __when;			\
	asm volatile ( "rdtsc		    \n\t"		\
	    : "=A" (__when)	/* rdtsc output in edx,eax */	\
	    : /* no inputs */					\
	    ) ;							\
	__when; } )


int main(int argc, char *argv[]) {
   int i = 0;
   long long int start = 0;
   long long int end = 0;
   long long int temp = 0;
   long long int TOTAL = 0;
	long long int MAXIMUM = 0;
	long long int MINIMUM = 100000000;
	for(; i < 1000000; i++){
		start = WHEN;                
      end = WHEN;
      temp = start - end;
		temp = fabs(temp);
		if(MAXIMUM < temp){
			MAXIMUM = temp;
		}
		if(MINIMUM > temp){
			MINIMUM = temp;
		}
		TOTAL += temp;
	}
	fprintf(stdout,"Get time, then get time again\n");
	fprintf(stdout,"Average: %lld ticks\n",TOTAL/1000000);
 	fprintf(stdout,"Maximum: %lld ticks\n",MAXIMUM);
	fprintf(stdout,"Minimum: %lld ticks\n",MINIMUM);
	
	int a, b, c;
   a = 1;
   b = 2;
   c = 4;
   
	i = 0;
   start = 0;
   end = 0;
   temp = 0;
   TOTAL = 0;
	MAXIMUM = 0;
	MINIMUM = 100000000;
	for(; i < 1000000; i++){
		start = WHEN;
		
		__asm__ __volatile__(
         "   addl %1,%0 ;\n"
         : "=m"  (a)
         : "ir"  (c), "m" (b)               /* no clobber-list */
      );
                
      end = WHEN;
      temp = start - end;
		//fprintf(stdout,"|%lld|",temp);
		temp = fabs(temp);
		if(MAXIMUM < temp){
			MAXIMUM = temp;
		}
		if(MINIMUM > temp){
			MINIMUM = temp;
		}
		TOTAL += temp;
	}
	fprintf(stdout,"Get time, then add in assmembly /wo lock, then get the time again\n");
	fprintf(stdout,"Average: %lld ticks\n",TOTAL/1000000);
 	fprintf(stdout,"Maximum: %lld ticks\n",MAXIMUM);
	fprintf(stdout,"Minimum: %lld ticks\n",MINIMUM);

   a = 1;
   b = 2;
   c = 4;
   
	i = 0;
   start = 0;
   end = 0;
   temp = 0;
   TOTAL = 0;
	MAXIMUM = 0;
	MINIMUM = 100000000;
	for(; i < 1000000; i++){
		start = WHEN;
		
		__asm__ __volatile__(
         "   lock       ;\n"
         "   addl %1,%0 ;\n"
         : "=m"  (a)
         : "ir"  (c), "m" (b)               /* no clobber-list */
      );
                
      end = WHEN;
      temp = start - end;
		//fprintf(stdout,"|%lld|",temp);
		temp = fabs(temp);
		if(MAXIMUM < temp){
			MAXIMUM = temp;
		}
		if(MINIMUM > temp){
			MINIMUM = temp;
		}
		TOTAL += temp;
	}
	fprintf(stdout,"Get time, then add in assmembly with lock, then get the time again\n");
	fprintf(stdout,"Average: %lld ticks\n",TOTAL/1000000);
 	fprintf(stdout,"Maximum: %lld ticks\n",MAXIMUM);
	fprintf(stdout,"Minimum: %lld ticks\n",MINIMUM);
	
   return 0;
}


