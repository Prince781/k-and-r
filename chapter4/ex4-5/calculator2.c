// section 4.3
// ex. 4-5: add access to library functions like sin, exp, and pow.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// include getop2.c getch.c pushpop.c
#define MAXOP		100	// max size of operand or operator
#define NUMBER		'0'
#define MATH_POW	1
#define MATH_EXP	2
#define MATH_SQRT	3
#define MATH_SIN	4
#define MATH_COS	5
#define MATH_TAN	6
#define MATH_ASIN	7
#define MATH_ACOS	8
#define MATH_ATAN	9
int getop(char[]);	// get operator or operand
void push(double);	// push contents to stack
double pop(void);	// remove from stack

int main() {
	int type;
	double op2;
	char s[MAXOP];
	
	while ((type=getop(s)) != EOF)
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			op2 = pop();
			push(pop() / op2);
			break;
		case '%':
			op2 = pop();
			push((long)(pop()+0.5) % (long)(op2+0.5));
			break;
		case MATH_POW:
			op2 = pop();
			push(pow(pop(),op2));
			break;
		case MATH_EXP:
			push(exp(pop()));
			break;
		case MATH_SQRT:
			push(sqrt(pop()));
			break;
		case MATH_SIN:
			push(sin(pop()));
			break;
		case MATH_COS:
			push(cos(pop()));
			break;
		case MATH_TAN:
			push(tan(pop()));
			break;
		case MATH_ASIN:
			push(asin(pop()));
			break;
		case MATH_ACOS:
			push(acos(pop()));
			break;
		case MATH_ATAN:
			push(atan(pop()));
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	return 0;
}