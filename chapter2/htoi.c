// section 2.7
// ex 2-3: write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value
// the allowable digits are 0 through 9, a through f, and A through F
#include <stdio.h>
#define MAXLINE 1024

int htoi(char[]);
int getline_f(char ln[], int lim);

int main() {
	char line[MAXLINE];
	printf("Convert hexadecimal to decimal.\n");
	while (getline_f(line, MAXLINE) != 0)
		printf("%s = %d\n", line, htoi(line));
	return 0;
}

int getline_f(char ln[], int lim) {
	int i, c;
	for (i=0; (i<lim-1)+((c=getchar())!='\n')+(c!=EOF) == 3; ++i)
		ln[i] = c;
	ln[i] = '\0';
	return i;
}

int htoi(char s[]) {
	int v = 0, i = 0;
	for (i=0; (s[i]=tolower(s[i])) != '\0'; ++i)
		if (s[i] >= '0' && s[i] <= '9')
			v = v*16 + (s[i] - '0');
		else if (s[i] >= 'a' && s[i] <= 'f')
			v = v*16 + 10 + (s[i] - 'a');
		// else if (s[i] >= 'A' && s[i] <= 'F')
		//	v = v*16 + 10 + (s[i] - 'A');
		else if (i == 1 && (s[i] == 'x'||s[i] == 'X'))
			v = 0;
		else break;
	return v;
}
