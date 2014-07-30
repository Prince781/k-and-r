// section 7.4
// ex. 7-4: write a private version of scanf analogous to minprintf from the
// previous section.
#include <stdio.h>
#include <stdarg.h>

static int minscanf(char *fmt, ...);

int main() {
	unsigned day = 0;
	int year = 0;
	char mon[100];
	int status;
	while ((status=minscanf("%x/%d", &day, &year)) != EOF)
		printf("day(oct->dec): %u, year: %d\n", day, year);
	return 0;
}

static int minscanf(char *fmt, ...) {
	va_list ap;
	union {
		int *ip;
		float *fp;
		unsigned *up;
		char *cp, *s;
	} data;
	char *p;
	int c = 0, set = 0, status = 1;
	
	va_start(ap, fmt);
	for (p = fmt; *p && c != EOF && status; p++)
		if (*p == ' ')
			continue;
		else if (*p != '%') {
			if ((c=getchar()) != *p)
				break;
		} else {
			switch (*++p) {
			default:
				if ((c=getchar()) != '%')
					status = 0;
				if (status && *p!='%' && (c=getchar())!=*p)
					status = 0;
				break;
			case 'i':
				data.ip = va_arg(ap, int *);
				set += status=scanf("%i", data.ip);
				break;
			case 'd':
				data.ip = va_arg(ap, int *);
				set += status=scanf("%d", data.ip);
				break;
			case 'f':
				data.fp = va_arg(ap, float *);
				set += status=scanf("%f", data.fp);
				break;
			case 'u':
				data.up = va_arg(ap, unsigned *);
				set += status=scanf("%u", data.up);
				break;
			case 'x':
				data.up = va_arg(ap, unsigned *);
				set += status=scanf("%x", data.up);
				break;
			case 's':
				data.s = va_arg(ap, char *);
				set += status=scanf("%s", data.s);
				break;
			case 'c':
				data.cp = va_arg(ap, char *);
				set += status=scanf("%c", data.cp);
				break;
			}
			if (!status)
				c = getchar();
			else if (status == EOF)
				c = status;
		}
	va_end(ap);
	return c == EOF ? c : set;
}
