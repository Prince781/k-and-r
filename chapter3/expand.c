// section 3.5
// ex. 3-3: write a function expand(s1,s2) that expands shorthand notations like
// a-z in the string s1 into the equivalent complete list abc...xyz in s2. Allow
// for letters of either case and digits, and be prepared to handle cases like
// a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken
// literally.
#include <stdio.h>
#include <ctype.h>
#define MAXLINE		1024

void expand(char[], char[]);
int getline_f(char[], int);

int main() {
	char line[MAXLINE], nline[MAXLINE];
	while (getline_f(line, MAXLINE) != 0) {
		expand(line, nline);
		printf("%s", nline);
	}
	return 0;
}

// expand: expand sequences in ln
void expand(char ln[], char nln[]) {
	int i, j;
	int state = 0, old_state;
	int c, incr;
	for (i=0,j=-1; ln[i] != '\0'; ++i) {
		old_state = state;
		state = (ln[i] == '-' && i>0 && isalnum(ln[i-1]));
		switch (state - old_state) {
		case 0: case 1:
			nln[++j] = ln[i];
			break;
		case -1:
			if (isdigit(ln[i]) != isdigit(ln[i-2])
			|| islower(ln[i]) != islower(ln[i-2])
			|| isupper(ln[i]) != isupper(ln[i-2])) {
				nln[++j] = ln[i];
				continue;
			}
			j -= 2;
			incr = (ln[i] > ln[i-2]) ? 1 : -1;
			for (c=ln[i-2]; c != ln[i]; c+=incr)
				nln[++j] = c;
			nln[++j] = c;
			break;
		}
	}
	nln[++j] = '\0';
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
