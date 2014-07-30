// section 5.10
// ex. 5-11: modify the programs entab and detab (written as exercises in
// Chapter 1) to accept a list of tab stops as arguments. Use the default tab
// settings if there are no arguments.
#include <stdio.h>
#include <stdlib.h>
#include "getlinef.h"

#define MAXLINE		1024	// maximum line length
#define IN		1	// inside tabs
#define OUT		0	// outside tabs
#define MAXSTOPS	100	// maximum number of tab stops
#define TABLENGTH	8

int detab(char *, char *, int);
int nextstop(int, int);

static int tabstop[MAXSTOPS] = {0};	// tab stop positions

int main(int argc, char *argv[]) {
	char in[MAXLINE], out[MAXLINE];
	int *tbp = tabstop;
	while (--argc > 0 && tbp < tabstop + MAXSTOPS)
		*tbp++ = atoi(*++argv);
	while (getlinef(in,MAXLINE) > 0) {
		detab(in, out, tbp - tabstop);
		printf("%s", out);
	}
	return 0;
}

// detab: remove tabs and replace with spaces, retaining alignment
int detab(char *in, char *out, int stops) {
	int gap = 0;
	char *outp = out;
	while (*out++ = *in++)
		if (in[-1] == '\t') {
			gap = nextstop(--out-outp, stops) - (out-outp);
			while (--gap >= 0)
				*out++ = ' ';
		}
	return --out - outp;
}

// nextstop: get next tab stop position from starting position
int nextstop(int pos, int size) {
	int *tbp = tabstop;
	if (size) {
		while (tbp < tabstop+size-1 && *tbp <= pos) ++tbp;
		return *tbp;
	}	// else: assume default stop
	return TABLENGTH * (pos/TABLENGTH + 1);
}
