#ifndef ENGINE_DEFS_H
#define ENGINE_DEFS_H
#include "TYPES.H"
#include "COMMON/LIGHTDATA.H"

struct LightNode {
    char pad0[8];
    LightData *data;
    f32 intensity;
    s16 position[3];
    s16 active;
};

extern s32 Defs_FindSortedGroupRange(u32 *, s32, u32 group, s32 *, s32 *last);
extern int Defs_GetBitArrayByteCount(int);
extern void Defs_ToggleBit(s32, s32);
extern f32 Defs_CosineEase(f32 fraction);
extern int Defs_IsAddressInBufferRanges(u32 address);
extern void Defs_NoOperation(void);
extern void Defs_FormatIntegerValue(char *buffer, const char *format, s32 value);
extern void Defs_FormatSingleInteger(char *buffer, const char *format, s32 value);
extern void Defs_FormatThreeIntegers(char *buffer, const char *format, s32 a, s32 b, s32 c);
extern void Defs_FormatFourIntegers(char *buffer, const char *format, s32 a, s32 b, s32 c, s32 d);
extern s32 Defs_ReadResourceWord(s32);
#endif
