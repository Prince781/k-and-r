// section 4.3
// ex. 4-7: write a routine ungets(s) that will push back an entire string onto
// the input. Should ungets know about buf and bufp, or should it just use
// ungetch?
#include <stdio.h>
#include <string.h>
#define MAXLINE	1024
#define BUFSIZE	100
char buf[BUFSIZE]; // buffer of buffer chars
int bufp = 0;

int getlinef(char[],char[],int);
int getch(void);
void ungetch(int);
void ungets(char[]);

int main() {
	char line[MAXLINE], delim[] = "delim";
	printf("Delimiter: %s\n", delim);
	printf("Enter delimited input: ");
	while (getlinef(line,delim,MAXLINE) != 0) {
		printf("%s\n", line);
		printf("Enter delimited input: ");
	}
	return 0;
}

// getlinef: get line with delimeter, and then the rest until '\n'
int getlinef(char ln[], char d[], int lim) {
	int i, k, c, j;
	char rest[lim];
	for (i=k=0; i<lim && d[k] != '\0'; ++i) {
		ln[i] = (c=getch());
		if (c == d[k]) ++k;
		else k = 0;
	}
	i -= k;
	ln[i] = '\0';
	for (j=0; j<lim && (c=getch()) != EOF && c != '\n'; ++j,++i)
		rest[j] = c;
	rest[j] = '\0';
	ungets(rest);
	return i;
}

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp < BUFSIZE)
		buf[bufp++] = c;
	else printf("ungetch: too many characters\n");
}

/* explanation:
 * ungets should know about bufp, but only so that it may allow ungetch to be
 * be called ONCE (after the buffer is full). Additional error messages would
 * be unnecessary; thus, ungets must know bufp so that it may allow one
 * possible call to ungetch() when bufp == BUFSIZE. ungets need not be aware of
 * buf, since ungetch takes care of stack operations.
 */
void ungets(char s[]) {
	int i, l = strlen(s);
	for (i=l-1; i >= 0 && bufp+(l-1-i) <= BUFSIZE; --i)
		ungetch(s[i]);
}
