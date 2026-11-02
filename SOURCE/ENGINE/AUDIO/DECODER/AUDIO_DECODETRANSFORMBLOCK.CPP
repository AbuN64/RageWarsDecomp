#include "include_asm.h"
#include "COMMON/TRIPLE.H"
#include "COMMON/LLDIVRESULT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "AUDIO/audio_decodetransformblock.H"

/* Builds the decoder's trigonometric tables: for 128 steps it stores the sine and cosine of
   (i * g_audioTransformCoefficientStep + g_audioTransformCoefficientOffset) * g_audioTransformPrimaryScale in g_audioTransformSines and g_audioTransformCosines and clears g_audioTransformZeros,
   then for 128 steps of i * g_audioTransformSecondaryScale stores sine plus cosine in g_audioTransformSums and cosine minus sine in
   g_audioTransformDifferences. */


void Audio_InitTransformTables(void) {
    s16 i;
    f32 angle;
    f32 s;
    f32 c;
    f32 step;
    f32 offset;
    f32 scale;
    f32 *sines;
    f32 *cosines;
    f32 *zeros;
    f32 *sums;
    f32 *differences;
    step = g_audioTransformCoefficientStep;
    offset = g_audioTransformCoefficientOffset;
    scale = g_audioTransformPrimaryScale;
    i = 0;
    sines = g_audioTransformSines;
    cosines = g_audioTransformCosines;
    zeros = g_audioTransformZeros;
    for (; i < 128; i++) {
        angle = (i * step + offset) * scale;
        sines[i] = Math_Cosf(angle);
        cosines[i] = Gu_Sinf(angle);
        zeros[i] = 0.0f;
    }
    i = 0;
    scale = g_audioTransformSecondaryScale;
    sums = g_audioTransformSums;
    differences = g_audioTransformDifferences;
    for (; i < 128; i++) {
        angle = i * scale;
        s = Math_Cosf(angle);
        c = Gu_Sinf(angle);
        sums[i] = s + c;
        differences[i] = c - s;
    }
}
/* Prepares the FFT tables in g_audioTransformBandTables for n points: fills the first n / 2 entries of the sine and
   negated cosine tables for angles i * g_audioTransformTertiaryScale / n, fills the order table with 0..n - 1 and
   bit-reverses it with the standard index-swapping walk, records n and returns the tables. */


