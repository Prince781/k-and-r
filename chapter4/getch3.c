// section 4.3
// ex. 4-9: our getch and ungetch do not handle a pushed-back EOF correctly.
// Decide what their properties ought to be if an EOF is pushed back, then 
// implement your design.
#include <stdio.h>
#define BUFSIZE	100
/* In the previous version, buf is an array of characters, but EOF is a value
 * that is out of the scope of characters. Therefore, buf must be an array
 * of ints, a datatype size large enough to accomodate the value of EOF.
 * Because getchar() returns an unsigned character from stdin, an unsigned
 * char 255 will also be interpreted as an EOF (-1), but erroneously.
 */
int buf[BUFSIZE]; // buffer of chars
int bufp = 0;

int getch(void);
void ungetch(int);

int main() {
	int c;
	while ((c=getch()) != EOF)
		putchar(c);
	ungetch(EOF);
	printf("EOF encountered. Break once.\n");
	while ((c=getch()) != EOF)
		putchar(c);
	return 0;
}

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp < BUFSIZE)
		buf[bufp++] = c;
	else printf("ungetch: too many characters\n");
}
