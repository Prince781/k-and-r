// section 6.6
// ex. 6-6: implement a simple version of the #define processor (i.e., no
// arguments) suitable for use with C programs, based on the routines of this
// section. You may also find getch and ungetch helpful.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getch.h"

#define MAXHASH		101	// maximum number of hashes
#define MAXWORD		1000	// maximum word length
#define MAXTOKEN	10000	// maximum value length

struct entry {
	struct entry *next;	// next item in list
	char *name;		// key
	char *defn;		// definition (value)
};

unsigned hash(char *);			// hashing function
struct entry *lookup(char *);		// search
struct entry *install(char *, char *);	// install key, val
struct entry *undef(char *);		// remove key, val from table
void tableprint(void);			// print all hash table entries
void nodeprint(struct entry *);

static struct entry *hashtab[MAXHASH];	// array of pointers to linked list

int getword(char *, int);		// read in a new word
int gettoken(char *, int);		// read in after #define/#undef word
int procdefn(void);			// read in next #define/#undef entry

int main() {
	while (procdefn() != EOF);
	tableprint();
	return 0;
}

// procdefn: process #define or #undef statement
int procdefn(void) {
	char word[MAXWORD], val[MAXTOKEN];
	int c, def;

	while ((c=getch()) != '#' && c != EOF);
	if (c == '#' && (c=getword(word,MAXWORD)) != EOF)
		if ((!strcmp(word,"define")||!strcmp(word,"undef"))) {
			def = word[0] == 'd';
			if ((c=getword(word,MAXWORD)) != EOF) {
				c = gettoken(val,MAXTOKEN);
				if (def)
					install(word, *val != '\0' ? val : "");
				else
					free((void *) undef(word));
			}
		}
	return c;
}

// gettoken: read in entry
int gettoken(char *t, int lim) {
	char *s = t;
	int c;

	while ((c=getch()) == ' ' || c == '\t');
	if (c == '\n' || c == EOF)
		return c;
	for (*t++=c; t-s<lim-1 && (c=getch())!='\n' && c!=EOF; *t++=c);
	ungetch(c);
	*t = '\0';
	return *s;
}

// getword: get word input
int getword(char *w, int lim) {
	int c;
	char *word = w;

	while (isspace(c=getch()));
	if (!isalpha(c) && c != '_')
		return c;
	for (*w++=c; w-word<lim-1 && (isalnum(c=getch()) || c=='_'); *w++=c);
	if (w-word < lim-1) {
		ungetch(c);
		c = word[0];
	}
	*w = '\0';
	return c;
}

// hash: generate a hash value from a string
unsigned hash(char *s) {
	unsigned v;
	for (v=0; *s; ++s)
		v = *s + 31*v;
	return v % MAXHASH;
}

// lookup: look up an entry from its name
struct entry *lookup(char *name) {
	struct entry *ep;
	for (ep=hashtab[hash(name)]; ep != NULL; ep = ep->next)
		if (strcmp(ep->name,name) == 0)	// found match
			return ep;
	return NULL;
}

// install: install a key,value pair and return its address
struct entry *install(char *name, char *defn) {
	struct entry *ep;
	unsigned hashval;
	
	if ((ep=lookup(name)) == NULL) {
		ep = (struct entry *) malloc(sizeof(struct entry));
		hashval = hash(name);
		if ((ep->name = strdup(name)) == NULL)
			return NULL;
		ep->next = hashtab[hashval];	// insert at beginning of list
		hashtab[hashval] = ep;
	} else free((void *) ep->defn);		// free previous defn
	if ((ep->defn = strdup(defn)) == NULL)
		return NULL;
	return ep;
}

// undef: remove a definition and return it (note: don't forget to free() it)
struct entry *undef(char *name) {
	struct entry *ep, **pp;

	if ((ep=lookup(name)) == NULL)
		return NULL;
	for (pp=hashtab+hash(name); *pp != ep; pp=&(*pp)->next);
	*pp = ep->next;
	return ep;
}

// tableprint: print all #define rules
void tableprint(void) {
	struct entry **p;
	for (p=hashtab; p-hashtab < MAXHASH; ++p)
		nodeprint(*p);
}

// nodeprint: print a node
void nodeprint(struct entry *ep) {
	if (ep != NULL) {
		nodeprint(ep->next);
		printf("%s => %s\n", ep->name, ep->defn);
	}
}
