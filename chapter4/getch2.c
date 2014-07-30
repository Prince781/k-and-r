// section 4.3
// ex. 4-8: suppose that there will never be more than one character of
// pushback. Modify getch and ungetch accordingly.
#include <stdio.h>
#define MAXLINE		1024
int bufchar;
int buffered = 0;

int getlinef(char[],int);
int getch(void);
void ungetch(int);

// put back last character (neither EOF nor '\n') into input
int main() {
	char line[MAXLINE];
	while (getlinef(line,MAXLINE) != 0)
		printf("%s\n", line);
	return 0;
}

int getlinef(char ln[], int lim) {
	int i, c;
	for (i=0; (c=getch()) != EOF && c != '\n'; ++i)
		ln[i] = c;
	if (i > 1) ungetch(ln[--i]);
	ln[i] = '\0';
	return i;
}

int getch(void) {
	if (!buffered) return getchar();
	buffered = 0;
	return bufchar;
}

void ungetch(int c) {
	bufchar = c;
	buffered = 1;
}
