// section 1.10
// ex 1-24: write a program to check a C program for syntax errors
// (eg. unbalanced parentheses, brackets, and braces)
#include <stdio.h>
#define OUT	0
#define IN	1
#define STRLEN	8096	// max input length

void check_syntax(char[]);

int main() {
	int len, nlen;
	char input[STRLEN];

	int c;
	for (len=0; len<STRLEN-1 && (c=getchar()) != EOF; ++len)
		input[len] = c; // slow, but for practice
	input[len] = '\0';
	check_syntax(input);
	return 0;
}

int check_errors(char in[], int p, int strc, int endc) {
	int icom = OUT, pcom = OUT, str = OUT, chr = OUT;
	int oldp = p;
	while (in[++p] != '\0') {
		if (icom == OUT && pcom == OUT && str == OUT && in[p] == '\'')
			chr = !chr;				// chars
		else if (icom == OUT && pcom == OUT && chr == OUT
			 && in[p] == '"')
			str = !str;				// strings
		else if (pcom == OUT && str == OUT && chr == OUT
			 && in[p] == '/' && in[p+1] == '/')	// inline com
			icom = IN;
		else if (icom == IN && in[p] == '\n')
			icom = OUT;
		else if (icom == OUT && str == OUT && chr == OUT
			 && in[p] == '/' && in[p+1] == '*')	// prologue com
			pcom = IN;
		else if (pcom == IN && in[p-1] == '*' && in[p] == '/')
			pcom = OUT;
		else if (icom == OUT && pcom == OUT&& str == OUT && chr == OUT)
			if (in[p] == strc)
				p = check_errors(in, p, strc, endc);
			else if (in[p] == endc) {
				if (oldp == -1)
					printf("c%d: Unmatched '%c'\n",
						p, endc);
				else return p;
			}
	}
	if (in[p] == '\0' && oldp != -1)
		printf("c%d: Unmatched '%c'\n", oldp, strc);
	return p;
}

void check_syntax(char in[]) {
	check_errors(in, -1, '(', ')');
	check_errors(in, -1, '[', ']');
	check_errors(in, -1, '{', '}');
}
