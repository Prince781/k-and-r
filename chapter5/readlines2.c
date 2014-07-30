// section 5.6
// ex. 5-7: rewrite readlines to store lines in an array supplied by main,
// rather than calling alloc to maintain storage. How much faster is the
// program?
#include "getlinef.h"
#include <stdio.h>

#define MAXLEN		1000	// maximum line length
#define MAXLINES	1000	// maximum number of lines

int readlines(char *lineptr[], char *buf, int maxlines);

int main() {
	char *lines[MAXLINES], buffer[MAXLEN*MAXLINES];
	int n = readlines(lines, buffer, MAXLINES);
	while (--n >= 0)
		printf("lines[%d] = %s\n", n, lines[n]);
	return 0;
}

int readlines(char *lineptr[], char *buf, int maxlines) {
	int len = -1, nlines = -1;
	while (++nlines < maxlines
		&& (len = getlinef(lineptr[nlines]=(buf+=len+1),MAXLEN)) > 0)
		lineptr[nlines][len-1] = '\0';	// remove '\n'
	return nlines;
}
