#include "types.h"
#include "Engine/curve.h"
#include "Common/effectrender.h"
#include "Data/rest_source_records.h"
#include "include_asm.h"
#include "Data/Enemy/curve_decodethreebitsamples_data.h"
#include <platform_sdk.h>
#include <PR/gbi.h>

/* CURVE.CPP */

/* Two LSB-first bit streams, each a 32-bit window, its count of valid bits and the next byte to load:
 * g_curvePredictorBitWindow.. carries the 6-bit predictor codes, g_curveSampleBitWindow.. the 3-bit sample deltas. */

/* Q16 predictor coefficient pairs, indexed by the top 2 bits of a predictor code. */

/* Drops width bits from the sample bit stream and refills it a byte at a time. */
static inline void skip_sample_bits(s32 width) {
    u32 previous = g_curveSampleBitWindow;
    s32 available = g_curveSampleBitCount_de;
    s32 remaining = available - width;
    u32 shifted = previous >> width;
    g_curveSampleBitWindow = shifted;
    g_curveSampleBitCount_de = remaining;
    if (remaining < 25) {
        u8 *cursor = g_curveSampleByteCursor;
        u32 next = *cursor++;
        g_curveSampleByteCursor = cursor;
        g_curveSampleBitCount_de = remaining + 8;
        g_curveSampleBitWindow = shifted | (next << remaining);
    }
}

/* Takes the next 6-bit predictor code (2-bit coefficient pair index, 4-bit shift) from the control stream. */
static inline u32 read_predictor_code(void) {
    u32 previous = g_curvePredictorBitWindow;
    u32 bits = previous & 63;
    s32 available = g_curvePredictorBitCount;
    s32 remaining = available - 6;
    u32 shifted = previous >> 6;
    g_curvePredictorBitWindow = shifted;
    g_curvePredictorBitCount = remaining;
    if (remaining < 25) {
        u8 *cursor = g_curvePredictorByteCursor;
        u32 next = *cursor++;
        g_curvePredictorByteCursor = cursor;
        g_curvePredictorBitCount = remaining + 8;
        g_curvePredictorBitWindow = shifted | (next << remaining);
    }
    return bits;
}

/* Takes a signed width-bit delta from the sample stream and scales it by 1 << shift. */
static inline s32 read_scaled_delta(s32 width, s32 shift) {
    u32 mask = (1U << width) - 1;
    u16 encoded = (u16)g_curveSampleBitWindow;
    s32 value = encoded & mask;
    skip_sample_bits(width);
    if (encoded & ((mask + 1) >> 1)) {
        return (s16)(value | ~mask) * (1 << shift);
    }
    return value * (1 << shift);
}

/* Decodes count samples: each group of 4 takes a 6-bit predictor code (2-bit coefficient pair
 * index, 4-bit shift) from the control stream, each sample a 3-bit delta from the sample stream.
 * The scaled delta plus the two-tap prediction is integrated into a running sample clamped to 16 bits. */
void Curve_DecodeThreeBitSamples(s16 *out, s32 count) {
    s32 previous = 0;
    s32 older = 0;
    s32 sample;
    u8 head = (u8)g_curveSampleBitWindow;
    s32 group = 0;
    s32 shift;
    s32 first, second;
    s32 delta, predicted, clamped, total;
    u32 code;
    u8 range;
    u32 word;
    skip_sample_bits(8);
    sample = (s8)head * 256;
    while (count-- > 0) {
        if (group-- == 0) {
            group = 3;
            word = g_curvePredictorBitWindow;
            code = read_predictor_code();
            range = word & 15;
            word = code;
            shift = range;
            first = g_curvePredictorShortLagCoefficients[word >> 4];
            second = g_curvePredictorLongLagCoefficients[word >> 4];
        }
        delta = read_scaled_delta(3, shift);
        predicted = previous * first + older * second;
        older = previous;
        delta += predicted >> 16;
        previous = delta;
        total = sample + delta;
        sample = total;
        if (total <= 32767) {
            clamped = total;
        } else {
            clamped = 32767;
        }
        total = clamped;
        clamped = -32768;
        if (total >= -32768) {
            clamped = total;
        }
        *out++ = clamped;
    }
}

