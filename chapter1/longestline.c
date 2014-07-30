// section 1.9 - character arrays
// write a program that reads a set of text lines and prints the longest
#include <stdio.h>
#define MAXLINE	1000	// maximum input line size

int getline_f(char[], int);
void copy(char[], char[]);

int main() {
	int len;		// current line length
	int max;		// max length
	char line[MAXLINE];	// current line
	char longest[MAXLINE];	// longest line saved

	max = 0;
	while ((len = getline_f(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0)	// there was a line
		printf("%s", longest);
	return 0;
}

// getline_f: read a line into s; return length
int getline_f(char s[], int lim) {
	int c, i;
	
	for (i=0; i<lim && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c; // fill s
	if (c == '\n') {
		s[i] = c;
		++i; // increase length
	}
	s[i] = '\0'; // null terminate
	return i;
}

// copy: copy 'from' into 'to', assuming 'to' is big enough
void copy(char to[], char from[]) {
	int i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
