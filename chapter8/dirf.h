#ifndef DIRF_H
#define DIRF_H

#include <sys/types.h>

#ifndef DIRSIZ
#define DIRSIZ		255		// maximum name length
#endif

struct linux_dirent {
	long		d_ino;		// inode number
	off_t		d_off;		// offset to next linux_dirent
	unsigned short	d_reclen;	// length of this linux_dirent
	char		d_name[];	// filename (null-terminated)
				// length = d_reclen - 2
				// - offsetof(struct linux_dirent, d_name)
//	char		pad;		// zero padding byte
//	char		d_type;		// file type (since Linux 2.6.4)
};

#endif
