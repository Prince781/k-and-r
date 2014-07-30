// getlinef.c - chapter 4
#include <stdio.h>
#include <string.h>
// cut first n characters of str
void strcut(char str[], int n) {
	int i, l = strlen(str);
	for (i=0; i+n<l; ++i)
		str[i] = str[i+n];
	str[i] = '\0';
}

// getlinef: get line into s, return length
int getlinef(char s[], int lim) {
	int c, i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return i;
}
