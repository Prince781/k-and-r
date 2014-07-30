// section 2.8
// ex 2-4: write an alternative version of squeeze(s1,s2) that deletes each character in s1 that matches _any_ character in the string s2
#include <stdio.h>
#define MAXLINE 1024

void squeeze(char[], char[]);
int getline_f(char[], int);

int main() {
	char line[MAXLINE], ptrn[MAXLINE];
	printf("Enter a string of characters to parse: ");
	getline_f(line, MAXLINE);
	printf("Remove chars: ");
	while (getline_f(ptrn, MAXLINE) != 0) {
		squeeze(line, ptrn);
		printf("\tUpdate: %s\n", line);
		printf("Remove chars: ");
	}
	return 0;
}

void squeeze(char ln[], char ptrn[]) {
	int i, j, k, match = 0;
	for (i=j=0; ln[i] != '\0'; ++i, match=0) {
		for (k=0; ptrn[k] != '\0'; ++k)
			if (ptrn[k] == ln[i]) {
				match = 1;
				break;
			}
		if (!match)
			ln[j++] = ln[i];
	}
	ln[j] = '\0';
}

int getline_f(char ln[], int lim) {
	int i, c;
	for (i=0; i<lim && (c=getchar()) != '\n' && c != EOF; ++i)
		ln[i] = c;
	ln[i] = '\0';
	return i;
}
