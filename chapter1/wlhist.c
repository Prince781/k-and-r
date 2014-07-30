// section 1.6
// ex 1-13
// write a program to print histogram of word lengths
#include <stdio.h>

#define IN	1	// in word
#define OUT	0	// out of word

main() {
	int c, i, nc = 0, status = OUT;

	int wordlengths[512];

	for (i=0; i<512; i++)
		wordlengths[i] = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			status = OUT;
			if (nc != 0) {
				++wordlengths[nc];
				nc = 0;
			}
		} else if (status == OUT) {
			status = IN;
			nc = 1; // reset
		} else ++nc;
	}

	++wordlengths[nc];

	for (i=1; i<512; i++)
		if (wordlengths[i] > 0) {
			int j;
			for (j=0; j<wordlengths[i]; j++)
				putchar('=');
			printf("(%d chars)\n", i);
		}
}
