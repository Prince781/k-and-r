// section 4.3
#include <stdio.h>
#define MAXVAL	100	// stack depth

int sp = 0;		// next free stack position
double val[MAXVAL];	// value stack

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
