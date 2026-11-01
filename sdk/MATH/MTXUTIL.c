#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/ALDELAY28.H"
#include "COMMON/GUMTXL2F.H"
#include "DATA/REST_SOURCE_RECORDS.H"
#include "COMMON/ALFXPARAM.H"

/* mtxutil.CPP */
void guMtxIdent(Mtx *m) {
    s32 *fixedMatrix = (s32 *)m;
    f32 matrix[16];
    u8 *diagBase;
    u8 *diag;
    u8 *elem;
    u8 *row;
    s32 r;
    s32 c;
    f32 one;
    s32 *outLo;
    s32 *outHi;
    f32 *inRow;
    f32 *inPair;
    f32 mult;
    u32 mask;
    f32 t1;
    f32 t0;
    s32 v0;
    s32 v1;
    s32 i;
    s32 j;

    r = 0;
    one = g_matrixIdentityUnitValue;
    diagBase = (u8 *)matrix;
    row = (u8 *)matrix;
    do {
        c = 0;
        diag = diagBase;
        elem = row;
        do {
            if (r == c) {
                *(f32 *)diag = one;
            } else {
                *(s32 *)elem = 0;
            }
            c++;
            elem += 4;
        } while (c < 4);
        diagBase += 0x14;
        r++;
        row += 0x10;
    } while (r < 4);

    outLo = fixedMatrix;
    outHi = fixedMatrix + 8;
    i = 0;
    mult = g_matrixFloatToFixedScale;
    mask = 0xFFFF0000;
    inRow = matrix;
    do {
        j = 0;
        inPair = inRow;
        do {
            t1 = inPair[0] * mult;
            t0 = inPair[1] * mult;
            inPair += 2;
            j++;
            v0 = (s32)t1;
            v1 = (s32)t0;
            *outLo = (v0 & mask) | ((u32)v1 >> 16);
            outLo++;
            *outHi = ((v0 << 16) & mask) | (v1 & 0xFFFF);
            outHi++;
        } while (j < 2);
        i++;
        inRow += 4;
    } while (i < 4);
}

void guMtxIdentF(float mf[4][4]) {
    u8 *matrixBytes = (u8 *)mf;
    u8 *diag;
    u8 *elem;
    s32 r;
    s32 c;
    f32 one;

    r = 0;
    one = g_matrixFloatIdentityUnitValue;
    diag = matrixBytes;
    do {
        c = 0;
        elem = matrixBytes;
        do {
            if (r == c) {
                *(f32 *)diag = one;
            } else {
                *(s32 *)elem = 0;
            }
            c += 1;
            elem += 4;
        } while (c < 4);
        diag += 0x14;
        r += 1;
        matrixBytes += 0x10;
    } while (r < 4);
}

void guMtxF2L(float mf[4][4], Mtx *m) {
    f32 *floatMatrix = (f32 *)mf;
    s32 *fixedMatrix = (s32 *)m;
    s32 *outLo;
    s32 *outHi;
    f32 *inRow;
    f32 *inPair;
    f32 mult;
    u32 mask;
    f32 t1;
    f32 t0;
    s32 v0;
    s32 v1;
    s32 i;
    s32 j;

    outLo = fixedMatrix;
    outHi = fixedMatrix + 8;
    i = 0;
    mult = g_matrixFixedToFloatScale;
    mask = 0xFFFF0000;
    inRow = floatMatrix;
    do {
        j = 0;
        inPair = inRow;
        do {
            t1 = inPair[0] * mult;
            t0 = inPair[1] * mult;
            inPair += 2;
            j += 1;
            v0 = (s32) t1;
            v1 = (s32) t0;
            *outLo = (v0 & mask) | ((u32) v1 >> 16);
            outLo += 1;
            *outHi = ((v0 << 16) & mask) | (v1 & 0xFFFF);
            outHi += 1;
        } while (j < 2);
        i += 1;
        inRow += 4;
    } while (i < 4);
}

void guMtxL2F(float mf[4][4], Mtx *m) {
    f32 *floatMatrix = (f32 *)mf;
    s32 *fixedMatrix = (s32 *)m;
    s32 *inLo;
    u32 *inHi;
    f32 *outRow;
    f32 *outPair;
    f32 mult;
    u32 mask;
    s32 raw0;
    u32 raw1;
    s32 v0;
    s32 v1;
    s32 i;
    s32 j;

    inLo = fixedMatrix;
    inHi = (u32 *) (fixedMatrix + 8);
    i = 0;
    mask = 0xFFFF0000;
    mult = g_matrixLongToFloatScale;
    outRow = floatMatrix;
    do {
        j = 0;
        outPair = outRow;
        do {
            raw0 = *inLo;
            raw1 = *inHi;
            inHi += 1;
            v0 = (raw0 & mask) | (raw1 >> 16);
            v1 = ((raw0 << 16) & mask) | (raw1 & 0xFFFF);
            inLo += 1;
            j += 1;
            outPair[0] = (f32) v0 * mult;
            outPair[1] = (f32) v1 * mult;
            outPair += 2;
        } while (j < 2);
        i += 1;
        outRow += 4;
    } while (i < 4);
}

/* LOOKAT.CPP */
const float k_lookatFloatConstantWords[7] = {
    -1.0f, 1.0f, 1.0f, 65536.0f, 1.0f, 65536.0f,
    1.5258789e-05f,
};

#if defined(VERSION_DE)
float k_LookatEncodedWordsBlock1[3] = {
    0.5f, -1.0f, 2.0f,
};
#endif
