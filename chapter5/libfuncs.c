// section 5.6
// ex. 5-5: write versions of the library functions strncpy, strncat, and
// strncmp, which operate on at most the first n characters of their argument
// strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
#include <stdio.h>

void strncpyf(char *, char *, int);
void strncatf(char *, char *, int);
int strncmpf(char *, char *, int);

int main() {
	char dest[100], str[] = "This is a sample.", t[] = "This is a test.";
	int cmpval;
	printf("dest: %s\n", dest);
	printf("t: %s\n", t);
	printf("str: %s\n", str);
	strncpyf(dest, t, 9);
	printf("strncpyf(dest, t, 9) -> dest = %s\n", dest);
	strncatf(str, t, 9);
	printf("strncatf(str, t, 9) -> str = %s\n", str);
	cmpval = strncmpf(dest, str, 9);
	printf("strncmpf(dest, str, 9) = %d\n", cmpval);
	return 0;
}

// copy first n characters from t into s
void strncpyf(char *s, char *t, int n) {
	while (n-- && (*s++ = *t++));
	*s = '\0';
}

// concatenate first n characters of t at end of s
void strncatf(char *s, char *t, int n) {
	while (*s) *s++;
	while (n-- && (*s++ = *t++));
	*s = '\0';
}

// compare first n characters of t to s
int strncmpf(char *s, char *t, int n) {
	for (; n && *s == *t; ++s, ++t, --n)
		if (*s == '\0')
			return 0;
	return *s - *t;
}
