// section 2.8
// ex 2-5: write the function any(s1,s2), which returns the first location in the string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2
#include <stdio.h>
#define MAXLINE 1024

int getline_f(char[], int);
int any(char[], char[]);

int main() {
	char line[MAXLINE], ptrn[MAXLINE];
	printf("Enter a string: ");
	getline_f(line, MAXLINE);
	printf("Enter characters to search for: ");
	while (getline_f(ptrn, MAXLINE) != 0) {
		printf("First char occurrence at position %d.\n",
			any(line,ptrn));
		printf("Enter characters to search for: ");
	}
	return 0;
}

int getline_f(char ln[], int lim) {
	int i, c;
	for (i=0; (i<lim-1)+((c=getchar())!='\n')+(c!=EOF) == 3; ++i)
		ln[i] = c;
	ln[i] = '\0';
	return i;
}

int any(char ln[], char ptrn[]) {
	int i, j;
	for (i=0; ln[i] != '\0'; ++i)
		for (j=0; ptrn[j] != '\0'; ++j)
			if (ptrn[j] == ln[i])
				return i;
	return -1;
}
