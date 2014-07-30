// section 5.5
// ex. 5-6: rewrite, but with pointers
#include <stdio.h>
#include <ctype.h>
#define NUMBER	'0'

int getop(char *s);

int main() {
	char input[100];
	int op;
	while ((op = getop(input)) != EOF)
		switch (op) {
		case NUMBER:
			printf("You entered a number.\n");
			break;
		case '+':
		case '-':
		case '\\':
		case '*':
			printf("You entered an operator.\n");
			break;
		case '\n': break;
		default:
			printf("You did not enter something valid.\n");
			break;
		}
	return 0;
}

// get next operator or numeric operand
int getop(char *s) {
	while ((*s = getc(stdin)) == ' ' || *s == '\t'); // skip spaces
	*(s+1) = '\0';
	if (!isdigit(*s) && *s != '.')
		return *s;
	if (isdigit(*s))
		while (isdigit(*++s = getc(stdin)));
	if (*s == '.')
		while (isdigit(*++s = getc(stdin)));
	if (*s != EOF) ungetc(*s, stdin);
	*s = '\0';
	return NUMBER;
}

