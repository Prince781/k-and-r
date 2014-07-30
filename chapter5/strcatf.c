// section 5.6
// ex. 5-3: write a pointer version of the function strcat that we showed in
// chapter 2: strcat(s,t) copies the string t to the end of s.
#include <stdio.h>

void strcatf(char *, char *);

int main() {
	char str[] = "This is a string. ", endstr[] = "This is at the end.";
	printf("str: %s\n", str);
	strcatf(str, endstr);
	printf("str: %s\n", str);
	return 0;
}

// copy t to end of s
void strcatf(char *s, char *t) {
	while (*s++);
	while (*(s++ - 1) = *t++);
}
