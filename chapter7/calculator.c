// section 7.4
// ex. 7-5: rewrite the postfix calculator of Chapter 4 to use scanf and/or
// sscanf to do the input and number conversion.
#include <stdio.h>
#include <math.h>

#define NUMBER		'0'
#define FUNC		0x100
#define MATH_SIN	0x101
#define MAXOP		100
#define STACKSIZE	1000

double vals[STACKSIZE];	// values on stack
double *valp = vals;	// value pointer

void push(double);
double pop(void);
int getop(void);	// get operator or operand

int main() {
	int c;
	double temp;
	while ((c=getop()) != EOF)
		switch (c) {
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
		case '\n':
			printf("\t= %.3lf\n", pop());
			break;
		case NUMBER:
		case ' ':
			break;
		case MATH_SIN:
			push(sin(pop()));
			break;
		default:
			printf("unknown command %c\n", c);
			break;
		}
	return 0;
}

// get operator or operand
int getop(void) {
	double v = 0.0;
	char c, temp[MAXOP];
	if ((c=scanf("%[^\n ]",temp)) <= 0)
		return c == EOF ? EOF : getchar();
	else if (*temp == '+' || *temp == '-' || *temp == '/' || *temp == '*')
		return *temp;
	else if (sscanf(temp, "%lf", &v) > 0) {
		push(v);
		return NUMBER;
	} else if (strcmp(temp,"sin") == 0)
		return MATH_SIN;
	else return FUNC;
}

// push: add operand onto stack
void push(double f) {
	if (valp < vals + STACKSIZE-1)
		*valp++ = f;
	else printf("push: stack is full\n");
}

// pop: remove operand from stack
double pop(void) {
	if (valp > vals)
		return *--valp;
	else {
		printf("pop: stack is empty\n");
		return 0.0;
	}
}
