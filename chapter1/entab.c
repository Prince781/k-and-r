// section 1.10
// ex 1-21: write a program that replaces tabs with spaces and minimum number
// of tabs required to retain the spacing
#include <stdio.h>
#define TABLENGTH	8	// 8 spaces per tab
#define MAXLINE		1024
#define IN		1
#define OUT		0

int getline_f(char[], int);
int entab(char[], char[]);

int main() {
	int len, nlen; // length of lines
	char line[MAXLINE], nline[MAXLINE];

	while ((len = getline_f(line, MAXLINE)) != 0) {
		nlen = entab(line, nline);
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

// entab: replace strings of blanks by minimum number of tabs and blanks
int entab(char ln[], char nln[]) {
	int p = -1, p2 = -1, state = OUT, str = -1, end = -1;
	
	int i, old_state;
	while (ln[++p] != '\0') {
		old_state = state;
		state = (ln[p] == ' ');

		if (old_state == OUT && state == IN)
			str = end = p;
		else if (state == IN)
			end = p;

		// copy tab/space characters to nln
		if (old_state == IN && state == OUT) {
			if (str + TABLENGTH-str%TABLENGTH < end) {
				nln[++p2] = '\t';
				str += TABLENGTH-str%TABLENGTH;
			}
			for (str; str+TABLENGTH < end; str+=TABLENGTH)
				nln[++p2] = '\t';
			for (str; str<=end; str++)
				nln[++p2] = ' ';
			str = end = -1;
		}
		
		if (state == OUT)
			nln[++p2] = ln[p];
	}

	nln[++p2] = '\0';

	return p2;
}
