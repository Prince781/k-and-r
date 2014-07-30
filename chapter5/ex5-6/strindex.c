// section 5.5
// ex. 5-6: rewrite, but with pointers
#include <stdio.h>

int strindex(char *, char *);

int main() {
	char str[] = "This is a string.", key[] = "ing.";
	printf("string: \"%s\"\n", str);
	printf("found \"%s\" at position %d\n", key, strindex(str,key));
	return 0;
}

// strindex: return index of t in s, -1 if none
int strindex(char *s, char *t) {
	char *tstr = t, *sstr = s;
	for (; *s && *t; ++s)
		if (*s == *t) ++t;
		else t = tstr;
	return (*t == '\0') ? s - (t - tstr) - sstr : -1;
}
