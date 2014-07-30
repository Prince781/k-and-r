// section 6.3
// ex. 6-1: our version of getword does not properly handle underscores, string
// constants, comments, or preprocessor control lines. Write a better version.
#include <stdio.h>
#include <ctype.h>
#include "getch.h"

#define MAXWORD	100

int getword(char *, int);

int main() {
	char word[MAXWORD];
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) || word[0] == '_')
			printf("found word: %s\n", word);
		else printf("skipped\n");
	return 0;
}

// getword: get next word or character from valid code input
int getword(char *word, int lim) {
	int c, d;
	char *w = word;
	
	while (isspace(c=getch()));
	if (c == '/') {
		if ((d=getch()) == '*') {
			do {
				d = c;
				c = getch();
			} while (c != EOF && (d!='*'||c!='/'));
		} else if (d == '/') {
			while (d != EOF && d != '\n') 
				if ((d=getch())=='\\' && (d=getch())=='\n')
					d = getch();	// skip
			c = d;
		} else ungetch(d);
	} else if (c == '#') {	// preprocessor control
		while (c != EOF && c != '\n') 
			if ((c=getch())=='\\' && (c=getch())=='\n')
				c = getch();	// skip
	} else if (c == '"')
		do {
			if (d == '\\')
				d = EOF;
			else d = c;
			c = getch();
		} while (c != EOF && (d=='\\'||c!='"'));
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}
