#include "TYPES.H"

#include "include_asm.h"

/* ROM-grounded data: src/ALCSEQSECTOTICKS_ENCODED_WORDS_US_REV1.c */
#if defined(VERSION_DE)
const f32 k_AlcseqsectoticksEncodedWords[3] = {
    30.0f, 0.0f, 2.14748365e+09f
};
#endif
#if defined(VERSION_EU)
const f32 k_AlcseqsectoticksEncodedWords[3] = {
    30.0f, 0.0f, 2.14748365e+09f
};
#endif
#if defined(VERSION_EU_X)
const f32 k_AlcseqsectoticksEncodedWords[3] = {
    30.0f, 0.0f, 2.14748365e+09f
};
#endif
#if defined(VERSION_US)
const f32 k_AlcseqsectoticksEncodedWords[3] = {
    30.0f, 0.0f, 2.14748365e+09f
};
#endif
#if defined(VERSION_US_REV1)
const f32 k_AlcseqsectoticksEncodedWords[3] = {
    30.0f, 0.0f, 2.14748365e+09f
};
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    u8 alignmentFill[12];
} k_AlcseqsectoticksEncodedWordsBlock1 __attribute__((aligned(4))) = {
    { 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x43, 0x46, 0x72, 0x61, 0x6D }
};
#endif
#endif

#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
struct {
    u8 alignmentFill[12];
} k_AlcseqsectoticksEncodedWordsBlock3 __attribute__((aligned(4))) = {
    { 0x00, 0x27, 0x91, 0xAC, 0x00, 0x27, 0x91, 0xEC, 0x00, 0x27, 0x90, 0xF0 }
};
#endif
#endif

#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    u8 alignmentFill[12];
} k_AlcseqsectoticksEncodedWordsBlock2 __attribute__((aligned(4))) = {
    { 0x00, 0x22, 0x9E, 0xD8, 0x00, 0x22, 0x9E, 0xE0, 0x00, 0x22, 0x9E, 0xE8 }
};
#endif
#endif

#if defined(VERSION_DE)
char s_AlcseqsectoticksAudioCsplayText[12] =
    "audio/csplay";
#endif
