// section 1.10
// print longest line (using extern)
#include <stdio.h>

#define MAXLINE	1000	// maximum input line size

int max;		// maximum length seen so far
char line[MAXLINE]; 	// current input line
char longest[MAXLINE];	// longest line saved here

int getline_f(void);
void copy(void);

// print longest input line; specialized version
main() {
	int len;
	extern int max;		// note: extern definitions here are redundant
	extern char longest[];	// note: extern definitions here are redundant

	max = 0;
	while ((len = getline_f()) > 0)
		if (len > max) {
			max = len;
			copy();
		}
	if (max > 0)	// there was a line
		printf("%s", longest);
	return 0;
}

// getline_f: specialized version
int getline_f(void) {
	int c, i;
	extern char line[];	// note: extern definitions here are redundant

	for (i=0; i<MAXLINE-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

// copy: specialized version
void copy(void) {
	int i;
	extern char line[], longest[];	// note: extern definitions here are
					// redundant. only for external files
					// is _extern_ needed
	i = 0;
	while ((longest[i] = line[i]) != '\0')
		++i;
}
