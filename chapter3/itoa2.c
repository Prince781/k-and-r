// section 3.6
// ex. 3-6: write a version of itoa that accepts three arguments instead of two
// the third argument is a minimum field width; the converted number must be
// padded with blanks on the left if necessary to make it wide enough
#include <stdio.h>
#include <string.h>
#define MAXLINE		1024

void itoa(int, char[], int);
void reverse(char[]);

int main() {
	char line[MAXLINE];
	int n = 3;
	itoa(n, line, 4);
	printf("%d = %s\n", n, line);
	return 0;
}

// convert integer to string, with minimum field width
void itoa(int n, char s[], int w) {
	int i, sign;
	sign = (n < 0) ? -1 : 1;
	i = 0;
	do
		s[i++] = sign*(n % 10) + '0';
	while ((n /= 10) != 0);
	if (sign < 0)
		s[i++] = '-';
	while (i < w) s[i++] = ' ';
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
