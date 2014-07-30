// section 3.6
// ex. 3-5: write the function itob(n,s,b) that converts the integer n into a
// base b character representation in the string s. In particular, itob(n,s,16)
// formats n as a hexadecimal integer in s.
#include <stdio.h>
#include <string.h>
#define MAXLINE		1024

void itob(int, char[], int);
void reverse(char[]);

int main() {
	char line[MAXLINE];
	int vals[9] = {30, 4, -10, -3, 255, 8, 240, 22, 134};
	int i, b=8;
	for (i=0; i<9; ++i) {
		itob(vals[i], line, b);
		printf("%d = %s (base %d)\n", vals[i], line, b);
	}
	return 0;
}

void itob(int n, char s[], int b) {
	int sign = (n < 0) ? -1 : 1;
	int i = 0, c;
	do {
		c = sign*(n%b) + '0';
		if (c > '9')
			c += 'A'-'9'-1;
		s[i++] = c;
	} while ((n /= b) != 0);
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
