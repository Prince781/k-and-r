// section 5.12
// ex. 5-20: expand dcl to handle declarations with function argument types,
// qualfiiers like const, and so on
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "getch.h"

#define MAXTOKEN	100

enum { NAME, PARENS, BRACKETS, TYPE, QUALIFIER, UNDEF };

void funcdcl(void);
void abs_dcl(void);
void abs_dirdcl(void);
void dcl(void);
void dirdcl(void);

int istype(char *);
int isqual(char *);
void printtoken(int);

int gettoken(void);
int tokentype = UNDEF;		// type of last token
char token[MAXTOKEN];		// last token string
char name[MAXTOKEN];		// identifier name
char datatype[MAXTOKEN];	// data type (int, char, etc)
char out[1000];

int main() {
	while (gettoken() != EOF) {
		strcpy(datatype, token);	// first token is data type
		while (tokentype == QUALIFIER) {
			gettoken();
			strcat(datatype, " ");
			strcat(datatype, token);
		}
		*name = '\0';
		out[0] = '\0';
		dcl();
		if (tokentype != '\n') {
			printf("syntax error\n");
			printf("current tokentype is ");
			printtoken(tokentype);
			printf("\n");
			while (gettoken() != '\n');
		}
		if (*name)
			printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

void printtoken(int tk) {
	if (tk == NAME)
		printf("NAME");
	else if (tk == PARENS)
		printf("PARENS");
	else if (tk == BRACKETS)
		printf("BRACKETS");
	else if (tk == QUALIFIER)
		printf("QUALIFIER");
	else if (tk == TYPE)
		printf("TYPE");
	else if (tk == UNDEF)
		printf("UNDEF");
	else printf("%c", tk);
}

// validate whether or not item is type
int istype(char *s) {
	return !(
		strcmp(s, "char") && strcmp(s, "short") && strcmp(s, "int")
		&& strcmp(s, "long") && strcmp(s, "float")
		&& strcmp(s, "double") && strcmp(s, "struct")
		&& strcmp(s, "void") && strcmp(s, "union")
	);
}

// validate whether or not item is qualifier
int isqual(char *s) {
	return !(
		strcmp(s, "const") && strcmp(s, "static")
		&& strcmp(s, "extern") && strcmp(s, "inline")
		&& strcmp(s, "unsigned") && strcmp(s, "signed")
	);
}

// parse arguments in a function declaration
void funcdcl(void) {
	char dtype[MAXTOKEN];	// type after argument
	do {
		strcat(out, " taking");
		dtype[0] = '\0';
		do {
			gettoken();
			strcat(dtype, " ");
			strcat(dtype, token);
		} while (tokentype == QUALIFIER);
		abs_dcl();
		strcat(out, dtype);
	} while (tokentype == ',');
}

// parse an abstract declarator (optional *) (abs-dir-dcl)
void abs_dcl(void) {
	int np, type;
	
	for (np = 0; (type=gettoken()) == '*'; ++np);
	if (type != ')' && type != ',')
		abs_dirdcl();
	while (np-- > 0)
		strcat(out, " pointer to");
}

// parse an abstract direct declarator
// []
// ()
// (abs-dcl)
// (...)
void abs_dirdcl(void) {
	int type = tokentype;
	char temp[MAXTOKEN];
	temp[0] = '\0';
	
	if (type == '(') {	// (abs-dcl)
		abs_dcl();
		if (tokentype != ')')
			printf("Expecting ')'\n");
	} else if (type == BRACKETS) {
		strcat(out, " array");
		strcat(out, token);
		strcat(out, " of");
	} else if (type == PARENS)
		strcat(out, " function returning");
	else if (type == TYPE || type == QUALIFIER) {
		strcpy(temp, " ");
		strcat(temp, token);
	}
	
	while ((type=gettoken())==TYPE || type==BRACKETS || type==PARENS
		||type == '('||type==QUALIFIER)
		if (type == TYPE || type == QUALIFIER) {
			strcat(out, " ");
			strcat(out, token);
		} else if (type == BRACKETS) {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		} else if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " function");
			funcdcl();
			strcat(out, " returning");
		}
	strcat(out, temp);	// print out saved type
}

// parse a declarator
void dcl(void) {
	int np;

	for (np = 0; gettoken() == '*'; ++np);
	dirdcl();
	while (np-- > 0)
		strcat(out, " pointer to");
}

// parse a direct declarator
void dirdcl(void) {
	int type;
	
	if (tokentype == '(') {	// (dcl)
		dcl();
		if (tokentype != ')')
			printf("error: missing ')'\n");
	} else if (tokentype == NAME)
		strcpy(name, token);
	else {
		printf("error: expected name or (dcl)\n");
		return;
	}

	while ((type=gettoken()) == PARENS || type == BRACKETS || type == '(')
		if (type == PARENS)
			strcat(out, " function returning");
		else if (type == '(') {	// dir-dcl(funcdl)
			strcat(out, " function");
			funcdcl();
			strcat(out, " returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
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
		if (isqual(token))
			return tokentype = QUALIFIER;
		else if (istype(token))
			return tokentype = TYPE;
		else return tokentype = NAME;
	} else
		return tokentype = c;
}
