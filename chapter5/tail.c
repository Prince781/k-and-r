// section 5.10
// ex. 5-13: write the program tail, which prints the last n lines of its
// input. By default, n is 10, let us say, but it can be changed by an optional
// argument, so that
//	tail -n
// prints the last n lines. The program should behave rationally no matter how
// unreasonable the input or the value of n. Write the program so it makes the
// best use of available storage; lines should be stored as in the sorting
// program of Section 5.6, not in a two-dimensional array of fixed size.
#include <stdio.h>
#include <string.h>
#include "getlinef.h"
#include "alloc.h"

#define MAXLINES	1000	// maximum number of lines
#define MAXLEN		1000	// maximum individual line length

int readlines(char *[], int, int *);

int main(int argc, char *argv[]) {
	char *lineptr[MAXLINES];
	int bufsize = 10, nlines = 0, i;
	int pos;	// wraparound position
	while (--argc > 0)
		switch ((*++argv)[0]) {
		case '-':
			bufsize = atoi(++argv[0]);
			if (bufsize > MAXLINES)
				bufsize = MAXLINES;
			break;
		default:
			printf("Usage: tail -n\n");
			argc = 0;
			break;
		}
	if (argc != 0) return -1;
	nlines = readlines(lineptr, bufsize, &pos);
	for (i=0; i<nlines; ++i)
		printf("%s\n", lineptr[(++pos)%nlines]);
	return 0;
}

// readlines: read lines; update in buffer
int readlines(char *lptr[], int bufsize, int *pos) {
	if (bufsize == 0)
		return 0;
	int nlines = 0, len, lastlen = 0;
	char temp[MAXLEN], *p, **st = lptr;
	
	*pos = 0;
	while ((len = getlinef(temp,MAXLEN)) > 0) {
		if (lastlen > 0) {
			adelete(*lptr, lastlen);
			while (lptr < st + bufsize)
				*lptr++ -= lastlen;
			lptr = st;
			lastlen = 0;
		}
		if ((p = alloc(len)) == NULL) {
			printf("Out of storage.\n");
			return nlines;
		} else {
			temp[len-1] = '\0';	// delete newline
			strcpy(*lptr = p, temp);
			*pos = lptr - st;
			lptr = st + (1+lptr-st)%bufsize;
			if (lptr - st == 0)
				lastlen = len;
			nlines = (nlines >= bufsize) ? bufsize : nlines+1;
		}
	}
	
	return nlines;
}
