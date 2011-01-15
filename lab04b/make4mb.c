#include <stdio.h>

int main (){
  FILE * plzwrite;
  char * value;
  *value = 'A';
  float i = 0;

  plzwrite = fopen("4MBFile","w");

  while (i != 1048576) {
    fwrite(value,1,sizeof(&value),plzwrite);
    i++;
  }
  fclose(plzwrite);
  return 0;
}
