// section 6.6
// ex. 6-2: write a program that reads a C program and prints in alphebetical
// order each group of variable names that are identical in the first 6
// characters, but different somewhere thereafter. Don't count words within
// strings and comments. Make 6 a parameter that can be set from the command
// line.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXWORD	100		// max word size
static int simchars = 6;	// number of similar chars necessary for match

static char *keywords[] = {
	"auto", "break", "case", "char", "const", "continue", "default", "do",
	"double", "else", "enum", "extern", "float", "for", "goto", "if",
	"int", "long", "register", "return", "short", "signed", "sizeof",
	"static", "struct", "switch", "typedef", "union", "unsigned", "void",
	"volatile", "while"
};

#define NKEYWORDS	(sizeof keywords / sizeof keywords[0])

struct term {			// found variable name
	char *str;
	struct term *left, *same, *right;
};

char *getkey(char *);
int isvarname(char *);
int getword(char *, int);
struct term *addtree(struct term *, char *);
void treeprint(struct term *);
void branchprint(struct term *);

int main(int argc, char *argv[]) {
	char word[MAXWORD];
	struct term *root = NULL;

	while (--argc > 0)
		if ((*++argv)[0] == '-' && isdigit(*++argv[0]))
			simchars = atoi(argv[0]);
		else {
			printf("Usage: getvars [-n]\n");
			return 1;
		}
	while (getword(word,MAXWORD) != EOF)
		if (isvarname(word) && strlen(word) >= simchars)
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

// get a C keyword or return NULL otherwise
char *getkey(char *s) {
	char **low = keywords,
	     **high = keywords + NKEYWORDS,
	     **mid;
	int comp;
	while (low < high) {
		mid = low + (high - low)/2;
		if ((comp=strcmp(s,*mid)) < 0)
			high = mid;
		else if (comp > 0)
			low = mid + 1;
		else return *mid;
	}
	return NULL;
}

// isvarname: validate if string is a variable name in C
int isvarname(char *s) {
	return (isalnum(s[0]) || s[0] == '_') && getkey(s) == NULL;
}

// getword: get word 
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

struct term *addtree(struct term *p, char *word) {
	int cmp;
	if (p == NULL) {
		p = (struct term *) malloc(sizeof(struct term));
		p->str = strdup(word);			// set word pointer
		p->left = p->same = p->right = NULL;	// initialize pointers
	} else if (strcmp(word,p->str)) {
		if ((cmp=strncmp(word,p->str,simchars)) < 0)
			p->left = addtree(p->left, word);
		else if (cmp > 0)
			p->right = addtree(p->right, word);
		else p->same = addtree(p->same, word);
	}
	return p;
}

// print out all members of a tree
void treeprint(struct term *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("starting with \"%.*s\":\n", simchars, p->str);
		printf("\t%s\n", p->str);
		branchprint(p->same);
		treeprint(p->right);
	}
}

// print out all nodes that are across the "same" branch
void branchprint(struct term *p) {
	if (p != NULL) {
		printf("\t%s\n", p->str);
		branchprint(p->same);
	}
}
