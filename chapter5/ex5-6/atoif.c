// section 5.6
// ex. 5-6: rewrite, but with pointers
#include <stdio.h>
#include <ctype.h>

int atoif(char *);

int main() {
	char str[] = "1234", str2[] = "112", str3[] = "1dd", str4[] = "+3",
		str5[] = "-3", str6[] = "d";
	printf("str: %s * 2 = %d\n", str, atoif(str)*2);
	printf("str2: %s * 2 = %d\n", str2, atoif(str2)*2);
	printf("str3: %s * 2 = %d\n", str3, atoif(str3)*2);
	printf("str4: %s * 2 = %d\n", str4, atoif(str4)*2);
	printf("str5: %s * 2 = %d\n", str5, atoif(str5)*2);
	printf("str6: %s * 2 = %d\n", str6, atoif(str6)*2);
	return 0;
}

// convert string into integer
int atoif(char *s) {
	int val = 0, sign;
	while (isspace(*s)) s++;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-') s++;
	while (isdigit(*s))
		val = 10*val + (*s++ - '0');
	return val*sign;
}
