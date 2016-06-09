NAME
	look - displays lines within a sorted file if the first word of the line matches the given string

USAGE
	look [-df] [-t termchar] string [file]

DESCRIPTION
	The look program reads in a file and will display to the console any lines that begin with the given string using a binary search
	The input file must be sorted for look to be effective
	In the case an input file is not given, look will default to the file usr/share/dict/words with the flags -d and -f applied
	Look requires Look.c and Look.h to compile correctly 

FLAGS
	-d	Only alphanumeric characters are compared
	-f	Ignores case for the given string and the input file
	-t	accepts a character, where only the characters in the string up to the given character are compared

RETURN VALUE
	Look exits with EXIT_SUCCESS if successful, else it exits with EXIT_FAILURE in the event of an error