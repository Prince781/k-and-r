// section 4.10
// ex. 4-12: adapt the ideas of printd to write a recursive version of itoa;
// that is, convert an integer into a string by calling a recursive routine
#include <stdio.h>
#define VALSIZE	6
void itoa(int, char[]);

int main() {
	char line[100];
	int vals[VALSIZE] = {-32, 4, 10, 13, 12, 0};
	int p;
	for (p=0; p<VALSIZE; ++p) {
		itoa(vals[p], line);
		printf("%d converts to %s\n", vals[p], line);
	}
	return 0;
}

// itoa: convert integer n into string s
void itoa(int n, char s[]) {
	static int i = -1;
	if (n < 0) {
		n = -n;
		s[i = 0] = '-';
	}
	if (n >= 10)
		itoa(n / 10, s);
	else if (!(i==0 && s[i]=='-'))
		i = -1;
	s[++i] = (n%10) + '0';
	s[i+1] = '\0';
}
