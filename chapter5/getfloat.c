// section 5.3
// ex. 5-2: write getfloat, the floating-point analog of getint. What type does
// getfloat return as its function value?
#include <stdio.h>
#include <ctype.h>
#include "getch.h"

int getfloat(double *);

int main() {
	int status;
	double num;
	printf("Enter float input to parse: ");
	if ((status=getfloat(&num)) == EOF)
		printf("End of file\n");
	else if (!status)
		printf("getfloat: not a float\n");
	else {
		printf("N = %f\n", num);
		printf("N * 2 = %f\n", num*2);
	}
	return 0;

}

// getfloat: parse float, return 0 (not a number), EOF, or positive (a number)
int getfloat(double *pn) {
	int c, d;
	double mag;	// magnitude

	while (isspace(c = getch()));
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	d = isdigit(c) ? c : getch();
	if (!isdigit(d)) {
		ungetch(c);
		ungetch(d);
		return 0;
	}
	mag = (c == '-') ? -1 : 1;
	for (*pn = 0; isdigit(d); d = getch())
		*pn = 10 * *pn + (d - '0');
	if (d == '.')
		for (; isdigit(d=getch()); mag /= 10)
			*pn = 10 * *pn + (d - '0');
	*pn *= mag;
	if (d != EOF)
		ungetch(d);
	return d;
}
