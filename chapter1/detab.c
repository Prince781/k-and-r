// section 1.10
// ex 1-20: write a program that replaces tabs with spaces,
// using the proper number of spaces for each column
#include <stdio.h>
#define TABLENGTH	8	// 8 spaces per tab
#define MAXLINE		1024

int getline_f(char[], int);
int detab(char[], char[]);

int main() {
	int len = 0, len2 = 0;			// for copying
	char line[MAXLINE], nline[MAXLINE];	// for copying
	
	while ((len = getline_f(line, MAXLINE)) != 0) {
		len2 = detab(line, nline);
		printf("%s", nline);
	}
	
	return 0;
}

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

// detab: remove tabs and replace with spaces, retaining alignment
int detab(char ln[], char nln[]) {
	int p = -1, p2 = -1; // position
	
	while (ln[++p] != '\0') {
		int s = 0; // number of spaces
		if (ln[p] == '\t')
			s = TABLENGTH - (p2+1)%TABLENGTH;	
		else nln[++p2] = ln[p];

		int i;
		for (i=0; i<s; ++i)
			nln[++p2] = ' ';
	}

	nln[++p2] = '\0';

	return p2;
}
