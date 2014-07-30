// section 5.12
// ex. 5-19: modify undcl so that it does not add redundant parentheses to
// declarations
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "getch.h"

#define MAXTOKEN	100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype;			// type of last token
char token[MAXTOKEN];		// last token string
char name[MAXTOKEN];		// identifier name
char datatype[MAXTOKEN];	// data type
char out[1000];

// undcl: convert word description to declaration
int main() {
	int type, lastpntr /* last was pointer */;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		lastpntr = 0;
		strcpy(out, token);
		while ((type = gettoken()) != '\n') {
			if (lastpntr) {
				sprintf(temp, 
					type=='*'||type==NAME?"*%s":"(*%s)",
					out);
				strcpy(out, temp);
			}
			lastpntr = type=='*';
			if (type == PARENS || type == BRACKETS) {
				strcat(out, token);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else if (type != '*')
				printf("invalid input at %s\n", token);
		}
		printf(lastpntr ? "*%s" : "%s\n", out);
	}
}

// get next token and return it; set it globally
int gettoken(void) {
	int c;
	char *p = token;

	while ((c=getch()) == ' ' || c == '\t');
	if (c == '(') {
		if ((c=getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++=c; p-token<MAXTOKEN-1 && isdigit(c=getch()); )
			*p++ = c;
		if (p-token<MAXTOKEN-1) {
			if (c != ']')
				ungetch(c);
			*p++ = ']';
		}
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++=c; isalnum(c=getch()); *p++ = c);
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}
