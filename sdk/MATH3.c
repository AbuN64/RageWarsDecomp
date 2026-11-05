#include "include_asm.h"
#include <platform_sdk.h>
#include "Common/runtime_declarations.h"
#include "Common/triple.h"
#include "Common/gumtxl2f.h"
#include "Common/alfxparam.h"

/* aisetfreq.CPP */
 /* 0.5, followed by 2^31 */

s32 osAiSetFrequency(u32 frequency)
{
    register unsigned int dacRate;
    register unsigned char bitRate;
    register float f;
    f64 wide;
    float clock;

    wide = (s32)frequency;
    clock = g_audioClockRate;
    if ((s32)frequency < 0) {
        wide += g_audioFrequencyUnsignedConversionBias;
    }
    f = clock / (float)wide + g_audioDacRateRoundingBias;
    if (f >= g_audioDacRateUnsignedConversionLimit) {
        goto large;
    }
    dacRate = (s32)f;
    goto converted;
large:
    dacRate = (s32)(f - g_audioDacRateUnsignedConversionLimit);
    dacRate |= 0x80000000;
converted:

    if (dacRate < 132) {
        return -1;
    }

    bitRate = dacRate / 66;
    if (bitRate > 16) {
        bitRate = 16;
    }

    IO_WRITE(0xA4500010U, dacRate - 1);
    IO_WRITE(0xA4500014U, bitRate - 1);
    IO_WRITE(0xA4500008U, 1);
    return g_audioClockRate / (s32)dacRate;
}

/* ROM-grounded data: src/os_ai_set_frequency_constant_words_us_rev1.c */
const unsigned int g_osAiSetFrequencyConstantWords[4] = {
    0x41F00000, 0x00000000, 0x3F000000, 0x4F000000,
};
