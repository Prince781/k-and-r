// section 5.10
// ex. 5-10: write the program expr, which evaluates a reverse Polish
// expression from the command line, where each operator or operand is a
// separate argument. For example,
// 	expr 2 3 4 + *
// evalues 2 * (3+4).
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define NUMBER		'0'
#define STACKSIZE	100	// maximum number of stack elements
static double stack[STACKSIZE];
static double *p = stack;

double pop(void);
void push(double);
int getop(char *);

int main(int argc, char *argv[]) {
	double temp;
	
	while (--argc > 0)
		switch (getop(*++argv)) {
		case NUMBER:
			push(atof(argv[0]));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			temp = pop();
			push(pop() - temp);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			temp = pop();
			push(pop() / temp);
			break;
		default:
			printf("invalid operand '%s'\n", argv[0]);
			break;
		}
	printf("%f\n", pop());
	return 0;
}

// pop: pop stack
double pop(void) {
	if (p > stack)
		return *--p;
	printf("pop: stack is empty\n");
	return 0.0;
}

// push: push onto stack
void push(double v) {
	if (p < stack + STACKSIZE)
		*p++ = v;
	else printf("push: stack is full\n");
}

// getop: get operator or operand
int getop(char *s) {
	if (!isdigit(*s))
		return *s;
	return NUMBER;
}
