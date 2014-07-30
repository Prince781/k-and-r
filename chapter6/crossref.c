// section 6.6
// ex. 6-3: write a cross-referencer that prints a list of all words in a
// document, and, for each word, a list of the line numbers on which it occurs.
// Remove noise words like "the," "and," and so on.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "getch.h"

#define MAXWORD		1000	// maximum word length
static int currentline = 1;	// current line of input
static char *noise_words[] = {
	"the", "and", "of", "it", "him", "her", "his", "I", "am", "you"
};

struct lnno {	// line number
	int ln;
	struct lnno *next;
};

struct term {
	char *str;
	struct term *left, *right;
	struct lnno *line;
};

int getword(char *, int);
struct term *addtree(struct term *, char *);
struct lnno *addlnno(struct lnno *, int);
void treeprint(struct term *);
void lnnoprint(struct lnno *);

int main() {
	char word[MAXWORD];
	struct term *root = NULL;
	int status;
	while ((status=getword(word,MAXWORD)) != EOF)
		if (status == '\n') currentline++;
		else if (isalnum(word[0]) || word[0] == '_')
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

int getword(char *w, int lim) {
	int c, isword = 0;
	char *word = w;

	while ((c=getch()) == ' ' || c == '\t');
	ungetch(c);
	for (; lim > 0 && (isalnum(c=getch()) || c=='_'); --lim) {
		*w++ = c;
		if (isalpha(c)) isword = 1;
	}
	if (!isword)
		w = word;
	*w = '\0';
	return c;
}

// add a word to the tree
struct term *addtree(struct term *p, char *word) {
	int cmp;

	if (p == NULL) {
		p = (struct term *) malloc(sizeof(struct term));
		p->str = strdup(word);
		p->left = p->right = NULL;
		p->line = addlnno(p->line, currentline);
	} else if ((cmp=strcmp(word,p->str)) < 0)
		p->left = addtree(p->left, word);
	else if (cmp > 0)
		p->right = addtree(p->right, word);
	else p->line = addlnno(p->line, currentline);
	return p;
}

// add a line number to a branch if unique
struct lnno *addlnno(struct lnno *p, int cln) {
	if (p == NULL) {
		p = (struct lnno *) malloc(sizeof(struct lnno));
		p->ln = cln;
		p->next = NULL;
	} else if (p->ln != cln)
		p->next = addlnno(p->next, cln);
	return p;
}

// print a tree
void treeprint(struct term *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%s:\n", p->str);
		lnnoprint(p->line);
		treeprint(p->right);
	}
}

// print a branch
void lnnoprint(struct lnno *p) {
	if (p != NULL) {
		printf("\tline %d\n", p->ln);
		lnnoprint(p->next);
	}
}
