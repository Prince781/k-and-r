// section 8.3
// ex. 8-1: rewrite the program cat from Chapter 7 using read, write, open, and
// close instead of their standard library equivalents. Perform experiments to
// determine the relative speeds of the two versions.
#include <fcntl.h>

#define BUFSIZE	4096

// cat: concatenate files to stdout
int main(int argc, char *argv[]) {
	int n;
	char buf[BUFSIZE];
	int fd;

	if (argc == 1) {
		while ((n = read(0, buf, BUFSIZE)) > 0)
			if (write(1, buf, n) == -1)
				write(2, "cat: write error\n", 17);
		if (n == -1)
			write(2, "cat: read error\n", 16);
		return !!n;
	} else
		while (--argc > 0) {
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				write(2, "cat: read error\n", 16);
				return 1;
			}
			while ((n = read(fd, buf, BUFSIZE)) > 0)
				if (write(1, buf, n) == -1)
					write(2, "cat: write error\n", 17);
			if (n == -1) {
				write(2, "cat: read error\n", 16);
				return 1;
			} else
				close(fd);
		}
	return 0;
}
