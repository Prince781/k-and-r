// section 1.10
// ex 1-22: write a C program to "fold" long input lines into two or more
// shorter lines after the last non-blank character that occurs before the nth
// column of input
#include <stdio.h>
#define MAXLINE		1024
#define TABLEN		8
#define OUT		0	// outside of word; inside whitespace
#define IN		1	// inside of word
#define COLUMN_WIDTH	60

int getline_f(char[], int);
int fold(char[], char[], int);

int main() {
	int len = 0, nlen = 0;
	char line[MAXLINE], nline[MAXLINE];

	while ((len = getline_f(line, MAXLINE)) != 0) {
		nlen = fold(line, nline, COLUMN_WIDTH);
		printf("%s", nline);
	}

	return 0;
}

int getline_f(char ln[], int lim) {
	int c, l;
	for (l=0; (c=getchar()) != EOF && c != '\n'; ++l)
		if (l < lim)
			ln[l] = c;

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

// fold: take a line and word-wrap it
int fold(char ln[], char nln[], int maxcol) {
	int p = -1, p2 = -1, state = OUT;
	int i;
	int col = 0, str = -1, old_state;
	while ((nln[++p2] = ln[++p]) != '\0') {
		old_state = state;
		state = (nln[p2] != '\t' && nln[p2] != '\n' && nln[p2] != ' ');
		
		if (old_state == IN && state == OUT)
			str = p2;
		col += (nln[p2] == '\t' ? TABLEN-col%TABLEN : 1);
		
		if (nln[p2] == '\n')
			col = 0;
		else if (col >= maxcol) {
			str = (str == -1 ? p2 : str);
			col = 0;
			for (i=p2+1; i>str; i--) {	// shift right
				nln[i] = nln[i-1];
				col += (nln[str + (p2+2)-i]=='\t'
					?TABLEN-col%TABLEN:1);
			}
			nln[str] = '\n';
			++p2;
			str = -1;
			state = OUT;
		}
	}
	
	return p2;
			
}
