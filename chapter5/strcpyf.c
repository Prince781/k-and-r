// test - ch 5
#include <stdio.h>

void strcpyf(char *, char*);

int main() {
	char cpy[100], str[] = "This is a string.";
	strcpyf(cpy, str);
	printf("Copy string: %s\n", cpy);
	return 0;
}

void strcpyf(char *s, char *t) {
	while (*s++ = *t++);
	printf("strcpy: *s = %c, *t = %c\n", *(s-1), *(t-1));
	if (*(s-1) == '\0')
		printf("strcpy: *s is null terminator\n");
}
