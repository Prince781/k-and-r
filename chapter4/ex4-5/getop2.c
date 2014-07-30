// section 4.3
// getop2.c
// ex. 4-5: add access to library functions like sin, exp, and pow.
#include <stdio.h>
#include <ctype.h>
// include getch.c calculator2.c pushpop.c
#define NUMBER	'0'	// number found
#define MATH_POW	1
#define MATH_EXP	2
#define MATH_SQRT	3
#define MATH_SIN	4
#define MATH_COS	5
#define MATH_TAN	6
#define MATH_ASIN	7
#define MATH_ACOS	8
#define MATH_ATAN	9
int getch(void);	// get character
void ungetch(int);	// put character back in buffer

// getop: get next operator or numeric operand, put in s[]
int getop(char s[]) {
	int i = 0, c;
	while ((s[0]=c=getch()) == ' ' || c == '\t'); // skip spaces
	s[1] = '\0';
	
	if (!isdigit(c) && isalpha(c)) {
		while ( isalnum(s[++i]=c=getch()) );
		s[i] = '\0';
		ungetch(c);
		if (strcmp(s, "pow") == 0) return MATH_POW;
		else if (strcmp(s, "exp") == 0) return MATH_EXP;
		else if (strcmp(s, "sqrt") == 0) return MATH_SQRT;
		else if (strcmp(s, "sin") == 0) return MATH_SIN;
		else if (strcmp(s, "cos") == 0) return MATH_COS;
		else if (strcmp(s, "tan") == 0) return MATH_TAN;
		else if (strcmp(s, "asin") == 0) return MATH_ASIN;
		else if (strcmp(s, "acos") == 0) return MATH_ACOS;
		else if (strcmp(s, "atan") == 0) return MATH_ATAN;
		else return c;
	} else if (!isdigit(c))
		return c;
		
	i = 0;
	if (isdigit(c))
		while ( isdigit(s[++i]=c=getch()) );
	if (c == '.')
		while ( isdigit(s[++i]=c=getch()) );
	s[i] = '\0';
	if (c != EOF) ungetch(c);
	return NUMBER;
}
