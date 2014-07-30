// section 5.6
// ex. 5-6: rewrite, but with pointers
#include <stdio.h>
#define MAXLINE		1024

int getlinef(char *, int);

int main() {
	char ln[MAXLINE];
	int len;
	printf("Enter input: ");
	while (len = getlinef(ln, MAXLINE))
		printf("input (%d chars): %s", len, ln);
	return 0;
}

int getlinef(char *s, int lim) {
	char *str = s;
	for (; s-str < lim && (*s=getchar()) != EOF && *s != '\n'; ++s);
	*(s+1) = '\0';
	return s - str;
}
