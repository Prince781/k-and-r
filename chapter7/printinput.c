// section 7.3
// ex. 7-2: write a program that will print arbitrary input in a sensible way.
// As a minimum, it should print non-graphic characters in octal or hexadecimal
// according to local custom, and break long text lines.
#include <stdio.h>
#include <ctype.h>

#define LINELENGTH	80

int main(int argc, char *argv[]) {
	int c, ll = 0;
	while ((c = getchar()) != EOF) {
		if (ll > LINELENGTH) {
			putchar('\n');
			ll = 0;
		} else if (c == '\n')
			ll = 0;
		if (!isgraph(c) && c != ' ' && c != '\n')
			printf("%x", c);
		else printf("%c", c);
		ll++;
	}
	return 0;
}
