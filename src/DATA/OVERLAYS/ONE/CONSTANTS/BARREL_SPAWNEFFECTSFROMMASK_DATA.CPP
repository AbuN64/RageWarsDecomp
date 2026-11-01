#include "TYPES.H"

#include "include_asm.h"

/* ROM-grounded data: src/k_barrelSpawneffectsfrommaskDataFloatConstantWords_BarrelSpawneffectsfrommaskData.c */
const float k_barrelSpawneffectsfrommaskDataFloatConstantWords[2] = {
    4.5e+02f, 6.0e+02f,
};

#if defined(VERSION_US)
char s_BarrelSpawneffectsfrommaskCBHoleTTText[12] =
    "CBHole_tT\000\000\000";
#endif

#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
struct {
    u8 alignmentFill[12];
} k_BarrelSpawneffectsfrommaskEncodedWordsBlock2 __attribute__((aligned(4))) = {
    { 0x00, 0x00, 0x00, 0x00, 0x41, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};
#endif
#endif

#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    u8 alignmentFill[12];
} k_BarrelSpawneffectsfrommaskEncodedWordsBlock1 __attribute__((aligned(4))) = {
    { 0x3C, 0x01, 0xFF, 0xFF, 0x34, 0x21, 0x00, 0xFF, 0x01, 0x81, 0x60, 0x24 }
};
#endif
#endif

#if defined(VERSION_DE)
#if defined(VERSION_DE)
struct {
    u8 alignmentFill[12];
} k_BarrelSpawneffectsfrommaskEncodedWords __attribute__((aligned(4))) = {
    { 0x3F, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x3B, 0x4C, 0xCC, 0xCD }
};
#endif
#endif
