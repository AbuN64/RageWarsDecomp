#ifndef UI_SMP_H
#define UI_SMP_H
#include "types.h"
#include "Common/runtime_declarations.h"
struct GameImage;
extern s32 Smp_CopyAndSwizzleImage(struct GameImage *dst, struct GameImage *src);
extern void Smp_SetImageStateWord(s32 flag);
#endif
