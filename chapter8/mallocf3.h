// mallocf3.h
#ifndef MALLOCF_H
#define MALLOCF_H

typedef long Align;	// for alignment to long boundary

union header {		// defines a block of memory
	struct {
		union header *ptr;	// points to next block on free list
		unsigned size;		// size of current block
	} s;
	Align x;	// force alignment of blocks
};

typedef union header Header;

// storage allocator
void		*mallocf	(unsigned);

// storage allocator with data zero-initialized
void		*callocf	(unsigned, unsigned);

// free a block of storage
void		freef		(void *);

// free a block of n bytes of storage
void		bfreef		(void *, unsigned);

#define HSIZE		sizeof(Header)
#define MALLOCF_DEBUG	0	// debug or not

// get number of header units from bytes
#define __getunits(nb)	(((nb)+HSIZE-1) / HSIZE + 1)

// get an aligned pointer
#define __ptralign(p,b)	((void *)((size_t)((void *)(p)+((b)-1)) & ~((b)-1)))

#endif
