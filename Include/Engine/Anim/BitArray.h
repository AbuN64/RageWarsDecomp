#ifndef ENGINE_ANIM_BITARRAY_H
#define ENGINE_ANIM_BITARRAY_H
#include "Engine/folded_constants.h"



extern float g_motionTrackDecodeRangeStart;
#include "Common/localdecoderange.h"
extern unsigned int Bitarray_GetWordBitOffset(unsigned int value);
extern u32 Bitarray_GetRequiredBitCount(s32 value);
extern const char g_animationText[];
#endif
