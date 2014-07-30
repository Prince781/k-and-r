#include "getlinef.h"

int getlinef(char *s, int lim) {
	char *str = s;
	for (; s-str < lim && (*s=getchar()) != EOF && *s != '\n'; ++s);
	if (*s == '\n') ++s;
	*s = '\0';
	return s - str;
}
