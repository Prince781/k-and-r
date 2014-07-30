// readlines example
#include "getlinef.h"
#include "alloc.h"
#include <stdio.h>
#include <string.h>

#define MAXLINES	5000	// maximum number of lines
#define MAXLEN		1000	// maximum length of any input line

int readlines(char *[], int);

int main() {
	char *lines[MAXLEN];
	printf("Enter input below:\n");
	int n = readlines(lines, MAXLINES);
	while (--n >= 0)
		printf("lines[%d] = %s\n", n, lines[n]);
	return 0;
}

// read from stdin and return number of lines, or -1 if input goes over
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];
	
	nlines = 0;
	while ((len = getlinef(line,MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0'; // delete newline
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}
