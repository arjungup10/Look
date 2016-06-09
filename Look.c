#include "Look.h"

#define ARGLENGTH 100

static int ListLength = 0;
static int argFlags[] = {0, 0, 0}; //d (alphanumeric) f (ignore case) t (termination char) in that order

char ParseArgs(int argc, char **argv) {
   int c;
   char tvalue = '\0';

   opterr = 0;
   while ((c = getopt (argc, argv, "dfat:")) != -1)
   switch (c) {
     case 'd':
         argFlags[0] = 1;
         break;
     case 'f':
         argFlags[1] = 1;
         break;
     case 't':
        argFlags[2] = 1;
        tvalue = optarg[0];
        break;
     case '?':
         if (optopt == 't') {
            fprintf (stderr, "Option -%c requires an argument.\n", optopt);
         }
         else {
            fprintf (stderr, "look: invalid option -- '%c'\n", optopt);
            fprintf(stderr, "usage: look [-dfa] [-t char] string [file]\n");
            exit(EXIT_FAILURE);
         }
   }
   return tvalue;
}

void ParseFile(char **argv, char **parse, char *fileName) {
   int length = 0, size = 10;
   char nextChar;
   FILE *inFile;

   if (access(fileName, F_OK) == -1) {
      printf("look: %s: No such file or directory\n", fileName);
      exit(EXIT_FAILURE);
   }

   inFile = fopen(fileName, "r");

   //Parse the contents of the file
   while ((nextChar = fgetc(inFile)) != EOF) {
     (*parse)[length++] = nextChar;
     if (length + 2 > size) {
      size *= 2;
      *parse = realloc(*parse, size * sizeof(char));
     }
   }
   (*parse)[length] = '\0';

   length = 0;
}

char **MakeList(char *parse) {
   int length = 0, listSize = 10;
   char *save = NULL, *nextLine,
    *curLine = calloc(ARGLENGTH, sizeof(char)),
    **wordList = calloc(listSize, sizeof(char*));

   nextLine = strtok_r(parse, "\n", &save);
   while (nextLine != NULL) {
      curLine = realloc(curLine, strlen(nextLine) + 1 * sizeof(char));
      strcpy(curLine, nextLine);

      if (length >= listSize) {
        listSize *= 2;
        wordList = realloc(wordList, sizeof(char *) * listSize);
      }

      wordList[length] = calloc(strlen(curLine) + 1, sizeof(char));
      strcpy(wordList[length++], curLine);

      nextLine = strtok_r(NULL, "\n", &save);
   }
   wordList[length] = NULL;
   ListLength = length - 1;
   return wordList;
}

int FindFirst(char **wordList, int mid, char *key, char tvalue) {
   int count = -1, noMatch = 0, stringIndex = 0;
   char *firstWord, *temp = calloc(5, sizeof(char));

   for (count = 1; mid + count > 0; count--) {
      temp = realloc(temp, strlen(wordList[mid + count]) + 1 * sizeof(char));
      strcpy(temp, wordList[mid + count]);
      firstWord = strtok(temp, " ");
      firstWord = CheckFlags(firstWord, tvalue);

      noMatch = 0;
      stringIndex = 0;

      while(firstWord[stringIndex] != '\0' && key[stringIndex] != '\0') {
         if (firstWord[stringIndex] != key[stringIndex]) {
            noMatch = 1;
            break;
         }
         stringIndex++;
      }
      if (firstWord[stringIndex] == '\0' && key[stringIndex] != '\0') {
         noMatch = 1;
      }

      if (noMatch) {
         return mid + count + 1;
      }
   }
   return mid;
}

int FindKey(char **wordList, char *key, char tvalue) {
   int start = 0, mid = (start + ListLength) / 2, count = 0;
   char *firstWord, *temp = calloc(5, sizeof(char));

   while (start <= ListLength) {
      temp = realloc(temp, strlen(wordList[mid]) + 1 * sizeof(char));
      strcpy(temp, wordList[mid]);
      firstWord = strtok(temp, " ");

      count = 0;
      argFlags[2] = 0;
      firstWord = CheckFlags(firstWord, tvalue);

      if (!strcmp(firstWord, key)) {
         return FindFirst(wordList, mid, key, tvalue);
      }
      else if (strcmp(firstWord, key) < 0){
         start = mid + 1;
      }
      else if (strcmp(firstWord, key) > 0) {
         ListLength = mid - 1;
      }
      mid = (start + ListLength) / 2;
   }
   return FindFirst(wordList, mid, key, tvalue);
}

void PrintResults(char **wordList, char *key, char tvalue) {
   int listCount = 0, stringIndex = 0, noMatch = 0, count = 0;
   char *firstWord, *temp = calloc(5, sizeof(char));

   listCount = FindKey(wordList, key, tvalue);
   while (wordList[listCount] != NULL) {
      temp = realloc(temp, strlen(wordList[listCount]) + 1 * sizeof(char));
      strcpy(temp, wordList[listCount]);
      firstWord = strtok(temp, " ");

      count = 0;
      if (argFlags[1]) { //check case sensitivity
         while (firstWord[count] != '\0') {
            firstWord[count] = tolower(firstWord[count]);
            count++;
         }
      }

      noMatch = 0;
      stringIndex = 0;
      while(firstWord[stringIndex] != '\0' && key[stringIndex] != '\0') {
         if (firstWord[stringIndex] != key[stringIndex]) {
            noMatch = 1;
            break;
         }
         stringIndex++;
      }

      if (firstWord[stringIndex] == '\0' && key[stringIndex] != '\0') { //Checks if the word is done but the key is not
         noMatch = 1;
      }

      if (noMatch) { //Keep printing until there is not a match
         return;
      }
      else {
         printf("%s\n", wordList[listCount]);
      }
      listCount++;
   }
}

char *CheckFlags(char *str, char tvalue) { 
   int count = 0;
   char *newStr = str, *temp = str;

   if (argFlags[2] == 1) {
      while (temp[count] != '\0') {
         if (temp[count] == tvalue) {
            if (!isalnum(tvalue)) {
               temp[count] = '\0';
            }
            else {
            temp[count + 1] = '\0';
            }
            break;
         }
         count++;
      }
   }
   temp = newStr;
   count = 0;
   if (argFlags[0]) { //alphanumeric only
      while(str[count] != '\0') {
         if(isalnum(str[count]))
            *temp++ = str[count];
         count++;
      }
      *temp = '\0';
   }
   temp = newStr;
   count = 0;
   if (argFlags[1]) { //case insensitive
      while (temp[count] != '\0') {
         temp[count] = tolower(temp[count]);
         count++;
      }
   }
   return newStr;
}

int main(int argc, char **argv) {
   char tvalue = '\0', *key = calloc(ARGLENGTH, sizeof(char)),
    *parse = calloc(10, sizeof(char)),
    *fileName = calloc(ARGLENGTH, sizeof(char)), **wordList;

   tvalue = ParseArgs(argc, argv);

   key = argv[optind];
   fileName = argv[optind + 1];

   if (optind == argc || argc < 2) {
      fprintf(stderr, "usage: look [-dfa] [-t char] string [file]\n");
      exit(EXIT_FAILURE);
   }
   else if (optind + 1 == argc) {
      fileName = "/usr/share/dict/words";
      argFlags[0] = 1;
      argFlags[1] = 1;
   }
   key = CheckFlags(key, tvalue);

   ParseFile(argv, &parse, fileName);
   wordList = MakeList(parse);
   PrintResults(wordList, key, tvalue);
   return EXIT_SUCCESS;
}
