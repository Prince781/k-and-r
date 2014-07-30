// section 8.6
// ex. 8-2: rewrite fopenf and _fillbuff with fields instead of explicit bit
// operations. Compare code size and execution speed.
// ex. 8-3: design and write _flushbuff, fflushf, and fclosef.
// ex. 8-4: the standard library function
//	int fseek(FILE *fp, long offset, int origin)
// is identical to lseek except that fp is a file pointer instead of a file
// descriptor and the return value is an int status, not a position. Write
// fseekf. Make sure that your fseekf coordinates properly with the buffering
// done for the other functions of the library.
#ifndef STDIOF_H
#define STDIOF_H

#ifndef NULL
	#define NULL	0
#endif
#define EOF		(-1)
#define BUFSIZ		1024
#define OPEN_MAX	20
#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

struct _flag {
	int		read;	// file open for reading
	int		write;	// file open for writing
	int		unbuf;	// file is unbuffered
	int		eof;	// EOF has occurred on this file
	int		err;	// error has occurred on this file
};

typedef struct _iobuf {
	int		cnt;	// characters left
	char		*ptr;	// next character position
	char		*base;	// location of buffer
	struct _flag	flags;	// modes of file access
	int		fd;	// file descriptor
	int		init;	// initialized or not
} FILE;

extern FILE _iob[OPEN_MAX];	// files

#define stdin		(&_iob[0])
#define stdout		(&_iob[1])
#define stderr		(&_iob[2])

int 	_fillbuff	(FILE *);
int 	_flushbuff	(int, FILE *);

FILE	*fopenf		(char *, char *);
int	fputsf		(const char *, FILE *);
int	fprintnf	(long, int, FILE *);
int	fflushf		(FILE *);
int	fseekf		(FILE *, long, int);
int	fclosef		(FILE *);

#define feoff(p)	(((p)->flags.eof) != 0)
#define ferrorf(p)	(((p)->flags.err) != 0)
#define	filenof(p)	((p)->fd)

#define getcf(p)	(--(p)->cnt >= 0 \
			? (unsigned char) *(p)->ptr++ : _fillbuff(p))
#define putcf(x,p)	(--(p)->cnt >= 0 \
			? *(p)->ptr++ = (x) : _flushbuff((x),p))

#define getcharf()	getcf(stdin)
#define putcharf(x)	putcf((x), stdout)

#define minprintf(s)	fputsf((s), stdout)
#define printnf(n)	fprintnf((n), 10, stdout)
#define printnbf(n,b)	fprintnf((n), (b), stdout)
#endif
