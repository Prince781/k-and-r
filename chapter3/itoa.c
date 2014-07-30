// section 3.6
// ex. 3-4: in a two's complement number representation, our version of itoa
// does not handle the largest negative number, that is, the value of n equal to
// -(2^(wordsize-1)). Explain why not. Modify it to print that vlaue correctly,
// regardless of the machine on which it runs.

#include <stdio.h>
#include <string.h>
#define MAXLINE		1024

void reverse(char[]);
void itoa(int, char[]);

int main() {
	char str[MAXLINE];
	int n = ~0u - (~0u >> 1);
	itoa(n, str);
	printf("The string representation of %d is %s\n", n, str);
	return 0;
}

/* explanation:
 * For any n-bit signed integer, the range of negative values is from -1 to 
 * -(2^(n-1)), and the range of non-negative values is from 0 to 2^(n-1) -1.
 * Therefore, in overflowing, a positive value such as 2^(n-1) is represented
 * as -(2(^n-1)). In the example, the expression n = -n will fail to set n to
 * be positive, and the while loop will terminate prematurely.
 */
void itoa(int n, char s[]) {
	int i, sign;
	sign = (n < 0) ? -1 : 1;
	i = 0;
	do
		s[i++] = sign*(n % 10) + '0';
	while ((n /= 10) != 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

// reverse string
void reverse(char s[]) {
	int i, n = strlen(s);
	int c;
	for (i=0; i<(n+1)/2; ++i) {
		c = s[i];
		s[i] = s[n-i-1];
		s[n-i-1] = c;
	}
}
