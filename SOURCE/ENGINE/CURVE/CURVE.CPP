#include "TYPES.H"
#include "ENGINE/CURVE.H"

/* Two LSB-first bit streams, each a 32-bit window, its count of valid bits and the next byte to load:
 * g_curvePredictorBitWindow.. carries the 6-bit predictor codes, g_curveSampleBitWindow.. the 3-bit sample deltas. */
extern s32 g_curvePredictorBitCount;
extern u8 *g_curvePredictorByteCursor;
extern s32 g_curveSampleBitCount_de;
extern u8 *g_curveSampleByteCursor;

/* Q16 predictor coefficient pairs, indexed by the top 2 bits of a predictor code. */
extern s32 g_curvePredictorFirstCoefficients[4];
extern s32 g_curvePredictorSecondCoefficients[4];

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
            first = g_curvePredictorFirstCoefficients[word >> 4];
            second = g_curvePredictorSecondCoefficients[word >> 4];
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
s32 Curve_DecodePackedChannels(s32 destinations, void *encoded, s32 channel_count) {
    s32 *channels = (s32 *)destinations;
    u8 *packed = (u8 *)encoded;
    s32 sample_count;
    s32 control_bits;
    s32 shift;
    u8 *sample_bytes;
    u8 *cursor;
    s32 i;
    u32 last_byte;

    sample_count = *packed++ << 8;
    sample_count |= *packed++;
    control_bits = ((sample_count + 3) / 4) * 6;
    sample_bytes = packed + control_bits / 8;
    g_curveSampleBitWindow = sample_bytes[0];
    g_curveSampleBitWindow |= sample_bytes[1] << 8;
    g_curveSampleBitWindow |= sample_bytes[2] << 16;
    shift = control_bits & 7;
    last_byte = sample_bytes[3];
    last_byte <<= 24;
    g_curveSampleBitCount_de = 32 - shift;
    g_curveSampleByteCursor = sample_bytes + 4;
    g_curveSampleBitWindow = (g_curveSampleBitWindow | last_byte) >> shift;

    for (i = 0; i < channel_count; i++) {
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
        Curve_DecodeThreeBitSamples((s16 *)channels[i], sample_count);
    }
    return sample_count;
}


