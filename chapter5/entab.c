// section 5.10
// ex. 5-11: modify the programs entab and detab (written as exercises in
// Chapter 1) to accept a list of tab stops as arguments. Use the default tab
// settings if there are no arguments.
#include <stdio.h>
#include <stdlib.h>
#include "getlinef.h"

#define MAXLINE		1024	// maximum line length
#define IN		1	// inside whitespace
#define OUT		0	// outside whitespace
#define MAXSTOPS	100	// maximum number of tab stops
#define TABLENGTH	8

static int tabstop[MAXSTOPS] = {0};	// tab stop positions

int entab(char *, char *, int);
int nextstop(int, int);

int main(int argc, char *argv[]) {
	char in[MAXLINE], out[MAXLINE];
	int *tabp = tabstop;
	while (--argc > 0 && tabp < tabstop + MAXSTOPS)
		*tabp++ = atoi(*++argv);
	while (getlinef(in,MAXLINE) > 0) {
		entab(in, out, tabp - tabstop);
		printf("%s", out);
	}
	return 0;
}

// replace string of blanks with minimum number of tabs and blanks to next stop
int entab(char *in, char *out, int stopsize) {
	int old_state, state, p = 0, strp;
	char *strcp = out;
	int nstop;

	old_state = state = OUT;
	for (; *in; ++in) {
		old_state = state;
		state = *in == ' ';
		
		if (old_state == OUT && state == IN) {
			strp = p;
			strcp = out;
		}
		if (old_state == IN && state == OUT)	// replace
			for (out=strcp; strp < p; ++out) {
				nstop = nextstop(strp, stopsize);
				if (nstop > strp && nstop <= p) {
					*out = '\t';
					strp = nstop;
				} else {
					*out = ' ';
					strp++;
				}
			}
		++p;
		*out++ = *in;
	}
	*out = '\0';
	return p;
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
