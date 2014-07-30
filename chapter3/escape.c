// section 3.4
// ex. 3-2: write a function escape(s,t) that converts characters like newline
// and tab into visible escape sequences like "\n" and "\t" as it copies the
// string t to s. Use a switch. Write a function for the other direction as
// well, converting escape sequences into the real characters.
#include <stdio.h>
#define MAXLINE 1024

int escape(char[], char[]);
int unescape(char[], char[]);
int getline_f(char[], int);

int main() {
	char line[MAXLINE], eline[MAXLINE], uneline[MAXLINE];
	printf("Enter text:\n");
	while (getline_f(line, MAXLINE) != 0) {
		escape(line, eline);
		printf("Escaped:\n%s\n", eline);
		unescape(eline, uneline);
		printf("Unescaped:\n%s", uneline);
		printf("Enter text:\n");
	}
	return 0;
}

// escape escape sequences in ln
int escape(char ln[], char nln[]) {
	int i, j;
	for (i=j=0; ln[i] != '\0'; ++i)
		switch (ln[i]) {
		case '\a':
			nln[j++] = '\\';
			nln[j++] = 'a';
			break;
		case '\b':
			nln[j++] = '\\';
			nln[j++] = 'b';
			break;
		case '\f':
			nln[j++] = '\\';
			nln[j++] = 'f';
			break;
		case '\n':
			nln[j++] = '\\';
			nln[j++] = 'n';
			break;
		case '\r':
			nln[j++] = '\\';
			nln[j++] = 'r';
			break;
		case '\t':
			nln[j++] = '\\';
			nln[j++] = 't';
			break;
		case '\v':
			nln[j++] = '\\';
			nln[j++] = 'v';
			break;
		case '\\':
			nln[j++] = '\\';
			nln[j++] = '\\';
			break;
		case '\'':
			nln[j++] = '\\';
			nln[j++] = '\'';
			break;
		default:
			nln[j++] = ln[i];
			break;
		}
	nln[j] = '\0';
	return j;
}

// unescape: convert escape sequences into characters
int unescape(char ln[], char nln[]) {
	int i, j;
	int slash = 0;
	for (i=1,j=0; ln[i-1] != '\0'; ++i)
		switch (ln[i-1]) {
		case '\\':
			switch (ln[i]) {
				case 'a': nln[j++] = '\a'; ++i; break;
				case 'b': nln[j++] = '\b'; ++i; break;
				case 'f': nln[j++] = '\f'; ++i; break;
				case 'n': nln[j++] = '\n'; ++i; break;
				case 'r': nln[j++] = '\r'; ++i; break;
				case 't': nln[j++] = '\t'; ++i; break;
				case 'v': nln[j++] = '\v'; ++i; break;
				case '\\': nln[j++] = '\\'; ++i; break;
				case '\'': nln[j++] = '\''; ++i; break;
				default:
					nln[j++] = ln[i-1];
					nln[j++] = ln[i];
					break;
			}
			break;
		default:
			nln[j++] = ln[i-1];
			break;
		}
	nln[j++] = '\0';
	return j;
}

int getline_f(char ln[], int lim) {
	int c, l;
	for (l=0; (c=getchar()) != EOF && c != '\n'; ++l)
		if (l < lim)
			ln[l] = c;

	if (l >= lim-1) {
		ln[lim-1] = '\0';
		ln[lim-2] = '\n';
		return ++l;
	}

	if (c == '\n') {
		ln[l] = c;
		++l;
	}

	ln[l] = '\0';
	return l;
}
