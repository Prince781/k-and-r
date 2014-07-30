// section 1.9
// ex 1-18: write a program to remove trailing blanks and tabs from each line
// of input, and to delete entirely blank lines
#include <stdio.h>
#define MAXLINE	2048	// maximum line size

int getline_f(char[], int);	// returns length of string
int copy(char[], char[]);	// returns length of new string

int main() {
	int len = 0, olen = 0;
	char line[MAXLINE], output[MAXLINE];
	
	while ((len = getline_f(line, MAXLINE)) != 0) {
		olen = copy(output, line);
		printf("Line (l=%d; shaved %d chars): %s\n",
			olen, len - olen, output);
		// note: \n is shaved off, but printed anyway artificially
	}
	
	return 0;
}

// getline_f: get line from input, with limit
int getline_f(char ln[], int lim) {
	int c, l;
	for (l=0; l<lim && (c=getchar()) != EOF && c != '\n'; ++l)
		ln[l] = c;
	
	if (c != '\n' && c != EOF)
		while ((c=getchar()) != EOF && c != '\n')
			++l;

	if (l >= lim-1) {
		ln[lim-1] = '\0';
		ln[lim-2] = '\n';
		return ++l;
	}

	if (c == '\n') {
		ln[l] = c;
		++l;
	}

	ln[l] = '\0';
	return l;
}

int copy(char to[], char from[]) {
	int i = 0, space = 0, l = 0; // 1 == in

	while ((to[i] = from[i]) != '\0') {
		space = (to[i] == ' ' || to[i] == '\t' || to[i] == '\n');
		++i;
		if (!space) l = i;
	}

	to[l] = '\0';

	return l;
}
