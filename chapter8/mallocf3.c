// section 8.7
// ex. 8-8: write a routine bfreef(p,n) that will free an arbitrary block p of
// n characters into the free list maintained by mallocf and freef. By using
// bfreef, a user can add a static or external array to the free list at any
// time.
#include <stdio.h>
#include <unistd.h>
#include "mallocf3.h"

#define NALLOC		1024	// minimum units to request from system
#ifdef MALLOCF_DEBUG
#	undef MALLOCF_DEBUG
#endif
#define MALLOCF_DEBUG	1

static unsigned long tsize = 0;	// total number of units allocated
static Header base;		// empty list
static Header *freep = NULL;	// start of free list

static Header *morecore(unsigned);

// mallocf: general-purpose storage allocator
void *mallocf(unsigned nbytes) {
	Header *p, *prevp;
	unsigned nunits;

	if (nbytes == 0)
		return NULL;
	// size = (ceil nbytes to # of blocks) + 1 block for header
	nunits = __getunits(nbytes);
	if ((prevp = freep) == NULL) {	// no free list yet
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	// jump from position to next position pointed to indefinitely
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {	// free chunk is large enough
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);	// position after header
		}
		if (p == freep)			// wrapped around free list
			if ((p = morecore(nunits)) == NULL)
				return NULL;	// nothing left
	}
	return NULL;
}

// callocf: allocate bytes and then initialize them to 0
void *callocf(unsigned n, unsigned size) {
	unsigned nbytes = n*size;

	char *p, *strp;
	if ((p = mallocf(nbytes)) == NULL)
		return NULL;
	for (strp=p; nbytes-- > 0; strp++)
		*strp = 0;
	return (void *)p;
}

// morecore: ask system for more memory
static Header *morecore(unsigned nu) {
	char *cp;
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * HSIZE);
	if (cp == (char *) -1)		// no space left
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	tsize += nu;
	freef((void *)(up+1));
	return freep;
}

// free: put block ap in free list
void freef(void *ap) {
	/* free block of memory; if there is a neighboring free block, combine
	 * it with this one
	 */
	Header *bp, *p;

	bp = (Header *)ap - 1;		// point to block header
	if (ap < (void *)HSIZE) {
		fprintf(stderr, "freef: invalid pointer given\n");
		return;
	}
	// jump around until we find a range that bp is in
	// if bp is outside of the list, break and put at start/end
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;

	if (bp->s.size > tsize) {
		fprintf(stderr, "freef: block size > total\n");
		return;
	}
	if (bp + bp->s.size == p->s.ptr) {	// join to upper
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else				// otherwise point to somewhere on the
		bp->s.ptr = p->s.ptr;	// list
	if (p + p->s.size == bp) {	// join to lower
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;		// otherwise complete the list by
	freep = p;			// connecting the other element
}

// bfreef: free a block p of n characters (bytes) into the free list
void bfreef(void *p, unsigned n) {
	void *ptr;
	unsigned nunits;
	Header *bp;
	
	ptr = __ptralign(p,HSIZE);
	nunits = ((p+n) - ptr) / HSIZE;
	if (n < HSIZE) {
		fprintf(stderr, "bfreef: block size is too small\n");
		return;
	} else if (ptr+HSIZE > p+n) {
		fprintf(stderr, "bfreef: not enough space after alignment\n");
		if (MALLOCF_DEBUG)
			printf("\tp = %p\n\tptr = %p\n", p, ptr);
		return;
	}

	if (MALLOCF_DEBUG)
		printf("bfreef: using %u units for %u bytes\n", nunits, n);
	
	bp = (Header *)ptr;
	bp->s.size = nunits;

	freef(bp+1);
}
