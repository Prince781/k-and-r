// section 4.3
// getop.c
#include <stdio.h>
#include <ctype.h>
// include getch.c
#define NUMBER	'0'	// number found
int getch(void);	// get character
void ungetch(int);	// put character back in buffer

// getop: get next operator or numeric operand, put in s[]
int getop(char s[]) {
	int i, c;
	while ((s[0]=c=getch()) == ' ' || c == '\t'); // skip spaces
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	// not a number
	i = 0;
	if (isdigit(c))
		while ( isdigit(s[++i]=c=getch()) );
	if (c == '.')
		while ( isdigit(s[++i]=c=getch()) );
	s[i] = '\0';
	if (c != EOF) ungetch(c);
	return NUMBER;
}