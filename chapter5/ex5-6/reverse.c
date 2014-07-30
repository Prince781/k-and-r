// section 5.5
// ex. 5-6: rewrite, but with pointers
#include <stdio.h>

void reverse(char *);

int main() {
	char str[] = "This is a string";
	printf("former: \"%s\"\n", str);
	reverse(str);
	printf("reversed: \"%s\"\n", str);
	return 0;
}

// reverse a string in place
void reverse(char *s) {
	char *end = s, temp;
	while (*end) ++end;
	while (end - s > 0) {
		temp = *s;
		*s++ = *--end;
		*end = temp;
	}
}
