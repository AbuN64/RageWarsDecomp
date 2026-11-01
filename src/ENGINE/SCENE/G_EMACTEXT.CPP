#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"

/* g_GEmactextEncodedWords_GEmactext.CPP */
/* ROM-grounded data: rodata/writable/800D2930 */
s32 g_GEmactextEncodedWords[1] = {
    1,
};

/* g_emacText.CPP */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
RestemacTextLayout324 g_emacText = {
    { 0, 0 },
    { 1.5f, 0.0f, 15.0f },
    { 65280, 20 },
};
#endif
#if defined(VERSION_EU)
unsigned short g_emacText[14] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x3FC0, 0x0000, 0x0000, 0x0000, 0x4170, 0x0000, 0x0000, 0xFF00,
    0x8011, 0x00B0,
};
#endif
#if defined(VERSION_EU_X)
RestemacTextLayout325 g_emacText = {
    { 0, 0 },
    { 1.5f, 0.0f, 15.0f },
    { 65280, 0 },
};
#endif
#if defined(VERSION_US)
RestemacTextLayout326 g_emacText = {
    { 0, 0 },
    { 1.5f, 0.0f, 15.0f },
    65280,
    "HRIN",
};
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded exact candidate, normalized from prior lane proof. */
struct {
    unsigned int w0;
    unsigned char b1[4];
    unsigned int w2;
    unsigned char b3[4];
    unsigned int w4;
    unsigned char b5[4];
    unsigned int w6;
} g_emacText = {
    0x00000000,
    {
        0x00, 0x00, 0x00, 0x00,
    },
    0x3FC00000,
    {
        0x00, 0x00, 0x00, 0x00,
    },
    0x41700000,
    {
        0x00, 0x00, 0xFF, 0x00,
    },
    0x454D4143,
};
#endif
