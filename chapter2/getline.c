// section 2.6
// ex 2-2: write a loop equivalent to the for loop above without using && or ||
#include <stdio.h>
#define MAXLINE 1024

int getline_f(char[], int);

int main() {
	char line[MAXLINE];
	int len;
	while ((len = getline_f(line, MAXLINE)) != 0)
		printf("%s [l=%d]\n", line, len);
	return 0;
}

// getline_f: based off of getline in ch 1, but with no && or ||
int getline_f(char ln[], int lim) {
	int i, c;
	for (i=0; (i<lim-1)+((c=getchar())!='\n')+(c!=EOF) == 3; ++i)
		ln[i] = c;
	ln[i] = '\0';
	return i;
}
