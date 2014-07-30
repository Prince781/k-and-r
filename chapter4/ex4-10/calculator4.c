// section 4.3
// ex. 4-10: an alternate organization uses getline to read an entire input
// line; this makes getch and ungetch unnecessary. Revise the calculator to use
// this approach.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// include getop4.c pushpop.c
#define MAXLINE		1024
#define MAXOP		100	// max size of operand or operator
#define NUMBER		'0'
#define VARIABLE	'a'
#define MATH_POW	1
#define MATH_EXP	2
#define MATH_SQRT	3
#define MATH_SIN	4
#define MATH_COS	5
#define MATH_TAN	6
#define MATH_ASIN	7
#define MATH_ACOS	8
#define MATH_ATAN	9
#define F_VAR		11	// function: set variable
#define VAR_ANS		12	// answer variable

int getlinef(char[],int);
int getop(char[],char[]);		// get operator or operand
void push(double);		// push contents to stack
double pop(void);		// remove from stack
void pushvar(int);		// push variable address to stack
int popvar(void);		// pop variable address from stack
void setvar(double);		// set variable on top of stack to value
double getvar(int);		// get variable value from address

int main() {
	int type;
	double op2;
	char s[MAXOP], line[MAXLINE];
	double ans = 0.0;
	
	while (getlinef(line,MAXLINE) != 0)
		while ((type=getop(line, s)) != '\0')
			switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case VARIABLE: // push to both stacks
				push(getvar(s[0]-'a')); // value stack
				pushvar(s[0]-'a');
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
			case VAR_ANS:
				push(ans);
				break;
			case F_VAR:
				setvar(op2 = pop());
				pop();		// pop variable value
				push(op2);
				break;
			case '\n':
				printf("\t%.8g\n", ans = pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
			}
	return 0;
}
