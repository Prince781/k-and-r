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

int entab(char *, char *);
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
			printf("Usage: entab -[m] +[n]\n");
			argc = 0;
			break;
		}
	if (argc == 0)
		while (getlinef(in,MAXLINE) > 0) {
			entab(in, out);
			printf("%s", out);
		}
	return 0;
}

// replace string of blanks with minimum number of tabs and blanks to next stop
int entab(char *in, char *out) {
	int old_state, state, p = 0, strp;
	char *strcp = out;
	int nstop;

	old_state = state = OUT;
	for (; *in; ++p, ++in) {
		old_state = state;
		state = *in == ' ';
		
		if (old_state == OUT && state == IN) {
			strp = p;
			strcp = out;
		}
		if (old_state == IN && state == OUT)	// replace
			for (out=strcp; strp < p; ++out) {
				nstop = nextstop(strp);
				if (nstop > strp && nstop <= p) {
					*out = '\t';
					strp = nstop;
				} else {
					*out = ' ';
					strp++;
				}
			}
		*out++ = *in;
	}
	*out = '\0';
	return p;
}

// nextstop: get next tab stop position from starting position
int nextstop(int pos) {
	if (pos >= m*TAB)
		return m*TAB + n*TAB*(1 + (pos-m*TAB)/(n*TAB));	// (int)
	return m*TAB;
}
