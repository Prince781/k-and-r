// section 6.6
// ex. 6-5: write a function undef that will remove a name and definition from
// the table maintained by lookup and install
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXHASH	101		// maximum number of hashes

struct entry {
	struct entry *next;	// next item in list
	char *name;		// key
	char *defn;		// definition (value)
};

unsigned hash(char *);			// hashing function
struct entry *lookup(char *);		// search
struct entry *install(char *, char *);	// install key, val
struct entry *undef(char *);		// remove key, val from table

static struct entry *hashtab[MAXHASH];	// array of pointers to linked list

int main() {
	struct entry *temp = NULL;
	install("test1", "something");
	install("test2", "something else");
	install("test3", "this is pretty cool");
	printf("'%s' == '%s'\n", "test1", (lookup("test1"))->defn);
	install("test1", "something overwritten");
	printf("'%s' == '%s'\n", "test1", (lookup("test1"))->defn);
	printf("'%s' == '%s'\n", "test2", (lookup("test2"))->defn);
	printf("'%s' == '%s'\n", "test3", (lookup("test3"))->defn);
	printf("'%s' is %sin hashtable\n",
		"test1", lookup("test1") ? "" : "not ");
	printf("'%s' is %sin hashtable\n",
		"test4", lookup("test4") ? "" : "not ");
	printf("Removing '%s' from hashtable...\n", "test1");
	temp = undef("test1");
	printf("'%s' is %sin hashtable\n",
		"test1", lookup("test1") ? "" : "not ");
	printf("Adding to table key '%s' again...\n", "test1");
	install("test1", "something new");
	printf("'%s' == '%s'\n", "test1", (lookup("test1"))->defn);
	printf("Old version of '%s' == '%s'\n", "test1", temp->defn);
	free((void *) temp);
	printf("Freeing memory.\n");
	return 0;
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
