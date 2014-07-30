// section 4.3
#include <stdio.h>
#define MAXVAL	100	// value/variable stack depth
#define MAXVAR	26	// variable stack depth

int sp = 0;		// next free stack position
double val[MAXVAL];	// value stack
int vp = 0;		// next free variable stack position
double var[MAXVAR];	// variables
int varstack[MAXVAL];	// variable _set_ stack

// push: push f onto value stack
void push(double f) {
	if (sp < MAXVAL) val[sp++] = f;
	else printf("error: stack full, can't push %g\n", f);
}

// pop: pop and return top value from stack
double pop(void) {
	if (sp > 0) return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

// pushvar: put onto stack a request to set c
void pushvar(int c) {
	if (vp < MAXVAL) varstack[vp++] = c;
	else printf("error: variable stack full, can't push '%c'\n", 'a'+c);
}

// popvar: remove variable _set_ stack top-most item
int popvar(void) {
	if (vp > 0) return varstack[--vp];
	else {
		printf("error: variable stack empty\n");
		return 0;
	}
}

// setvar: set topmost variable on _set_ stack to f
void setvar(double f) {
	var[popvar()] = f;
}

// getvar: get value from variable address
double getvar(int c) {
	if (c >= 0 && c < MAXVAR) return var[c];
	else {
		printf("error: '%c' not a variable\n", 'a'+c);
		return 0.0;
	}
}
