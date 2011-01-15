//Ryuho Kudo
//lab05a

#include "myls.h"



int main(int argc, char* argv[]){
   DIR *dirp;
   struct dirent  *dp;
   struct stat     statbuf;
   struct passwd  *pwd;
   struct group   *grp;
   struct tm      *tm;
   char            datestring[256];

   if ((dirp = opendir(".")) == NULL) {
      perror("couldn't open '.'");
      return EXIT_FAILURE;
   }

   while ((dp = readdir (dirp)) != NULL) {
      if (lstat(dp->d_name, &statbuf) == -1){
         continue;
      }
      /* Print out type, permissions, and number of links. */

      printf("%04o", statbuf.st_mode & 4095);


      //prints # of links
      printf("%4d", statbuf.st_nlink);
      
      
      
      
      /* Print out owner's name if it is found using getpwuid(). */
      if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
         printf(" %-8.8s", pwd->pw_name);
      else
         printf(" %-8d", statbuf.st_uid);

      /* Print out group name if it is found using getgrgid(). */
      if ((grp = getgrgid(statbuf.st_gid)) != NULL)
        printf(" %-8.8s", grp->gr_name);
      else
        printf(" %-8d", statbuf.st_gid);
      /* Print size of file. */
      printf(" %9jd", (intmax_t)statbuf.st_size);


      tm = localtime(&statbuf.st_mtime);


      /* Get localized date string. */
      strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);


      printf(" %s %s\n", datestring, dp->d_name);

      //printf("%s\n",dp->d_name);

      }



   return EXIT_SUCCESS;
}

