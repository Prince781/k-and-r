// section 5.3
// ex. 5-1: as written, getint treats a + or - not followed by a digit as a 
// valid representation of zero. Fix it to push such a character back on the
// input.
#include <stdio.h>
#include <ctype.h>
#include "getch.h"

int getint(int *);

int main() {
	int num, status;
	printf("Enter integer input to parse: ");
	if ((status=getint(&num)) == EOF)
		printf("End of file\n");
	else if (!status)
		printf("Not a number\n");
	else {
		printf("N = %d\n", num);
		printf("N * 2 = %d\n", num*2);
	}
	return 0;
}

// getint: get next integer from input into *pn
// return values: 0 (not a number), EOF, or 1 (is a number)
int getint(int *pn) {
	int c, d, sign;

	while (isspace(c = getch()));
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	d = isdigit(c) ? c : getch();
	if (!isdigit(d)) {
		ungetch(c);
		// ungetch(d);
		return 0;
	}
	for (*pn = 0; isdigit(d); d = getch())
		*pn = 10 * *pn + (d - '0');
	*pn *= sign;
	if (d != EOF)
		ungetch(d);
	return d;
}
