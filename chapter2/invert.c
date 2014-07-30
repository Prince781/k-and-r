// section 2.9
// ex 2-7: write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (1 to 0 and vice versa), leaving the others unchanged
#include <stdio.h>

unsigned invert(unsigned, int, int);
unsigned strtobin(char[]);
void printb(unsigned);

int main() {
	char str_x[] = "110111010101";
	unsigned x = strtobin(str_x);
	int p = 7, n = 4;
	int res = invert(x,p,n);
	printf("invert(%s, %d, %d) = %d = ", str_x, p, n, res);
	printb(res);
	printf("\n");
	return 0;
}

unsigned invert(unsigned x, int p, int n) {
	unsigned mid = ~(~0 << n) << (p+1-n); // eg 000(1n)000 
	return (~(x&mid) & mid) | (x & ~mid);
}

unsigned strtobin(char s[]) {
	unsigned i, v = 0;
	int end = 0;
	for (end=-1; s[end+1] != '\0'; ++end);
	for (i=0; s[i] != '\0'; ++i)
		v += (s[i]-'0')<<(end-i);
	return v;
}

void printb(unsigned v) {
	if (v>>1 > 0) printb(v>>1);
	putchar((v&1) + '0');
}

