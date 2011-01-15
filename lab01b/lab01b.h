/**
 * @file
 * <pre> CPE 357 Winter 2009
 * -------------------
 *
 * Header file for Lab 1 B.
 *
 * Last Modified: Mon Jan  5 19:57:31 PST 2009</pre>
 * @author Kevin O'Gorman
 */

#ifndef LAB1B_H
#define LAB1B_H

/// Reimplementation of strchr.
char *mystrchr(char *s, char c);

/// Find the index of an entry in an array of ints, if it's there at all.
int intindex(int needle, int haystack[], int haystacksize);

#endif
/* vim: set et ai sts=2 sw=2: */

