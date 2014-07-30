// section 5.5
// ex. 5-6: rewrite, but with pointers
#include <stdio.h>

int abs(int);
char *itoa(int, char *);

int main() {
	int a = 32, b = 4, c = -45, d = 1394;
	char stra[10], strb[10], strc[10], strd[10];
	itoa(a, stra);
	itoa(b, strb);
	itoa(c, strc);
	itoa(d, strd);
	printf("a = %d = \"%s\"\n", a, stra);
	printf("b = %d = \"%s\"\n", b, strb);
	printf("c = %d = \"%s\"\n", c, strc);
	printf("d = %d = \"%s\"\n", d, strd);
	return 0;
}

int abs(int n) {
	return n*(2*(n>=0) - 1);
}

// itoa: convert n into a string s
char *itoa(int n, char *s) {
	if (n / 10)
		s = itoa(n / 10, s);
	else if (n < 0)
		*s++ = '-';
	*s++ = abs(n % 10) + '0';
	*s = '\0';
	return s;
}
