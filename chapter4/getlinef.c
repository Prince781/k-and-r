// getlinef.c - chapter 4
#include <stdio.h>

// getlinef: get line into s, return length
int getlinef(char s[], int lim) {
	int c, i = 0;

	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
