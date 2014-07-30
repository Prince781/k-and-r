// mallocf.h
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

#endif