/* Initializes the packed control and sample bit streams, then decodes each output channel. */
s32 Curve_DecodePackedChannels(s32 *channels, void *encoded, s32 channelCount) {
    u8 *packed = (u8 *)encoded;
    s32 sampleCount;
    s32 controlBits;
    s32 shift;
    u8 *sampleBytes;
    u8 *cursor;
    s32 i;
    u32 lastByte;

    sampleCount = *packed++ << 8;
    sampleCount |= *packed++;
    controlBits = ((sampleCount + 3) / 4) * 6;
    sampleBytes = packed + controlBits / 8;
    g_curveSampleBitWindow = sampleBytes[0];
    g_curveSampleBitWindow |= sampleBytes[1] << 8;
    g_curveSampleBitWindow |= sampleBytes[2] << 16;
    shift = controlBits & 7;
    lastByte = sampleBytes[3];
    lastByte <<= 24;
    g_curveSampleBitCount_de = 32 - shift;
    g_curveSampleByteCursor = sampleBytes + 4;
    g_curveSampleBitWindow = (g_curveSampleBitWindow | lastByte) >> shift;

    for (i = 0; i < channelCount; i++) {
        u32 tail;
        cursor = packed;
        g_curvePredictorBitWindow = *cursor++;
        g_curvePredictorBitWindow |= *cursor++ << 8;
        g_curvePredictorBitWindow |= *cursor++ << 16;
        tail = *cursor++;
        g_curvePredictorBitCount = 32;
        g_curvePredictorByteCursor = cursor;
        tail <<= 24;
        g_curvePredictorBitWindow |= tail;
        Curve_DecodeThreeBitSamples((s16 *)channels[i], sampleCount);
    }
    return sampleCount;
}

/* CURVE_DECODETHREEBITSAMPLES_DATA.CPP */

#if defined(VERSION_DE)
CurveDecodethreebitsamplesEncodedWordsLayout313 k_CurveDecodethreebitsamples = {
    { 0, 61440, 124928, 117760, 0, 0, -61440, -53248 },
    { &g_threadLabelWordsGerman[0x5C], &g_threadLabelWordsGerman[0x54], &g_threadLabelWordsGerman[0x4C], &g_threadLabelWordsGerman[0x3C], &g_threadLabelWordsGerman[0x34], &g_threadLabelWordsGerman[0x2C], &g_threadLabelWordsGerman[0x20], &g_threadLabelWordsGerman[0x14], &g_threadLabelWordsGerman[0xC], 0 },
    { -1, 10273 }
};
#endif

#if defined(VERSION_EU)
CurveDecodethreebitsamplesEncodedWordsLayout314 k_CurveDecodethreebitsamples = {
    { 0, 61440, 124928, 117760, 0, 0, -61440, -53248 },
    { &g_threadLabelWordsEuropean[0x5C], &g_threadLabelWordsEuropean[0x54], &g_threadLabelWordsEuropean[0x4C], &g_threadLabelWordsEuropean[0x3C], &g_threadLabelWordsEuropean[0x34], &g_threadLabelWordsEuropean[0x2C], &g_threadLabelWordsEuropean[0x20], &g_threadLabelWordsEuropean[0x14], &g_threadLabelWordsEuropean[0xC], 0 },
    -1,
    "FAMI"
};
#endif

#if defined(VERSION_EU_X)
CurveDecodethreebitsamplesEncodedWordsLayout315 k_CurveDecodethreebitsamples = {
    { 0, 61440, 124928, 117760, 0, 0, -61440, -53248 },
    { &g_threadLabelWordsEuropeanX[0x5C], &g_threadLabelWordsEuropeanX[0x54], &g_threadLabelWordsEuropeanX[0x4C], &g_threadLabelWordsEuropeanX[0x3C], &g_threadLabelWordsEuropeanX[0x34], &g_threadLabelWordsEuropeanX[0x2C], &g_threadLabelWordsEuropeanX[0x20], &g_threadLabelWordsEuropeanX[0x14], &g_threadLabelWordsEuropeanX[0xC], 0 },
    -1,
    1.000847f
};
#endif