FftTables *Audio_InitFftTables(s32 n) {
    FftTables *tables;
    s32 half;
    s32 i;
    s32 k;
    s32 j;
    s32 m;
    s32 swap;
    s32 limit;
    s32 *order;
    f32 angle;
    f32 scale;
    f32 count;
    half = n >> 1;
    tables = &g_audioTransformBandTables;
    i = 0;
    if (i < half) {
        scale = g_audioTransformTertiaryScale;
        count = n;
        do {
            angle = i * scale / count;
            tables->sines[i] = Math_Cosf(angle);
            tables->cosines[i] = -Gu_Sinf(angle);
            i++;
        } while (i < half);
    }
    order = tables->order;
    limit = n * 2;
    for (k = 0; k < n; k++) {
        order[k] = k;
    }
    j = 1;
    for (k = 1; k <= limit; k += 2) {
        if (k < j) {
            swap = order[(j - 1) / 2];
            order[(j - 1) / 2] = order[(k - 1) / 2];
            order[(k - 1) / 2] = swap;
        }
        m = n;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
    tables->size = n;
    return tables;
}
/* Dequantises 256 coefficients: for each of the 16 bands, whose end indices are in g_audioTransformBandEnds,
   every coefficient is the quantised value at offset 0xA0 of the input divided by the step
   g_audioTransformBandSteps selected by the band's scale index and multiplied by the gain g_audioTransformOutputGain; the
   coefficients past the last band end (g_audioTransformFirstUpperBand) are cleared. Returns 1. */
s32 Audio_DequantizeTransformCoefficients(f32 *out, s16 *in) {
    s16 *scale;
    s16 band;
    s16 i;
    s16 start;
    s16 *values;
    u16 *ends;
    f32 *steps;
    f32 gain;
    start = 0;
    values = ((TransformAudioFrame *)in)->coefficients;
    band = 0;
    ends = g_audioTransformBandEnds;
    steps = g_audioTransformBandSteps;
    gain = g_audioTransformOutputGain;
    for (; band < 16; band++) {
        for (i = start; i < ends[band]; i++) {
            out[i] = (f32)values[i] / steps[*(scale = &in[band])] * gain;
        }
        start = ends[band];
    }
    for (band = g_audioTransformFirstUpperBand; band < 256; band++) {
        out[band] = 0.0f;
    }
    return 1;
}

void Audio_ComplexFft(f32 *data, s32 count, s32 sign, f32 *cosines, f32 *sines, s32 *reverse) {
    s32 i, j, k;
    s32 width, groups, n, m;
    f32 real, imag, co, si;
    for (i = 0; i < count; i++) {
        if (i < reverse[i]) {
            real = data[i * 2];
            data[i * 2] = data[reverse[i] * 2];
            data[reverse[i] * 2] = real;
            real = data[i * 2 + 1];
            data[i * 2 + 1] = data[reverse[i] * 2 + 1];
            data[reverse[i] * 2 + 1] = real;
        }
    }
    width = 2;
    groups = 1;
    n = count >> groups;
    count <<= groups;
    while (n > 0) {
        m = 0;
        for (j = 0; j < groups; j++) {
            co = cosines[m];
            si = sign * sines[m];
            for (k = j * 2; k < count; k += width * 2) {
                real = co * data[k + width] - si * data[k + width + 1];
                imag = co * data[k + width + 1] + si * data[k + width];
                data[k + width] = data[k] - real;
                data[k + width + 1] = data[k + 1] - imag;
                data[k] = data[k] + real;
                data[k + 1] = data[k + 1] + imag;
            }
            m += n;
        }
        n >>= 1;
        groups <<= 1;
        width <<= 1;
    }
}

/* Decoder stage helpers. Their out-of-line copies are Audio_ReorderTransformSamples, Audio_RotateComplexSamples,
   Audio_TransformFft and Audio_QuantizeSampleS16 in the next unit (each with its own literal pool). */
static inline void interleaveMirrored(f32 *dst, f32 *src) {
    s16 i = 0;
    do {
        dst[i * 2] = src[i * 2];
        dst[i * 2 + 1] = src[255 - i * 2];
        i++;
    } while (i < 128);
}
static inline void rotatePairs(f32 *data, f32 *a, f32 *b) {
    s16 i = 0;
    do {
        f32 re = data[i * 2];
        f32 im = data[i * 2 + 1];
        f32 ca = a[i];
        f32 cb = b[i];
        data[i * 2] = re * ca - im * cb;
        data[i * 2 + 1] = re * cb + im * ca;
        i++;
    } while (i < 128);
}
static inline void transformFft(f32 *data, FftTables *tables, s32 sign) {
    Audio_ComplexFft(data, tables->size, sign, tables->sines, tables->cosines, tables->order);
}
static inline s16 roundToSample(f32 value) {
    f32 rounded;
    if (value >= 0.0f) {
        rounded = value + 0.5f;
        if (32767.0f < rounded) {
            rounded = 32767.0f;
        }
    } else {
        rounded = value - 0.5f;
        if (rounded < -32768.0f) {
            rounded = -32768.0f;
        }
    }
    return (s16)(s32)rounded;
}
/* Decode a 256-sample transform block: unpack it, pre-rotate, inverse FFT, post-rotate, then
   overlap it with the previous block's history (g_audioTransformZeros) and round/saturate to PCM. */
void Audio_DecodeTransformBlock(s16 *out, s16 *input) {
    f32 data[256];
    f32 unpacked[256];
    f32 scale;
    s16 i;
    s16 *initialized = &g_audioTransformTablesInitialized;
    if (*initialized == 0) {
        Audio_InitTransformTables();
        g_audioTransformFftTable = Audio_InitFftTables(128);
        *initialized = 1;
    }
    scale = 23170.474609375f; /* 32768 / sqrt(2) */
    Audio_DequantizeTransformCoefficients(unpacked, input + 12);
    interleaveMirrored(data, unpacked);
    rotatePairs(data, g_audioTransformSines, g_audioTransformCosines);
    transformFft(data, g_audioTransformFftTable, -1);
    rotatePairs(data, g_audioTransformSums, g_audioTransformDifferences);
    i = 0;
    do {
        f32 *history = g_audioTransformZeros;
        f32 *sines = g_audioTransformSines;
        f32 previous = history[i];
        f32 s = sines[i];
        f32 im = data[i * 2 | 1];
        f32 *cosines = g_audioTransformCosines;
        f32 c = cosines[i];
        f32 first = previous * s + im * c;
        f32 second = previous * c - im * s;
        history[i] = data[i * 2];
        out[i * 2] = roundToSample(scale * first);
        out[255 - i * 2] = roundToSample(scale * second);
        i++;
    } while (i < 128);
}
