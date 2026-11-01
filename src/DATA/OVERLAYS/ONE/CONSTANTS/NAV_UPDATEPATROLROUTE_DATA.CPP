#include "TYPES.H"

#include "include_asm.h"

#if !(defined(VERSION_US))
/* ROM-grounded data: src/navUpdatepatrolrouteDataFloatConstantWords.c */
#if defined(VERSION_DE)
const f32 k_navUpdatepatrolrouteDataFloatConstantWords = 102.399994f;
#endif
#if defined(VERSION_EU)
const f32 k_navUpdatepatrolrouteDataFloatConstantWords = 102.399994f;
#endif
#if defined(VERSION_EU_X)
const f32 k_navUpdatepatrolrouteDataFloatConstantWords = 102.399994f;
#endif
#if defined(VERSION_US_REV1)
const f32 k_navUpdatepatrolrouteDataFloatConstantWords = 102.399994f;
#endif
#endif

#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
struct {
    u8 alignmentFill[12];
} k_NavUpdatepatrolrouteEncodedWordsBlock1 __attribute__((aligned(4))) = {
    { 0x3C, 0x8E, 0xFA, 0x36, 0x41, 0x80, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00 }
};
#endif
#endif

#if defined(VERSION_DE)
#if defined(VERSION_DE)
struct {
    u8 alignmentFill[12];
} k_NavUpdatepatrolrouteEncodedWords __attribute__((aligned(4))) = {
    { 0x42, 0x4C, 0xCC, 0xCC, 0xAF, 0xB1, 0x00, 0x14, 0x00, 0xC0, 0x88, 0x21 }
};
#endif
#endif
