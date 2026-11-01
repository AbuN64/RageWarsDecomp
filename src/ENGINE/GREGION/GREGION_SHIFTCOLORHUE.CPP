#include "include_asm.h"
#include "LISTS/EXTERNS.H"
#include "TYPES.H"
#include "COMMON/MATH_HELPERS.H"
#include "COMMON/MODEL_TREE_REGION_OPERATIONS.H"
#include "COMMON/TRIPLE.H"

const float g_regionHueFirstWeightScale_StorageWords[3] = {
    0.011764706f, 0.011764706f, 0.011764706f,
};

void Gregion_ShiftColorHue(u8 hue, u8 red_arg, u8 green_arg, u8 blue_arg,
    void *red_out, void *green_out, void *blue_out) {
    s32 phase;
    s32 distance0, distance1, distance2;
    s32 phase2;
    s32 w0, w1, w2;
    s32 red, green, blue;
    s32 p0, p1, p2, p3, p4, p5, p6, p7, p8;
    s32 mixed_red, mixed_green, mixed_blue, largest;
    f32 original_max, mixed_max;

    phase = (s8)hue;
    if (phase != 0) {
        if (phase < 0) {
            distance0 = phase + 85;
            if (distance0 >= 0) w0 = (s32)((f32)(distance0 * 100) * g_regionHueFirstWeightScale);
            else w0 = 0;
        } else {
            distance0 = 85 - phase;
            if (distance0 >= 0) w0 = (s32)((f32)(distance0 * 100) * g_regionHueFirstWeightScale);
            else w0 = 0;
        }
        distance1 = (s8)hue;
        if (distance1 < -85) {
            distance1 += 170;
            w1 = (s32)((f32)(distance1 * 100) * g_regionHueSecondWeightScale);
        } else {
            distance1 = -distance1;
            if (distance1 >= 0) w1 = (s32)((f32)(distance1 * 100) * g_regionHueSecondWeightScale);
            else w1 = 0;
        }
        phase2 = (s8)hue;
        if (phase2 > 85) {
            distance2 = 170 - phase2;
            w2 = (s32)((f32)(distance2 * 100) * g_regionHueThirdWeightScale);
        } else {
            if (phase2 >= 0) w2 = (s32)((f32)(phase2 * 100) * g_regionHueThirdWeightScale);
            else w2 = 0;
        }

        blue = (u8)blue_arg;
        red = (u8)red_arg;
        green = (u8)green_arg;
        p0 = w1 * blue;
        p1 = w0 * red;
        p2 = w2 * green;
        p3 = w1 * red;
        p4 = w0 * green;
        p5 = w2 * blue;
        p6 = w1 * green;
        p7 = w0 * blue;
        p8 = w2 * red;
        mixed_red = p0 + p1 + p2;
        mixed_green = p3 + p4 + p5;
        mixed_blue = p6 + p7 + p8;
        original_max = RW_MAX_GT((u8)red_arg,
            RW_MAX_GT((u8)green_arg, (u8)blue_arg));
        largest = mixed_blue;
        if (largest < mixed_green) largest = mixed_green;
        if (largest < mixed_red) largest = mixed_red;
        mixed_max = (f32)largest;
        if (mixed_max != 0.0f) {
            *(u8 *)red_out = (u32)((f32)mixed_red * original_max / mixed_max);
            *(u8 *)green_out = (u32)((f32)mixed_green * original_max / mixed_max);
            *(u8 *)blue_out = (u32)((f32)mixed_blue * original_max / mixed_max);
        } else {
            *(u8 *)red_out = red_arg;
            *(u8 *)green_out = green_arg;
            *(u8 *)blue_out = blue_arg;
        }
    } else {
        *(u8 *)red_out = red_arg;
        *(u8 *)green_out = green_arg;
        *(u8 *)blue_out = blue_arg;
    }
}

/* Blends a colour toward the grey of its brightest channel: with amount (0-100) zero it copies r, g, b to the outputs, otherwise each output is (channel * (100 - amount) + max(r, g, b) * amount) / 100. */
void Gregion_DesaturateColor(u8 amount, u8 r, u8 g, u8 b, u8 *outR, u8 *outG, u8 *outB) {
    s32 rest;
    s32 top;
    if (amount != 0) {
        rest = 100 - amount;
        top = RW_MAX_GT(r, RW_MAX_GT(g, b));
        *outR = (r * rest + top * amount) * 0.01f;
        *outG = (g * rest + top * amount) * 0.01f;
        *outB = (b * rest + top * amount) * 0.01f;
    } else {
        *outR = r;
        *outG = g;
        *outB = b;
    }
}

/* Darkens a colour by a percentage: with a non-zero percentage each channel becomes the channel scaled by one hundredth of (100 minus the percentage), and with zero the channels are copied unchanged. */
void Gregion_DarkenColor(unsigned char percent, unsigned char r, unsigned char g, unsigned char b,
                   unsigned char *outR, unsigned char *outG, unsigned char *outB) {
    int remaining;
    if (percent != 0) {
        remaining = 100 - percent;
        *outR = (unsigned int)(r * 0.01f * remaining);
        *outG = (unsigned int)(g * 0.01f * remaining);
        *outB = (unsigned int)(b * 0.01f * remaining);
    } else {
        *outR = r;
        *outG = g;
        *outB = b;
    }
}




