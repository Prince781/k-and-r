// section 7.3
// ex. 7-3: revise minprintf to handle more of the other facilities of printf
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void minprintf(char *fmt, ...);

int main() {
	void *p = malloc(100);
	minprintf("Testing minprintf function:\n");
	minprintf("double: %f\n", 32.5);
	minprintf("void pointer: %p\n", p);
	minprintf("string: %s\n", "example");
	minprintf("%%e example: %e\n", 32.5);
	minprintf("%%x example: %x\n", 0xDEADBEEF);
	free(p);
	return 0;
}

// minprintf: print formatted output
void minprintf(char *fmt, ...) {
	va_list ap;		// argument pointer
	char *p;
	union {
		int i;
		unsigned u;
		double d;
		char *s;
		void *p;
	} data;

	va_start(ap, fmt);	// initialize argument pointer
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
		case 'd':
		case 'i':
			data.i = va_arg(ap, int);
			printf("%d", data.i);
			break;
		case 'f':
			data.d = va_arg(ap, double);
			printf("%f", data.d);
			break;
		case 's':
			data.s = va_arg(ap, char *);
			for (data.s; *data.s; data.s++)
				putchar(*data.s);
			break;
		case 'p':
			data.p = va_arg(ap, void *);
			printf("%p", data.p);
			break;
		case 'u':
			data.u = va_arg(ap, unsigned);
			printf("%u", data.u);
			break;
		case 'o':
			data.u = va_arg(ap, unsigned);
			printf("%o", data.u);
			break;
		case 'x':
			data.u = va_arg(ap, unsigned);
			printf("%x", data.u);
			break;
		case 'X':
			data.u = va_arg(ap, unsigned);
			printf("%X", data.u);
			break;
		case 'e':
			data.d = va_arg(ap, double);
			printf("%e", data.d);
			break;
		case 'E':
			data.d = va_arg(ap, double);
			printf("%E", data.d);
			break;
		defualt:
			putchar(*p);
			break;
		}
	}
	va_end(ap);		// clean up
}
