
#include <unistd.h>
#include <stdio.h>

int main(void){
   printf("Claims:\n");
   #ifdef _POSIX_VERSION
      printf("\t_POSIX_VERSION = %ld\n", (long)_POSIX_VERSION);
      printf("\t(SUS1=1990 , SUS2=199506L , SUS3= 200112L)\n");
   #else
      printf("\tNot POSIX\n");
   #endif

   #ifdef _XOPEN_UNIX
      printf("\tX/Open\n");
   #ifdef _XOPEN_VERSION
      printf("\t_XOPEN_VERSION = %d\n", _XOPEN_VERSION);
   #else
    printf("\tError: _XOPEN_UNIX defined, but not _XOPEN_VERSION\n");
   #endif
   #else
      printf("\tNot X/Open\n");
   #endif
   
   #if _POSIX_ASYNCHRONOUS_IO <= 0
      printf("\t_POSIX_ASYNCHRONOUS_IO NOT defined\n");
   #else
     printf("\t_POSIX_ASYNCHRONOUS_IO defined\n");
   #endif
   return 0;
}
