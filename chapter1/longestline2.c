// section 1.9
// ex 1-16: revise longest line program to correctly print the length of
// arbitrarily-long input lines, and as much as possible of the text
#include <stdio.h>
#define MAXLINE	10	// max line size

int getline_f(char[], int);
void copy(char[], char[]);

int main() {
	int len, max;
	char line[MAXLINE], longest[MAXLINE];

	len = max = 0;
	while ((len = getline_f(line, MAXLINE)) != 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}

	if (max > 0)
		printf("Longest (l=%d): %s", max, longest);
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

void copy(char to[], char from[]) {
	int i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
