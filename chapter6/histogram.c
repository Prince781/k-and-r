// section 6.6
// ex. 6-4: write a program that prints the distinct words in its input sorted
// into decreasing order of frequency of occurrence. Precede each word by its
// count.
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getch.h"

#define MAXWORD		1000	// maximum word length

struct term {
	char *str;		// word
	int freq;		// word frequency
	struct term *left, *right;
};

int getword(char *, int);
struct term *addtree(struct term *, char *);
void reordertree(struct term *, struct term *);
struct term *addtreef(struct term *, struct term *);
void treeprint(struct term *);

int main() {
	struct term *root = NULL;
	char word[MAXWORD];
	while (getword(word,MAXWORD) != EOF)
		if (word[0] != '\0')
			root = addtree(root, word);
	reordertree(root, root);
	treeprint(root);
	return 0;
}

// getword: get word input
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

// add word to tree, sorted by strcmp
struct term *addtree(struct term *p, char *word) {
	int cmp;

	if (p == NULL) {
		p = (struct term *) malloc(sizeof(struct term));
		p->str = strdup(word);	// copy word
		p->freq = 1;
		p->left = p->right = NULL;
	} else if ((cmp=strcmp(word,p->str)) < 0)
		p->left = addtree(p->left, word);
	else if (cmp > 0)
		p->right = addtree(p->right, word);
	else p->freq++;
	return p;
}

// reorder tree
void reordertree(struct term *root, struct term *p) {
	struct term *l = p->left, *r = p->right;
	p->left = p->right = NULL;
	if (l != NULL)
		reordertree(root, l);
	if (r != NULL)
		reordertree(root, r);
	addtreef(root, p);
}

// add a node to tree according to frequency
struct term *addtreef(struct term *pos, struct term *child) {
	if (pos == NULL || pos == child)
		pos = child;
	else if (pos->freq >= child->freq)
		pos->left = addtreef(pos->left, child);
	else pos->right = addtreef(pos->right, child);
	return pos;
}

// print tree
void treeprint(struct term *p) {
	if (p != NULL) {
		treeprint(p->right);
		printf("%d: %s\n", p->freq, p->str);
		treeprint(p->left);
	}
}
