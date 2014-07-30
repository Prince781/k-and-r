// section 1.10
// ex 1-23: write a program to remove all comments from a C program
// don't forget to handle quoted strings and character constants
// C comments do not nest
#include <stdio.h>
#define IN	1	// inside
#define OUT	0	// outside
#define STRLEN	2048	// maximum length of input

int rmcomments(char[], char[]);

int main() {
	int len, nlen;
	char input[STRLEN], output[STRLEN];

	int c;
	for (len=0; len<STRLEN-1 && (c=getchar()) != EOF; ++len)
		input[len] = c; // slow, but for practice
	input[len] = '\0';
	nlen = rmcomments(input, output);
	printf("%s", output);
	return 0;
}

// rmcomments: remove all valid comments from a C file
int rmcomments(char in[], char out[]) {
	int icom = OUT, pcom = OUT, str = OUT, chr = OUT;
	int p = -1, p2 = -1;
	while (in[++p] != '\0') {
		if (icom == OUT && pcom == OUT && str == OUT && in[p] == '\'')
			chr = !chr;				// chars
		else if (icom == OUT && pcom == OUT && chr == OUT
			 && in[p] == '"')
			str = !str;				// strings
		
		if (pcom == OUT && str == OUT && chr == OUT
			 && in[p] == '/' && in[p+1] == '/')	// inline com
			icom = IN;
		else if (icom == IN && in[p] == '\n')
			icom = OUT;
		else if (icom == OUT && str == OUT && chr == OUT
			 && in[p] == '/' && in[p+1] == '*')	// prologue com
			pcom = IN;
		else if (pcom == IN && in[p-1] == '*' && in[p] == '/')
			pcom = OUT;
		else if (icom == OUT && pcom == OUT)
			out[++p2] = in[p];
	}
	out[++p2] = '\0';
	return p2;
}
