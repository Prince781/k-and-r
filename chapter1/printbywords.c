// section 1.5.4
// ex 1-12
// write a program that prints its input one word per line
#include <stdio.h>

main() {
	int c;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t')
			putchar('\n');
		else putchar(c);
	}
}
