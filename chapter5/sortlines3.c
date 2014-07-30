// section 5.11
// ex. 5-16: add the -d ("directory order") option, which makes comparisons
// only on letters, numbers, and blanks. Make sure it works in conjunction with
// -f.
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
int ins = 0;			// case insensitivity

void writelines(char *[], int);
int readlines(char *[], int);
int numcmp(char *, char *);
int strcmpf(char *, char *);
int strcmpd(char *, char*);
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
			default:
				printf("Unknown option '%c'\n", *argv[0]);
				argc = 0;
				break;
			}
	if (argc < 0) {
		printf("Usage: sortlines [-n] [-r] [-f] [-d]\n");
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

// compare strings in phone directory fashion
int strcmpd(char *s1, char *s2) {
	char *ss1 = s1, *ss2 = s2;
	int diff = 0, spc1, spc2;
	
	// first, compare digits and letters only
	for (; diff == 0 && (*s1 || *s2); ++s1, ++s2) {
		while (*s1 && !isalnum(*s1)) ++s1;
		while (*s2 && !isalnum(*s2)) ++s2;
		if (ins ? tolower(*s1) != tolower(*s2) : *s1 != *s2)
			diff = (*s1 < *s2) ? -1 : 1;
	}
	if (diff != 0)
		return diff;
	// if same, compare by spaces
	spc1 = spc2 = 0;
	for (; spc1 == spc2 && (*ss1 || *ss2); ++ss1, ++ss2) {
		for (; *ss1 && !isalnum(*ss1); ++ss1, ++spc1);
		for (; *ss2 && !isalnum(*ss2); ++ss2, ++spc2);
	}
	if (spc1 != spc2)
		return (spc1 < spc2) ? -1 : 1;
	return 0;
}

// compare strings (special function)
int strcmpf(char *s1, char *s2) {
	for (; ins ? tolower(*s1) == tolower(*s2) : *s1 == *s2; ++s1, ++s2)
		if (*s1 == '\0')
			return 0;
	return (unsigned char)*s1 < (unsigned char)*s2 ? -1 : 1;
}

// compare strings numerically
int numcmp(char *s1, char *s2) {
	double a = atof(s1), b = atof(s2);
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
