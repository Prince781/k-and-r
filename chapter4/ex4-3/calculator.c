// section 4.3
// ex. 4-3: given the basic framework, it's straightforward to extend the 
// calculator. Add the modulus (%) operator and provisions for negative numbers.
#include <stdio.h>
#include <stdlib.h>
// include getop.c getch.c pushpop.c
#define MAXOP	100	// max size of operand or operator
#define NUMBER	'0'
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
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	return 0;
}
