#ifndef DEFS_DEFS_H
#define DEFS_DEFS_H
#include "types.h"
extern s32 Defs_TestBit(void *, s32);
extern void Defs_SetBitValue(u8 *, s32, s32);
extern s32 Defs_TestBit(void *bits, s32 bit);
u32 Defs_GetMemorySize(void);
#endif
