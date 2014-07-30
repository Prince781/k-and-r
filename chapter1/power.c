// section 1.7 - functions
#include <stdio.h>

int power(int m, int n); // note: for function _prototypes_, using variables
	// or variable names is not necessary and need not conform to definition

/* eg. also valid
 * int power(int a, int b);
 * int power(int, int);
 */

// test power function
main() {
	int i;

	for (i=0; i<10; ++i)
		printf("%d %d %d\n", i, power(2,i), power(-3,i));
	return 0;
}

int power(int base, int n) {
	int i, p;

	p = 1;
	for (i=1; i<=n; ++i)
		p *= base;
	return p;
}