#if defined(VERSION_US)
CurveDecodethreebitsamplesEncodedWordsLayout316 k_CurveDecodethreebitsamples = {
    { 0, 61440, 124928, 117760, 0, 0, -61440, -53248 },
    { &g_threadLabelWordsUs[0x5C], &g_threadLabelWordsUs[0x54], &g_threadLabelWordsUs[0x4C], &g_threadLabelWordsUs[0x3C], &g_threadLabelWordsUs[0x34], &g_threadLabelWordsUs[0x2C], &g_threadLabelWordsUs[0x20], &g_threadLabelWordsUs[0x14], &g_threadLabelWordsUs[0xC], 0 },
    -1,
    "INI_"
};
#endif

#if defined(VERSION_US_REV1)
CurveDecodethreebitsamplesEncodedWordsLayout317 g_CurveDecodethreebitsamples = {
    { 0, 61440, 124928, 117760, 0, 0, -61440, -53248 },
    { &g_threadLabelWordsUsRevision[92], &g_threadLabelWordsUsRevision[84], &g_threadLabelWordsUsRevision[76], &g_threadLabelWordsUsRevision[60], &g_threadLabelWordsUsRevision[52], &g_threadLabelWordsUsRevision[44], &g_threadLabelWordsUsRevision[32], &g_threadLabelWordsUsRevision[20], &g_threadLabelWordsUsRevision[12], 0 },
    -1
};
#endif

/* DEFS_TOGGLESAVEDFLAG_DATA.CPP */

#if defined(VERSION_DE)
struct {
    unsigned int leadingWords;
    unsigned char colorBytes[32];
} g_savedFlagToggleStorage = {
    0x00000000,
    {
        0x38, 0x38, 0x38, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x38, 0x38, 0x38, 0x00,
        0x38, 0x38, 0x38, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xD6, 0x1E, 0xDC, 0x00,
    },
};
#endif

#if defined(VERSION_EU)
struct {
    unsigned int leadingWords[4];
    unsigned char colorBytes[20];
} g_savedFlagToggleStorage = {
    {
        0x00000000, 0x00000000, 0x4E4F5553, 0x20564F55,
    },
    {
        0x38, 0x38, 0x38, 0x00, 0x38, 0x38, 0x38, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
        0xD6, 0x1E, 0xDC, 0x00,
    },
};
#endif

#if defined(VERSION_EU_X)
struct {
    unsigned int leadingWords[4];
    unsigned char colorBytes[20];
} g_savedFlagToggleStorage = {
    {
        0x00000000, 0x3F7F9F36, 0x3F7F52FA, 0x3F7F06B0,
    },
    {
        0x38, 0x38, 0x38, 0x00, 0x38, 0x38, 0x38, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
        0xD6, 0x1E, 0xDC, 0x00,
    },
};
#endif

#if defined(VERSION_US)
struct {
    unsigned int leadingWords[4];
    unsigned char colorBytes[20];
} g_savedFlagToggleStorage = {
    {
        0x00000000, 0x52454144, 0x59657175, 0x5200006C,
    },
    {
        0x38, 0x38, 0x38, 0x00, 0x38, 0x38, 0x38, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
        0xD6, 0x1E, 0xDC, 0x00,
    },
};
#endif

/* PLAYERAI_BUILDFORCEMARKERTRANSFORM_DATA.CPP */

/* Light colour bytes (r, g, b, pad): bytes so every host reads the same colour. */
const char k_PlayeraiBuildforcemarkertransformEncodedBytes[4] = "888";

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const char k_playeraiForceMarkerLightColorWord[4] = "888";
#endif

/* PAK_ADJUSTOWNERNOTIFICATIONOPTION_DATA.CPP */
#if defined(VERSION_US_REV1)
/* Nine words, then the ambient light, the diffuse light and its direction as bytes (read bytewise by the RSP). */
struct {
    unsigned int words[9];
    unsigned char lights[20];
} g_enemyMixWordsAndLights = {
    { 0x00000001, 0x3F800000, 0x3F8067C9, 0x3F8041C9, 0x3F801BC1, 0x00000000, 0x3F7F9F36, 0x3F7F52FA,
      0x3F7F06B0 },
    { 0x38, 0x38, 0x38, 0x00, 0x38, 0x38, 0x38, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
      0xD6, 0x1E, 0xDC, 0x00 },
};
s32 g_notificationOptionZero[1] = {
    0,
};
#endif

/* ENEMY.CPP */
#if defined(VERSION_US_REV1)


/* Light colour bytes (r, g, b, pad): bytes so every host reads the same colour. */
const char k_enemyTextBytes[4] = "888";
#endif
