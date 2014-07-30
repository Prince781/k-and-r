// section 2.11
// ex. 2-10: rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else
#include <stdio.h>

char lower(char);

int main() {
	int c;
	while ((c=getchar()) != EOF)
		if (c == '\n') continue;
		else printf("lowercase: %c\n", lower(c));
	return 0;
}

char lower(char c) {
	return (c >= 'A' && c <= 'Z') ? c + ('a'-'A') : c;
}
