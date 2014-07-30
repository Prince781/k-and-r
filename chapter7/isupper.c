// section 7.8
// ex. 7-9: functions like isupper can be implemented to save space or to save
// time. Explore both possibilities.
#include <stdio.h>

// constants
#define ALPHA	0x001
#define DIGIT	0x002
#define SPACE	0x004
#define GRAPH	0x008
#define PUNCT	0x010
#define HXDIG	0x020
#define UPPER	0x040
#define LOWER	0x080
#define CNTRL	0x100
#define PRNTC	0x200

static const unsigned short cs[] = {
	CNTRL,							// NUL
	CNTRL,							// SOH
	CNTRL,							// STX
	CNTRL,							// ETX
	CNTRL,							// EOT
	CNTRL,							// ENQ
	CNTRL,							// ACK
	CNTRL,							// BEL
	CNTRL,							// BS
	CNTRL | SPACE,						// HT
	CNTRL | SPACE,						// LF
	CNTRL | SPACE,						// VT
	CNTRL | SPACE,						// FF
	CNTRL | SPACE,						// CR
	CNTRL,							// SO
	CNTRL,							// SI
	CNTRL,							// DLE
	CNTRL,							// DC1
	CNTRL,							// DC2
	CNTRL,							// DC3
	CNTRL,							// DC4
	CNTRL,							// NAK
	CNTRL,							// SYN
	CNTRL,							// ETB
	CNTRL,							// CAN
	CNTRL,							// EM
	CNTRL,							// SUB
	CNTRL,							// ESC
	CNTRL,							// FS
	CNTRL,							// GS
	CNTRL,							// RS
	CNTRL,							// US
	PRNTC | SPACE,						// SP
	PRNTC | GRAPH | PUNCT,					// !
	PRNTC | GRAPH | PUNCT,					// "
	PRNTC | GRAPH | PUNCT,					// #
	PRNTC | GRAPH | PUNCT,					// $
	PRNTC | GRAPH | PUNCT,					// %
	PRNTC | GRAPH | PUNCT,					// &
	PRNTC | GRAPH | PUNCT,					// '
	PRNTC | GRAPH | PUNCT,					// (
	PRNTC | GRAPH | PUNCT,					// )
	PRNTC | GRAPH | PUNCT,					// *
	PRNTC | GRAPH | PUNCT,					// +
	PRNTC | GRAPH | PUNCT,					// ,
	PRNTC | GRAPH | PUNCT,					// -
	PRNTC | GRAPH | PUNCT,					// .
	PRNTC | GRAPH | PUNCT,					// /
	PRNTC | GRAPH | HXDIG | DIGIT,				// 0
	PRNTC | GRAPH | HXDIG | DIGIT,				// 1
	PRNTC | GRAPH | HXDIG | DIGIT,				// 2
	PRNTC | GRAPH | HXDIG | DIGIT,				// 3
	PRNTC | GRAPH | HXDIG | DIGIT,				// 4
	PRNTC | GRAPH | HXDIG | DIGIT,				// 5
	PRNTC | GRAPH | HXDIG | DIGIT,				// 6
	PRNTC | GRAPH | HXDIG | DIGIT,				// 7
	PRNTC | GRAPH | HXDIG | DIGIT,				// 8
	PRNTC | GRAPH | HXDIG | DIGIT,				// 9
	PRNTC | GRAPH | PUNCT,					// :
	PRNTC | GRAPH | PUNCT,					// ;
	PRNTC | GRAPH | PUNCT,					// <
	PRNTC | GRAPH | PUNCT,					// =
	PRNTC | GRAPH | PUNCT,					// >
	PRNTC | GRAPH | PUNCT,					// ?
	PRNTC | GRAPH | PUNCT,					// @
	PRNTC | GRAPH | HXDIG | UPPER | ALPHA,			// A
	PRNTC | GRAPH | HXDIG | UPPER | ALPHA,			// B
	PRNTC | GRAPH | HXDIG | UPPER | ALPHA,			// C
	PRNTC | GRAPH | HXDIG | UPPER | ALPHA,			// D
	PRNTC | GRAPH | HXDIG | UPPER | ALPHA,			// E
	PRNTC | GRAPH | HXDIG | UPPER | ALPHA,			// F
	PRNTC | GRAPH | UPPER | ALPHA,				// G
	PRNTC | GRAPH | UPPER | ALPHA,				// H
	PRNTC | GRAPH | UPPER | ALPHA,				// I
	PRNTC | GRAPH | UPPER | ALPHA,				// J
	PRNTC | GRAPH | UPPER | ALPHA,				// K
	PRNTC | GRAPH | UPPER | ALPHA,				// L
	PRNTC | GRAPH | UPPER | ALPHA,				// M
	PRNTC | GRAPH | UPPER | ALPHA,				// N
	PRNTC | GRAPH | UPPER | ALPHA,				// O
	PRNTC | GRAPH | UPPER | ALPHA,				// P
	PRNTC | GRAPH | UPPER | ALPHA,				// Q
	PRNTC | GRAPH | UPPER | ALPHA,				// R
	PRNTC | GRAPH | UPPER | ALPHA,				// S
	PRNTC | GRAPH | UPPER | ALPHA,				// T
	PRNTC | GRAPH | UPPER | ALPHA,				// U
	PRNTC | GRAPH | UPPER | ALPHA,				// V
	PRNTC | GRAPH | UPPER | ALPHA,				// W
	PRNTC | GRAPH | UPPER | ALPHA,				// X
	PRNTC | GRAPH | UPPER | ALPHA,				// Y
	PRNTC | GRAPH | UPPER | ALPHA,				// Z
	PRNTC | GRAPH | PUNCT,					// [
	PRNTC | GRAPH | PUNCT,				// slant (\)
	PRNTC | GRAPH | PUNCT,					// ]
	PRNTC | GRAPH | PUNCT,					// ^
	PRNTC | GRAPH | PUNCT,					// _
	PRNTC | GRAPH | PUNCT,					// `
	PRNTC | GRAPH | HXDIG | LOWER | ALPHA,			// a
	PRNTC | GRAPH | HXDIG | LOWER | ALPHA,			// b
	PRNTC | GRAPH | HXDIG | LOWER | ALPHA,			// c
	PRNTC | GRAPH | HXDIG | LOWER | ALPHA,			// d
	PRNTC | GRAPH | HXDIG | LOWER | ALPHA,			// e
	PRNTC | GRAPH | HXDIG | LOWER | ALPHA,			// f
	PRNTC | GRAPH | LOWER | ALPHA,				// g
	PRNTC | GRAPH | LOWER | ALPHA,				// h
	PRNTC | GRAPH | LOWER | ALPHA,				// i
	PRNTC | GRAPH | LOWER | ALPHA,				// j
	PRNTC | GRAPH | LOWER | ALPHA,				// k
	PRNTC | GRAPH | LOWER | ALPHA,				// l
	PRNTC | GRAPH | LOWER | ALPHA,				// m
	PRNTC | GRAPH | LOWER | ALPHA,				// n
	PRNTC | GRAPH | LOWER | ALPHA,				// o
	PRNTC | GRAPH | LOWER | ALPHA,				// p
	PRNTC | GRAPH | LOWER | ALPHA,				// q
	PRNTC | GRAPH | LOWER | ALPHA,				// r
	PRNTC | GRAPH | LOWER | ALPHA,				// s
	PRNTC | GRAPH | LOWER | ALPHA,				// t
	PRNTC | GRAPH | LOWER | ALPHA,				// u
	PRNTC | GRAPH | LOWER | ALPHA,				// v
	PRNTC | GRAPH | LOWER | ALPHA,				// w
	PRNTC | GRAPH | LOWER | ALPHA,				// x
	PRNTC | GRAPH | LOWER | ALPHA,				// y
	PRNTC | GRAPH | LOWER | ALPHA,				// z
	PRNTC | GRAPH | PUNCT,					// {
	PRNTC | GRAPH | PUNCT,					// |
	PRNTC | GRAPH | PUNCT,					// }
	PRNTC | GRAPH | PUNCT					// DEL
};

#define isupper1(c) ((cs)[(unsigned)(c)] & UPPER)	// saves time
#define isspace1(c) ((cs)[(unsigned)(c)] & SPACE)
int isupper2(int);					// saves space
int isspace2(int);

int main() {
	char ln[1000], *lnp;
	while (fgets(ln,1000,stdin) != NULL)
		for (lnp=ln; *lnp && *lnp != '\n'; ++lnp) {
			printf("%c is %suppercase\n", *lnp,
				isupper1(*lnp) ? "" : "not ");
			printf("%c is %sspace\n", *lnp,
				isspace1(*lnp) ? "" : "not ");
			printf("%c is %suppercase\n", *lnp,
				isupper2(*lnp) ? "" : "not ");
			printf("%c is %sspace\n", *lnp,
				isspace2(*lnp) ? "" : "not ");
		}
	return 0;
}

// determine if char is uppercase, saving space
int isupper2(int c) {
	return c >= 'A' && c <= 'Z';
}

int isspace2(int c) {
	return c == ' ' || c == '\n' || c == '\t' || c == '\f' || c == '\v'
		|| c == '\r';
}
