// section 1.5
#include <stdio.h>

/* copy input to output; 2nd version */
main() {
	int c; // we use int rather than char to hold EOF + all chars

	while ((c = getchar()) != EOF)
		putchar(c);
}
