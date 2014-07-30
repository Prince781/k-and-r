// section 2.9
// ex. 2-8: write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions
#include <stdio.h>

unsigned rightrot(unsigned, int);
unsigned strtobin(char[]);
void printb(unsigned);

int main() {
	char str_x[] = "1010011101";
	unsigned x = strtobin(str_x);
	int n = 4, res = rightrot(x,n);
	printf("rightrot(%s,%d) = %d = ", str_x, n, res);
	printb(res);
	printf("\n");
	return 0;
}

// rightrot: rotate x to the right by n bit positions
unsigned rightrot(unsigned x, int n) {
	unsigned offset = ~(~0u >> n) ^ ~(~0u >> (n+1)),
		 mid = ~(~0u << n);
	return (x >> n) + (x&mid)*offset;
}

unsigned strtobin(char s[]) {
	unsigned i, v = 0u;
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
