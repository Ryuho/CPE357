#define ISASCII
#define VSCANF
#define GETCWD

#include <unistd.h>
#include <stdio.h>

int main(void){

#ifdef ISASCII
   char ch = 'a';
   if(isascii(ch) == 0){
      printf("this is not ascii\n");
   }
   else{
      printf("this is ascii\n");
   }
#endif

#ifdef VSCANF
   //va_list ptr;
   int i;
   //printf("type an int:");
   vscanf(" %d ", NULL);
   printf("you typed: %d", i);
#endif

#ifdef GETCWD
   char buffer[256];
   unsigned long size = 256;
   getcwd(buffer, size);
   printf("current dir: %s\n",buffer);
#endif

   return 0;
}

