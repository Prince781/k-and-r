#include <stdio.h>
#include "getch.h"

#define BUFSIZE	1000

static int buf[BUFSIZE]; // buffer of chars
static int bufp = 0;

int getch(void);
void ungetch(int);

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp < BUFSIZE)
		buf[bufp++] = c;
	else printf("ungetch: too many characters\n");
}
