// section 4.1
// ex. 4-1: write the function strrindex(s,t), which returns the position
// of the _rightmost_ occurrence of t in s, or -1 if there is none.
#include <stdio.h>
#include <string.h>
// #include "getlinef.c" // manually include this on compilation (cc)
#define MAXLINE 1024

int strrindex(char[], char[]);

int main() {
	char line[MAXLINE], pattern[] = "ing";
	printf("Enter a test string: ");
	while (getlinef(line, MAXLINE) != 0) {
		printf("Found %s at position %d.\n",
			pattern, strrindex(line,pattern));
		printf("Enter a test string: ");
	}
	return 0;
}

// strrindex: get position of rightmost occurrence of t in s
int strrindex(char s[], char t[]) {
	int i, j, k;
	int slen = strlen(s);
	for (i=slen-1; i>=0; --i) {
		for (j=i,k=0; j<slen && s[j]==t[k]; ++j,++k);
		if (t[k] == '\0') return i;
	}
	return -1;
}
