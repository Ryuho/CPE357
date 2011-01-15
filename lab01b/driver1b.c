/**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 * 
 * Driver for Lab 1 B
 *
 * Last Modified: Mon Jan  5 19:59:47 PST 2009</pre>
 * @author Kevin O'Gorman
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "lab01b.h"

#define START_INDEX 5
#define INDEX_STRIDE 7

/** The main thing.
 * @param argc the number of tokens on the input line.
 * @param argv an array of tokens.
 * @return 0 on success, 1-255 on failure
 */
int
main(int argc, char *argv[])
{
  // a sample string
  char *string = "The quick brown fox jumped over the lazy dog's back.";
  char *missing = "ABCDEFGHIJKLMNOPQRS-UVWXYZ!@#$%^&*()_+1234567890=";
  // a few select primes
  int intArray[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 }; 

  int index;
  int i;
  int arrayCount = sizeof(intArray) / sizeof(intArray[0]);

  // enable malloc checks.
  setenv("MALLOC_CHECK", "1", 1);

  // check that the stride is prime to the array size; since it's prime and
  // smaller than the array size, just a divisibility check should do it.
  // If this fails, the loop below wouldn't work as intended.
  assert(arrayCount % INDEX_STRIDE != 0);

  ////////////////////////////////////////////////////////////////////// test mystrchr
  fprintf(stderr, "///////////////////////////// testing mystrchr\n");
  fprintf(stderr, "Looking for: ");
  for (i = 0; string[i]; i++) {
    fprintf(stderr, "%c", string[i]);
    assert(strchr(string, string[i]) == mystrchr(string, string[i]));
  }
  fprintf(stderr, "\n");
  fprintf(stderr, "Looking for: ");
  for (i = 0; missing[i]; i++) {
    fprintf(stderr, "%c", missing[i]);
    assert(strchr(string, missing[i]) == mystrchr(string, missing[i]));
  }
  fprintf(stderr, "\n");
  fprintf(stderr, " !!! mystrchr is okay\n");

  ////////////////////////////////////////////////////////////////////// test intindex
  fprintf(stderr, "///////////////////////////// testing intindex\n");
  fprintf(stderr, "Looking for:");
  index = 5;
  for (i = 0; i < arrayCount; i++) {
    fprintf(stderr, " %d", intArray[index]);
    assert(index == intindex(intArray[index], intArray, arrayCount));
    index = (index + 7) % arrayCount;
  }

  fprintf(stderr, "\n");
  fprintf(stderr, "Looking for:");
  // Make sure it finds no even numbers after 2.
  for (i = 0; i < arrayCount; i++) {
    fprintf(stderr, " %d", 2 * i + 4);
    assert(intindex(2 * i + 4, intArray, arrayCount) == -1);
  }

  fprintf(stderr, "\n");
  fprintf(stderr, " !!! intindex is okay\n");
  printf("Success!\n");

  return EXIT_SUCCESS;
}

/* vim: set et ai sts=2 sw=2: */

