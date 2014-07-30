// section 5.6
// ex. 5-4: write the function strend(s,t), which returns 1 if the string t
// occurs at the end of the string s, and zero otherwise
#include <stdio.h>

int strend(char *, char *);

int main() {
	char str[] = "This is a string.", end[] = "a string.";
	if (strend(str, end))
		printf("\"%s\" is at the end of \"%s\"\n", end, str);
	else printf("\"%s\" is not at the end of \"%s\"\n", end, str);
	return 0;
}

// return 1 if t is at end of s, and 0 if not
int strend(char *s, char *t) {
	char *oldp = t;
	do {
		t = (*s == *t) ? t+1 : oldp;
	} while (*s++);
	return ! *t;
}
