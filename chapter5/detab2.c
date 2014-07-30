// section 5.10
// ex. 5-12: extend entab and detab to accept the shorthand:
//	entab -m +n
// to mean tab stops every n columns, starting at column m. Choose convenient
// (for the user) default behavior.
#include <stdio.h>
#include <stdlib.h>
#include "getlinef.h"

#define MAXLINE		1024	// maximum line length
#define IN		1	// inside whitespace
#define OUT		0	// outside whitespace
#define TAB		8	// tab length

static int m = 0,		// starting column
	   n = 1;		// column skips

int detab(char *, char *);
int nextstop(int);

int main(int argc, char *argv[]) {
	char in[MAXLINE], out[MAXLINE];
	while (--argc > 0)
		switch ((*++argv)[0]) {
		case '-':
			m = atoi(++argv[0]);
			break;
		case '+':
			n = atoi(++argv[0]);
			break;
		default:
			printf("Usage: detab -[m] +[n]\n");
			argc = 0;
			break;
		}
	if (argc == 0)
		while (getlinef(in,MAXLINE) > 0) {
			detab(in, out);
			printf("%s", out);
		}
	return 0;
}

// detab: remove tabs and replace with spaces, retaining alignment
int detab(char *in, char *out) {
	int gap = 0;
	char *outp = out;
	while (*out++ = *in++)
		if (in[-1] == '\t') {
			gap = nextstop(--out-outp) - (out-outp);
			while (--gap >= 0)
				*out++ = ' ';
		}
	return --out - outp;
}

// nextstop: get next tab stop position from starting position
int nextstop(int pos) {
	if (pos >= m*TAB)
		return m*TAB + n*TAB*(1 + (pos-m*TAB)/(n*TAB));	// (int)
	return m*TAB;
}
