#ifndef COMMON_LIGHTDATA_H
#define COMMON_LIGHTDATA_H
#include "TYPES.H"

extern float g_cosineEaseAngleScale;

struct LightData;
struct LightData {
    u16 falloff;
    u16 near;
    u8 color[4];
};

struct LightData;
typedef struct LightData LightData;

struct LightNode;

extern int Defs_IsAddressInBufferRanges(u32 address);

struct UnitLight;
typedef struct UnitLight UnitLight;

extern int Defs_GetBitArrayByteCount(int bitCount);


struct UnitLight;
struct UnitLight {
    s16 dir[3];
    u8 color[4];
    s16 falloff;
    u16 near;
    u16 range;
};

extern void Defs_ToggleBit(s32 bits, s32 bitIndex);

extern float g_cosineEaseUpperBound;

struct LightNode;
typedef struct LightNode LightNode;

extern float g_cosineEaseOutputConstants;

extern f32 Defs_CosineEase(f32 fraction);

extern void Defs_NoOperation(void);
#endif
