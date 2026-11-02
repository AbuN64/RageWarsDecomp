#include "COMMON/LLDIVRESULT.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "TYPES.H"
#include "AUDIO/audio_initbitreverseorder.H"

s16 Audio_DecodeFrame();
u32 Audio_DecodeFrameOk(void) {
    return (u32) ~Audio_DecodeFrame() >> 31;
}

/* Fills the first N words of an index table with 0..N-1, then applies the bit-reversal
   permutation of an FFT of length N to it, swapping entries in place. */
void Audio_InitBitReverseOrder(s32 *permutation, s32 elementCount) {
    s32 *ptr;
    s32 i;
    s32 j;
    s32 k;
    s32 tmp;
    s32 n2;

    i = 0;
    n2 = elementCount * 2;
    if (elementCount > 0) {
        ptr = permutation;
        do {
            *ptr = i;
            i++;
            ptr++;
        } while (i < elementCount);
    }

    j = 1;
    i = 1;
    if (n2 > 0) {
        do {
            if (j > i) {
                tmp = permutation[(j - 1) / 2];
                permutation[(j - 1) / 2] = permutation[(i - 1) / 2];
                permutation[(i - 1) / 2] = tmp;
            }
            k = elementCount;
            while (k >= 2 && j > k) {
                j -= k;
                k >>= 1;
            }
            i += 2;
            j += k;
        } while (n2 >= i);
    }
}

/** Interleave the first and mirrored halves of 128 float pairs. */
void Audio_ReorderTransformSamples(float *output, float *input) {
    short i = 0;
    do {
        output[i * 2] = input[i * 2];
        output[i * 2 + 1] = input[(255 - i * 2)];
        i++;
    } while (i < 128);
}

/** Complex-multiply 128 (re,im) pairs in-place by per-element (a,b) factors. */
void Audio_RotateComplexSamples(float *samples, float *rotationReal, float *rotationImaginary) {
    short i = 0;
    do {
        float re = samples[i * 2];
        float im = samples[i * 2 + 1];
        float a = rotationReal[i];
        float b = rotationImaginary[i];

        samples[i * 2] = re * a - im * b;
        samples[i * 2 + 1] = re * b + im * a;
        i++;
    } while (i < 128);
}


void Audio_TransformFft(f32 *data, FftTables *tables, s32 sign) {
    Audio_ComplexFft(data, tables->size, sign, tables->sines, tables->cosines, tables->order);
}

s16 Audio_QuantizeSampleS16(f32 sample) {
    f32 f0;
    f32 f12;

    if (sample >= 0.0f) {
        f12 = sample + g_audioSamplePositiveRoundingBias;
        f0 = g_audioSampleMaximum;
        if (f0 < f12) {
            f12 = f0;
        }
    } else {
        f12 = sample - g_audioSampleNegativeRoundingBias;
        f0 = g_audioSampleMinimum;
        if (f12 < f0) {
            f12 = f0;
        }
    }
    return (s16)(s32)f12;
}

/** Initialize the global decoder state and return its scaled period. */
u32 Audio_InitDecodeStream(s32 *source, u32 divisor, s32 *first)
{
    DecodeState *state = &g_audioSampleDecodeState;
    state->source = source;
    state->cursor = source;
    state->first = *(s32 *)state->cursor;
    state->cursor = (s32 *)state->cursor + 1;
    state->count = *(s32 *)state->cursor;
    state->second = *(s32 *)state->cursor;
    state->cursor = (s32 *)state->cursor + 1;
    state->third = *(s32 *)state->cursor;
    state->cursor = (s32 *)state->cursor + 1;
    g_audioDecodeFrameHeaderRead = 0;
    g_audioTransformTablesInitialized = 0;
    gPackedBitsLeft = 0;
    g_audioDecodeBitBuffer = 0;
    g_audioDecodeBitsLeft = 0;
    *first = state->first;
    return (u64)((s64)state->count * 0xF424000) / divisor;
}
