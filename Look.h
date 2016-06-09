#ifndef LOOK
#define LOOK

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>

//Finds the flags that are to be used
char ParseArgs(int, char **);

//Parse the data in the given file or default dictionary
void ParseFile(char **, char **, char *);

//Creates the list of words to be searched from the dictionary
char **MakeList(char *);

//Binary Search will not give us the first occurrence in list
//so we have to traverse up the list until we don't find a match
int FindFirst(char **, int, char *, char);

//Uses a binary search to find the key
//which is the lowerbound of the words to be printed
int FindKey(char **, char *, char);

//Prints all the results of the search to the screen
void PrintResults(char **, char *, char);

//Checks which flags are to be used and modifies the key
//wordlist to be searched
char *CheckFlags(char *, char);

#endif
