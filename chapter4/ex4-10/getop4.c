// section 4.3
// ex. 4-6
#include <stdio.h>
#include <ctype.h>
// include getlinef.c calculator3.c pushpop3.c
#define NUMBER		'0'	// number found
#define VARIABLE	'a'	// variable found
#define MATH_POW	1
#define MATH_EXP	2
#define MATH_SQRT	3
#define MATH_SIN	4
#define MATH_COS	5
#define MATH_TAN	6
#define MATH_ASIN	7
#define MATH_ACOS	8
#define MATH_ATAN	9
#define F_VAR		11
#define VAR_ANS		12

// getop: get next operator or numeric operand, put in s[]
int getop(char input[], char s[]) {
	int i=0, j=-1, c;
	while ((s[0]=c=input[++j]) == ' ' || c == '\t'); // skip spaces
	s[1] = '\0';
	
	if (!isdigit(c) && isalpha(c)) {
		while ( isalnum(s[++i]=c=input[++j]) );
		s[i] = '\0';
		strcut(input, j);
		if (strcmp(s, "pow") == 0) return MATH_POW;
		else if (strcmp(s, "exp") == 0) return MATH_EXP;
		else if (strcmp(s, "sqrt") == 0) return MATH_SQRT;
		else if (strcmp(s, "sin") == 0) return MATH_SIN;
		else if (strcmp(s, "cos") == 0) return MATH_COS;
		else if (strcmp(s, "tan") == 0) return MATH_TAN;
		else if (strcmp(s, "asin") == 0) return MATH_ASIN;
		else if (strcmp(s, "acos") == 0) return MATH_ACOS;
		else if (strcmp(s, "atan") == 0) return MATH_ATAN;
		else if (strcmp(s, "ans") == 0) return VAR_ANS;
		else if (strcmp(s, "var") == 0) return F_VAR;
		else if (i == 1) return VARIABLE;
		else return s[0];
	} else if (!isdigit(c)) {
		strcut(input, j+1);
		return c;
	}
	
	if (isdigit(c))
		while ( isdigit(s[++i]=c=input[++j]) );
	if (c == '.')
		while ( isdigit(s[++i]=c=input[++j]) );
	s[i] = '\0';
	strcut(input, j);
	return NUMBER;
}
