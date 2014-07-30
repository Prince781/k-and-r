// section 8.6
// ex. 8-2: rewrite fopenf and _fillbuff with fields instead of explicit bit
// operations. Compare code size and execution speed.
// ex. 8-3: design and write _flushbuff, fflushf, and fclosef.
// ex. 8-4: the standard library function
//	int fseekf(FILE *fp, long offset, int origin)
// is identical to lseek except that fp is a file pointer instead of a file
// descriptor and the return value is an int status, not a position. Write
// fseekf. Make sure that your fseekf coordinates properly with the buffering
// done for the other functions of the library.
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "stdiof.h"

FILE _iob[OPEN_MAX] = {	// files
	{ 0, (char *)NULL, (char *)NULL, { 1, 0, 0, 0, 0 }, 0, 1 }, // stdin
	{ 0, (char *)NULL, (char *)NULL, { 0, 1, 0, 0, 0 }, 1, 1 }, // stdout
	{ 0, (char *)NULL, (char *)NULL, { 0, 1, 1, 0, 0 }, 2, 1 }  // stderr
};
#define PERMS	0666	// RW for owner, group, others

// open a new file for reading
// note: no simultaneous read/write supported
FILE *fopenf(char *name, char *mode) {
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	FILE *fp;
	int fd;

	for (fp=_iob; fp < _iob+OPEN_MAX && fp->init; ++fp);
	if (fp >= _iob+OPEN_MAX)
		return NULL;		// no free slots
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {	// append
		if ((fd = open(name, O_WRONLY, PERMS)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);	// seek to end
	} else fd = open(name, O_RDONLY, PERMS);
	
	if (fd == -1)
		return NULL;
	fp->init = 1;
	fp->fd = fd;
	fp->cnt = 0;
	fp->ptr = fp->base = NULL;
	fp->flags.read = fp->flags.write = fp->flags.unbuf = fp->flags.eof
		= fp->flags.err = 0;
	if (*mode == 'r')
		fp->flags.read = 1;
	else fp->flags.write = 1;
	
	return fp;
}

// fillbuf: fill an input buffer
int _fillbuff(FILE *fp) {
	int bufsize;

	if (!fp->init || fp->flags.eof || fp->flags.err || !fp->flags.read)
		return EOF;
	bufsize = fp->flags.unbuf ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->base, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flags.eof = 1;
		else fp->flags.err = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

// flushbuf: flush a (full) output buffer
int _flushbuff(int c, FILE *fp) {
	int bufsize;
	
	if (!fp->init || fp->flags.eof || fp->flags.err || !fp->flags.write)
		return EOF;
	bufsize = fp->flags.unbuf ? 1 : BUFSIZ;
	if (fp->base == NULL) {
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;
		*fp->base = (unsigned char) c;
		fp->ptr = fp->base+1;
		fp->cnt = bufsize - 1;
		return *fp->base;
	} else
		fp->cnt = write(fp->fd, fp->base, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flags.eof = 1;
		else fp->flags.err = 1;
		return EOF;
	}
	fp->ptr = fp->base;
	return *fp->ptr++ = (unsigned char) c;
}

// fputsf: put string onto output buffer
int fputsf(const char *str, FILE *fp) {
	while (*str)
		if (putcf(*str++, fp) == EOF)
			return EOF;
	return 0;
}

// fprintnf: print base-b number onto output buffer
int fprintnf(long n, int b, FILE *fp) {
	int m = n < 0 ? -1 : 1;

	if (n/b != 0 && fprintnf(m*(n/b), b, fp) == EOF)
		return EOF;
	return putcf('0' + (m*n)%b, fp);
}

// fflushf: flush an output buffer
int fflushf(FILE *fp) {
	if (!fp->init || fp->flags.eof || fp->flags.err || !fp->flags.write)
		return EOF;
	if (fp->base == NULL)
		return 0;
	fp->cnt = 0;
	
	int n;
	if ((n=write(fp->fd, fp->base, fp->ptr - fp->base)) < 0) {
		fp->flags.err = 1;
		return EOF;
	} else if (n == 0 && fp->ptr-fp->base > 0) {
		fp->flags.eof = 1;
		return EOF;
	} else {
		fp->cnt = fp->flags.unbuf ? 0 : BUFSIZ-1;
		fp->ptr = fp->base;
		return 0;
	}
}

// fseekf: seek ahead in a file stream
int fseekf(FILE *fp, long offset, int origin) {
	long bp, cp, np;

	if (!fp->init || fp->flags.eof || fp->flags.err)
		return EOF;
	if ((cp = lseek(fp->fd, 0L, SEEK_CUR)) < 0) {
		fp->flags.err = 1;
		return EOF;
	} else if ((np = lseek(fp->fd, offset, origin)) < 0) {
		fp->flags.err = 1;
		return EOF;
	}

	lseek(fp->fd, cp, SEEK_SET);		// return
	if (fp->flags.write) {
		bp = cp;
		cp = bp + (fp->ptr - fp->base);
	} else
		bp = cp - fp->cnt;
	
	if (np >= bp && np <= cp) {
		fp->cnt += cp - np;
		fp->ptr = fp->base + (np - bp);
		return 0;
	} else {	// seek through file
		if (fp->flags.write && fflushf(fp) == EOF)
			return EOF;
		else if (!fp->flags.write)
			fp->cnt = 0;
		return lseek(fp->fd, np, SEEK_SET) == -1 ? EOF : 0;
	}
}

// fclosef: close a file stream
int fclosef(FILE *fp) {
	if (!fp->init)
		return EOF;
	if (fp->flags.write)
		fflushf(fp);
	fp->init = 0;
	fp->ptr = NULL;
	free(fp->base);
	fp->base = NULL;
	return close(fp->fd) == -1 ? EOF : 0;
}
