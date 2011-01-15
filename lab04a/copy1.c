/**
 *  CPE 357 Winter 2009
 *  -------------------
 *  Sample program for lab 4a; this one uses read(2) and write(2) to
 *  copy the file.  What an inefficient way to do it!
 *
 *  Last Modified: Sat Jan 24 19:55:53 PST 2009
 *  @author Kevin O'Gorman
 */

#include "copy1.h"
int
main(int argc, char *argv[])
{
  char ch;
  int r;
  int infd, outfd;

  /* Check the command line */
  if (argc != 3) {
    fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Open files */
  infd = open(argv[1], O_RDONLY);
  if (infd == -1) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  outfd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  if (outfd == -1) {
    perror(argv[2]);
    exit(EXIT_FAILURE);
  }

  /* copy */
  while ((r = read(infd, &ch, 1)) == 1) {
    if ((r = write(outfd, &ch, 1)) == -1) {
      perror(argv[2]);
      exit(EXIT_FAILURE);
    }
  }

  if (r == -1) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  /* close files */
  if (close(infd) == -1) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  if (close(outfd) == -1) {
    perror(argv[2]);
    exit(EXIT_FAILURE);
  }
  
  return EXIT_SUCCESS;
}

/* vim: set et ai sts=2 sw=2: */

