// section 4.10
// ex. 4-13: write a recursive version of the function reverse(s), which
// reverses the string s in place
#include <stdio.h>
#include <string.h>
#define MAXLINE	1024

int getlinef(char[], int);
void reverse(char[]);

int main() {
	char line[MAXLINE];
	while (getlinef(line,MAXLINE) != 0) {
		printf("String: %s\n", line);
		reverse(line);
		printf("Reversed: %s\n", line);
	}
	return 0;
}

int getlinef(char ln[], int lim) {
	int i, c;
	for (i=0; i<lim && (c=getchar()) != EOF && c != '\n'; ++i)
		ln[i] = c;
	ln[i] = '\0';
	return i;
}

void reverse(char s[]) {
	static int i = 0, len;
	if (i == 0)
		len = strlen(s);
	if (i < (len+1)/2) {
		int temp = s[len-i-1];
		s[len-i-1] = s[i];
		s[i++] = temp;
		reverse(s);
	} else i = 0;
}
