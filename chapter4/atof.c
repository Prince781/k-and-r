// section 4.2
// ex. 4-2: extend atof to handle scientific notation of the form 123.45e-6,
// where a floating-point number may be followed by e or E and an optionally
// signed exponent
#include <stdio.h>
// include getlinef.c
#define MAXLINE		1024

double atof(char[]);

int main() {
	char line[MAXLINE];
	printf("Enter scientific notation value: ");
	while (getlinef(line) > 0) {
		printf("Value = %3.5f\n", atof(line));
		printf("Enter scientific notation value: ");
	}
	printf("\n");
	return 0;
}

// convert string s to floating-point, accounting for scientific notation
double atof(char s[]) {
	double sign, val = 0, pow = 0, pow2 = 0, esign;
	int i = -1;
	while (isspace(s[++i])); // skip whitespace
	sign = s[i] == '-' ? -1 : 1;
	if (s[i] == '-') ++i;
	while (isdigit(s[i]))
		val = 10*val + (s[i++] - '0');
	if (s[i] == '.')
		for (i=i+1; isdigit(s[i]); ++i, --pow)
			val = 10*val + (s[i] - '0');
	val *= sign;
	switch (s[i]) {
	case 'e': case 'E':
		esign = s[i+1] == '-' ? -1 : 1;
		if (s[i+1] == '-' || s[i+1] == '+') ++i;
		while (isdigit(s[++i]))
			pow2 = 10*pow2 + esign*(s[i]-'0');
		break;
	}
	esign = (pow+=pow2) < 0 ? -1 : 1;
	for (pow; pow != 0; pow -= esign)
		val *= esign < 0 ? 0.1 : 10;
	return val;
}
