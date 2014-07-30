// section 2.9
// ex 2-6: write a function setbits(x,p,n,y) that returns x with the n bits that _begin_ at position p set to the rightmost n bits of y, leaving the other bits unchanged
#include <stdio.h>

int setbits(unsigned int, int, int, unsigned int);
void printb(unsigned int);
void bintostr(unsigned int, char[]);
unsigned int strtobin(char[]);

int main() {
	char str_x[] = "100000000001", str_y[] = "001110";
	unsigned int x = strtobin(str_x), y = strtobin(str_y);
	int p = 4, n = 3;
	int res = setbits(x,p,n,y);
	printf("setbits(%s,%d,%d,%s) = %d = ", str_x, p, n, str_y, res);
	printb(res);
	printf("\n");
	return 0;
}

int setbits(unsigned int x, int p, int n, unsigned int y) {
	unsigned mid = ~(~(~0u << n) << (p+1-n)); // eg 111(0n)111
	return (mid&x) | ((y << (p+1-n))& ~mid);
}

// convert binary string to number
unsigned int strtobin(char s[]) {
	unsigned int i, v = 0;
	int end = 0;
	for (end=-1; s[end+1] != '\0'; ++end);
	for (i=0; s[i] != '\0'; ++i)
		v += (s[i]-'0')<<(end-i);
	return v;
}

// bin: print binary value
void printb(unsigned int v) {
	if (v>>1 > 0) printb(v>>1);
	putchar((v&1) + '0');
}

// atobin: convert binary value into string
void bintostr(unsigned int v, char s[]) {
	int i;
	for (i=31; i>=0; --i, v>>=1)
		s[i] = (v&1) + '0';
	s[32] = '\0';
}
