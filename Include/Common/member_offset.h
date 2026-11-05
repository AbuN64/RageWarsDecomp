#ifndef COMMON_MEMBER_OFFSET_H
#define COMMON_MEMBER_OFFSET_H

/* Byte distance from the start of a structure to one of its members (the compilers here predate
 * __builtin_offsetof, so the address-of-null form is spelled once, here). */
#define MEMBER_OFFSET(type, member) ((int)((char *)&((type *)0)->member - (char *)0))

#endif
