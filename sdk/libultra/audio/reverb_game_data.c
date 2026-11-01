#include "TYPES.H"
#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#include "COMMON/ALFXPARAM.H"

/* G_RESOURCESENCODEDWORDSBLOCK39.CPP */
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
/* 800C8DA4.CPP */
struct {
    u8 alignmentFill[12];
} g_ResourcesEncodedWordsBlock71 __attribute__((aligned(4))) = {
    { 0x3F, 0x5F, 0x66, 0xF4, 0x3F, 0x06, 0x0A, 0x93, 0x00, 0x00, 0x01, 0x00 }
};
#endif
#endif

/* SAVE.CPP */
#if defined(VERSION_US)
/* 800C7704.CPP */
struct {
    unsigned int w0[4];
    unsigned char b1[16];
    unsigned int w2[5];
} s_audioSaveText = {
    {
        0x0000000F, 0x5649445F, 0x4D4F4445, 0x45580000,
    },
    {
        0x61, 0x75, 0x64, 0x69, 0x6F, 0x2F, 0x73, 0x61, 0x76, 0x65, 0x2E, 0x63, 0x00, 0x00, 0x00, 0x00,
    },
    {
        0x00000F56, 0x49445F4D, 0x4F44455F, 0x3FF00000, 0x00000000,
    },
};
#endif

/* SAVE.CPP */
#if !(defined(VERSION_US_REV1))
const float k_saveFloatConstantWords[9] = {
    3.0e+01f, 0.0f, 5.7762263e-06f, 32768.0f, 3.0517578e-05f, 1.0f,
    2.0f, 4.0f, 1.0f,
};
#endif

#if defined(VERSION_DE)
char s_SaveAudioSaveCText[12] =
    "audio/save.c";
#endif

#if defined(VERSION_US_REV1)
const float k_saveFloatConstantWordsBlock1[3] = {
    3.0e+01f, 0.0f, 5.7762263e-06f,
};

/* ROM-grounded data: src/k_saveFloatConstantWordsBlock2_Save.c */
const float k_saveFloatConstantWordsBlock2[3] = {
    32768.0f, 3.0517578e-05f, 1.0f,
};

/* ROM-grounded data: src/k_saveFloatConstantWordsBlock3_Save.c */
const float k_saveFloatConstantWordsBlock3[3] = {
    2.0f, 4.0f, 1.0f,
};
#endif
