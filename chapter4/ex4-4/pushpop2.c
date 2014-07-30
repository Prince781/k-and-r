// section 4.3
// pushpop.c - push and pop intermediate values to calculator
// ex. 4-4: add commands to print the top element of the stack without popping,
// to duplicate it, and to swap the top two elements. Add a command to clear the
// stack.
#include <stdio.h>
#include <stdlib.h>
#define MAXVAL	100	// value stack size
#define MAXLINE	1024	// line size
#define NUMBER	'0'
// include getop.c getch.c
int sp = -1;		// current stack position
double val[MAXVAL];	// value stack

double top(void);
void duptop(void);
void swaptop(void);
void clear(void);
void push(double);
double pop(void);
int getop(char[]);

int main() {
	char line[MAXLINE];
	int type;
	while ((type = getop(line)) != EOF)
		switch(type) {
		case NUMBER:
			push(atof(line));
			break;
		case '\n': break;
		default:
			printf("Input is %snumber.\n",
				type == NUMBER ? "" : "not ");
			printf("Please enter a number or EOF.\n");
			break;
		}
	printf("Size of stack: %d\n", sp+1);
	printf("Top element of stack is %.8g\n", top());
	swaptop();
	printf("After swap, top element is %.8g\n", top());
	duptop();
	printf("After duptop, size of stack is %d and top is %.8g\n", sp+1, top());
	clear();
	printf("After clear, size is %d\n", sp+1);
	return 0;
}

// top: print top element of stack without popping
double top(void) {
	if (sp > -1) return val[sp];
	else {
		printf("top: stack is empty.\n");
		return 0.0;
	}
}

// duptop: duplicate top element of stack
void duptop(void) {
	if (sp > -1) push(top());
	else printf("duptop: stack is empty.\n");
}

// swaptop: swap top two elements of stack
void swaptop(void) {
	double f1 = pop(), f2 = pop();
	push(f1);
	push(f2);
}

// clear: clear stack
void clear(void) {
	sp = -1;
	// for (sp; sp > -1; --sp)
	//	val[sp] = 0.0;
}

void push(double f) {
	if (sp < MAXVAL-1) val[++sp] = f;
	else printf("error: too many values; can't push %g\n", f);
}

double pop(void) {
	if (sp > -1) return val[sp--];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}
