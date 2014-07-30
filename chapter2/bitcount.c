// section 2.10
// ex. 2-9: in a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Explain why. Use this observation to write a faster version of bitcount
#include <stdio.h>

/* explanation:
 * If x is any arbitrary value, subtracting 1 will cause the right-most bit to 
 * "turn over" to a 0. This is because 1 is the maximum digit value in a radix
 * of 2, and thus any 1 followed by n 0s becomes a 0 followed by n 1s. The
 * bitwise AND of x and x_new will always set the rightmost 1 to 0, until the
 * entire number is 0. Therefore, an efficient bit counting algorithm should
 * simply call x&=(x-1) until x == 0, returning the number of iterations.
 */

int bitcount(unsigned);
unsigned strtobin(char[]);

int main() {
	char str_x[] = "110110111";
	unsigned x = strtobin(str_x);
	printf("bitcount(%s) = %d\n", str_x, bitcount(x));
	return 0;
}

int bitcount(unsigned x) {
	int c;
	for (c=0; x > 0; ++c)
		x &= (x-1);
	return c;
}

unsigned strtobin(char s[]) {
	unsigned i, v = 0u;
	int end = 0;
	for (end=-1; s[end+1] != '\0'; ++end);
	for (i=0; s[i] != '\0'; ++i)
		v += (s[i]-'0')<<(end-i);
	return v;
}

