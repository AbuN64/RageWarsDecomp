#ifndef COMMON_H
#define COMMON_H
#include "TYPES.H"

/* Decodes a float stored as its high 16 bits. */
extern f32 Menu_ExpandFloatHighWord(s32);
extern f32 Menu_ExpandFloatHighWord(s32);
#if defined(VERSION_EU)
#define RW_BITS_TO_FLOAT Menu_ExpandFloatHighWord
#else
#define RW_BITS_TO_FLOAT Menu_ExpandFloatHighWord
#endif
#endif
