// section 5.11
// ex. 5-17: add a field-handling capability, so sorting may be done on fields
// within lines, each field sorted according to an independent set of options.
// (The index for this book was sorted with -df for the index category and -n
// for the page numbers.)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "alloc.h"
#include "swap.h"
#include "getlinef.h"

#define MAXLEN		2000	// maximum line length
#define MAXLINES	5000	// maximum number of lines
char *lineptr[MAXLINES];	// line pointers
int ins = 0,			// case insensitivity
    field = 0;			// field to sort by

void writelines(char *[], int);
int readlines(char *[], int);
int numcmp(char *, char *);
int strcmpf(char *, char *);
int strcmpd(char *, char*);
void setend(char *, char);
char getfield(char **, int);
void qsortf(void *[], int, int, int (*)(void*,void*), int);

// sort input lines
int main(int argc, char *argv[]) {
	int nlines;
	int (*cmpfunc)(void*,void*) = (int (*)(void*,void*)) strcmpf;
	int direction = 1;	// ascending

	while (--argc > 0 && (*++argv)[0] == '-')
		while (*++argv[0])
			switch (*argv[0]) {
			case 'n':	// numerically
				cmpfunc = (int (*)(void*,void*)) numcmp;
				break;
			case 'r':	// reverse
				direction = -1;
				break;
			case 'f':	// fold cases
				ins = 1;
				break;
			case 'd':	// directory-style sort
				cmpfunc = (int (*)(void*,void*)) strcmpd;
				break;
			case 'k':	// sort by field (default = 1)
				field = 1;
				break;
			default:
				printf("Unknown option '%c'\n", *argv[0]);
				argc = 0;
				break;
			}
	for (; argc > 0; --argc, ++argv)
		switch (*argv[0]) {
		case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			if (field == 1)
				field = atoi(argv[0]);
			else if (field == 0)
				printf("Unknown option '%c'\n", *argv[0]);
			else if (field > 1)
				printf("Field already set to %d\n", field);
			break;
		default:
			printf("Invalid specifier after -k argument.\n");
			argc = 0;
			break;
		}
	if (argc < 0) {
		printf("Usage: sortlines [-n] [-r] [-f] [-d] [-k N]\n");
		return 1;
	} else if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsortf((void **) lineptr, 0, nlines-1, cmpfunc, direction);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

// qsortf: quicksort an array
void qsortf(void *v[], int left, int right,
	int (*comp)(void*,void*), int dir) {
	int i, last;
	
	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (dir * (*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsortf(v, left, last-1, comp, dir);
	qsortf(v, last+1, right, comp, dir);
}

// puts pointer at start of nth field, sets temp boundary, and returns
// char overwritten by '\0'
char getfield(char **lp, int n) {
	char *slp, c = '\0';

	if (n == 0)
		return c;
	for (; **lp && n > 0; --n) {
		while (**lp == ' ' || **lp == '\t') ++*lp;
		slp = *lp;
		while (**lp && **lp != ' '&& **lp != '\t') ++*lp;
	}
	c = **lp;
	**lp = '\0';
	*lp = slp;
	return c;
}

// set first occurrence of '\0' to c
void setend(char *p, char c) {
	while (*p) ++p;
	*p = c;
}

// compare strings in phone directory fashion
int strcmpd(char *s1, char *s2) {
	char s1end = getfield(&s1, field),
	     s2end = getfield(&s2, field);

	char *ss1 = s1, *ss2 = s2;
	int diff = 0, spc1, spc2;
	
	// first, compare digits and letters only
	for (; diff == 0 && (*s1 || *s2); ++s1, ++s2) {
		while (*s1 && !isalnum(*s1)) ++s1;
		while (*s2 && !isalnum(*s2)) ++s2;
		if (ins ? tolower(*s1) != tolower(*s2) : *s1 != *s2)
			diff = (*s1 < *s2) ? -1 : 1;
	}
	if (diff != 0) {
		setend(s1, s1end);
		setend(s2, s2end);
		return diff;
	}
	// if same, compare by spaces
	spc1 = spc2 = 0;
	for (; spc1 == spc2 && (*ss1 || *ss2); ++ss1, ++ss2) {
		for (; *ss1 && !isalnum(*ss1); ++ss1, ++spc1);
		for (; *ss2 && !isalnum(*ss2); ++ss2, ++spc2);
	}
	setend(ss1, s1end);
	setend(ss2, s2end);
	if (spc1 != spc2)
		return (spc1 < spc2) ? -1 : 1;
	return 0;
}

// compare strings (special function)
int strcmpf(char *s1, char *s2) {
	char s1end = getfield(&s1, field),
	     s2end = getfield(&s2, field);
	for (; ins ? tolower(*s1) == tolower(*s2) : *s1 == *s2; ++s1, ++s2)
		if (*s1 == '\0') {
			setend(s1, s1end);
			setend(s2, s2end);
			return 0;
		}
	setend(s1, s1end);
	setend(s2, s2end);
	return (unsigned char)*s1 < (unsigned char)*s2 ? -1 : 1;
}

// compare strings numerically
int numcmp(char *s1, char *s2) {
	char s1end = getfield(&s1, field),
	     s2end = getfield(&s2, field);
	double a = atof(s1), b = atof(s2);
	setend(s1, s1end);
	setend(s2, s2end);
	if (a > b) return 1;
	else if (a < b) return -1;
	else return 0;
}

// read from stdin and return number of lines, or -1 if input goes over
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];
	
	nlines = 0;
	while ((len = getlinef(line,MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0'; // delete newline
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

// print out lines
void writelines(char *lines[], int n) {
	while (n-- > 0)
		printf("%s\n", *lines++);
}
