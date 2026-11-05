#include "include_asm.h"
#include "Common/material_tree.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "types.h"
#include "Engine/graphics_math.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Common/approachlocation.h"
#include "Common/graphics_matrix_and_vector_math.h"
#include "Common/math_helpers.h"
#include "Common/ballisticparams.h"
#include "Common/triple.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Common/pooled_floats.h"
#include "Common/mtx.h"
#include "Game/builddirectionmatrix.h"
#include "Fx/normalize_vector.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/packed.h"
#include "Common/aiprofile.h"
#include "Common/objb.h"
#include <platform_sdk.h>
#include "Graphu64/graphu64_buildlookatmatrix.h"
#include "Data/rest_source_records.h"
#include "Data/Enemy/g_pickuptrailingrodataeux.h"
#include "Common/format.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"
#include "System/engine_data_source.h"

#include "Engine/gregion.h"

/* GRAPHU64_PACKFIXEDMATRIX.CPP */

/* Transforms an axis-aligned box by a matrix: starts the new minimum and maximum at the matrix translation and, for every matrix entry, adds the smaller of its products with the old minimum and maximum to the new minimum and the larger to the new maximum. */

void Graphu64_TransformBoundingBox(f32 m[4][4], ModelBoundingBox *box, ModelBoundingBox *out) {
    f32 min[3];
    f32 max[3];
    f32 newMin[3];
    f32 newMax[3];
    f32 a;
    f32 b;
    s32 i;
    s32 j;

    min[0] = box->min[0];
    min[1] = box->min[1];
    min[2] = box->min[2];
    max[0] = box->max[0];
    max[1] = box->max[1];
    max[2] = box->max[2];
    newMin[0] = newMax[0] = m[3][0];
    newMin[1] = newMax[1] = m[3][1];
    newMin[2] = newMax[2] = m[3][2];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            a = m[j][i] * min[j];
            b = m[j][i] * max[j];
            if (a < b) {
                newMin[i] += a;
                newMax[i] += b;
            } else {
                newMin[i] += b;
                newMax[i] += a;
            }
        }
    }
    out->min[0] = newMin[0];
    out->min[1] = newMin[1];
    out->min[2] = newMin[2];
    out->max[0] = newMax[0];
    out->max[1] = newMax[1];
    out->max[2] = newMax[2];
}

/**
 * Invert a row-major affine 4x4 transform, copying singular inputs unchanged.
 *
 * @name CMtxF__Invert
 * @param out Destination for the 16-float inverse; it must not overlap `m`.
 * @param m Source matrix stored as four contiguous rows. Its last column is
 *          (0, 0, 0, 1), its final row holds translation, and it transforms
 *          row vectors.
 *
 * Computes the determinant and adjugate of the upper-left 3x3 linear block,
 * scales them by the reciprocal determinant, then derives the inverse
 * translation as -translation * inverse_linear. If the determinant is exactly
 * zero, all 16 source elements are copied to `out` instead.
 *
 * Game role: Callers invert model or camera transforms so positions can be
 * moved from world space into object-local or view space for spatial and
 * rendering calculations.
 */
void Graphu64_InvertAffineMatrix(f32 *out, f32 *m) {
    f32 determinant;
    f32 reciprocalDeterminant;
    f32 m01TimesM22;
    f32 m00TimesM12;
    f32 inverseTranslationZNumeratorPartial;
    f32 affineHomogeneousOne;

    determinant = m[0] * m[5] * m[10]
                - m[0] * m[9] * m[6]
                - m[4] * m[1] * m[10]
                + m[4] * m[9] * m[2]
                + m[8] * m[1] * m[6]
                - m[8] * m[5] * m[2];

    if (determinant == 0.0f) {
        out[0] = m[0];
        out[1] = m[1];
        out[2] = m[2];
        out[3] = m[3];
        out[4] = m[4];
        out[5] = m[5];
        out[6] = m[6];
        out[7] = m[7];
        out[8] = m[8];
        out[9] = m[9];
        out[10] = m[10];
        out[11] = m[11];
        out[12] = m[12];
        out[13] = m[13];
        out[14] = m[14];
        out[15] = m[15];
        return;
    }

    affineHomogeneousOne = g_directionMatrixUnitConstants_de[0].x;
    reciprocalDeterminant = affineHomogeneousOne / determinant;
    out[0] = (m[5] * m[10] - m[9] * m[6]) * reciprocalDeterminant;
    m01TimesM22 = m[1] * m[10];
    out[1] = (m[9] * m[2] - m01TimesM22) * reciprocalDeterminant;
    out[2] = (m[1] * m[6] - m[5] * m[2]) * reciprocalDeterminant;
    out[3] = 0.0f;
    out[4] = (-m[4] * m[10] + m[8] * m[6]) * reciprocalDeterminant;
    out[5] = (m[0] * m[10] - m[8] * m[2]) * reciprocalDeterminant;
    m00TimesM12 = m[0] * m[6];
    out[6] = (m[4] * m[2] - m00TimesM12) * reciprocalDeterminant;
    out[7] = 0.0f;
    out[8] = -(-m[4] * m[9] + m[8] * m[5]) * reciprocalDeterminant;
    out[9] = (-m[0] * m[9] + m[8] * m[1]) * reciprocalDeterminant;
    out[10] = -(-m[0] * m[5] + m[4] * m[1]) * reciprocalDeterminant;
    out[11] = 0.0f;
    out[12] = (-m[4] * m[9] * m[14]
             + m[4] * m[10] * m[13]
             + m[8] * m[5] * m[14]
             - m[8] * m[6] * m[13]
             - m[12] * m[5] * m[10]
             + m[12] * m[9] * m[6]) * reciprocalDeterminant;
    out[13] = (m[0] * m[9] * m[14]
             - m[0] * m[10] * m[13]
             - m[8] * m[1] * m[14]
             + m[8] * m[2] * m[13]
             + m[12] * m[1] * m[10]
             - m[12] * m[9] * m[2]) * reciprocalDeterminant;
    inverseTranslationZNumeratorPartial = m[0] * m[5] * m[14]
                                        - m[0] * m[6] * m[13]
                                        - m[4] * m[1] * m[14]
                                        + m[4] * m[2] * m[13]
                                        + m[12] * m[1] * m[6];
    out[14] = (m[12] * m[5] * m[2] - inverseTranslationZNumeratorPartial) * reciprocalDeterminant;
    out[15] = affineHomogeneousOne;
}

/* Builds a look-at view matrix from an eye position, a target and an up vector: the forward axis is the normalised direction from the target back to the eye, the right axis the normalised cross product of up and forward, the true up axis their normalised cross product, each written as a matrix column with the negated eye projections as the translation row, falling back to the x axis when forward or right degenerate. */

void Graphu64_ComputeViewMatrix(MatrixF *mtx, CVector3 *eye, CVector3 *target, CVector3 *up) {
    CVector3 upward;
    CVector3 forward;
    CVector3 right;
    f32 length;

    Graphu64_SubtractVectors(&forward, target, eye);
    length = Gu_Sqrtf(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);
    if (0.001f < length) {
        length = -1.0f / length;
        forward.x *= length;
        forward.y *= length;
        forward.z *= length;
    } else {
        forward.x = 1.0f;
        forward.y = 0.0f;
        forward.z = 0.0f;
    }

    Graphu64_CrossVectors(&right, up, &forward);
    length = Gu_Sqrtf(right.x * right.x + right.y * right.y + right.z * right.z);
    if (0.001f < length) {
        length = 1.0f / length;
        right.x *= length;
        right.y *= length;
        right.z *= length;
    } else {
        right.x = 1.0f;
        right.y = 0.0f;
        right.z = 0.0f;
    }

    Graphu64_CrossVectors(&upward, &forward, &right);
    length = 1.0f / Gu_Sqrtf(upward.x * upward.x + upward.y * upward.y + upward.z * upward.z);
    upward.x *= length;
    upward.y *= length;
    upward.z *= length;

    mtx->m[0][0] = right.x;
    mtx->m[1][0] = right.y;
    mtx->m[2][0] = right.z;
    mtx->m[3][0] = -(eye->x * right.x + eye->y * right.y + eye->z * right.z);
    mtx->m[0][1] = upward.x;
    mtx->m[1][1] = upward.y;
    mtx->m[2][1] = upward.z;
    mtx->m[3][1] = -(eye->x * upward.x + eye->y * upward.y + eye->z * upward.z);
    mtx->m[0][2] = forward.x;
    mtx->m[1][2] = forward.y;
    mtx->m[2][2] = forward.z;
    mtx->m[3][2] = -(eye->x * forward.x + eye->y * forward.y + eye->z * forward.z);
    mtx->m[0][3] = 0.0f;
    mtx->m[1][3] = 0.0f;
    mtx->m[2][3] = 0.0f;
    mtx->m[3][3] = 1.0f;
}

/** Multiply two affine 4x4 matrices into the output matrix. */
void Graphu64_MultiplyAffineMatrices(f32 *out, f32 *left, f32 *right)
{
    out[(0) * 4 + (0)] = (left[(0) * 4] * right[(0)]) + (left[(0) * 4 + 1] * right[4 + (0)]) + (left[(0) * 4 + 2] * right[8 + (0)]);
    out[(0) * 4 + (1)] = (left[(0) * 4] * right[(1)]) + (left[(0) * 4 + 1] * right[4 + (1)]) + (left[(0) * 4 + 2] * right[8 + (1)]);
    out[(0) * 4 + (2)] = (left[(0) * 4] * right[(2)]) + (left[(0) * 4 + 1] * right[4 + (2)]) + (left[(0) * 4 + 2] * right[8 + (2)]);
    out[(1) * 4 + (0)] = (left[(1) * 4] * right[(0)]) + (left[(1) * 4 + 1] * right[4 + (0)]) + (left[(1) * 4 + 2] * right[8 + (0)]);
    out[(1) * 4 + (1)] = (left[(1) * 4] * right[(1)]) + (left[(1) * 4 + 1] * right[4 + (1)]) + (left[(1) * 4 + 2] * right[8 + (1)]);
    out[(1) * 4 + (2)] = (left[(1) * 4] * right[(2)]) + (left[(1) * 4 + 1] * right[4 + (2)]) + (left[(1) * 4 + 2] * right[8 + (2)]);
    out[(2) * 4 + (0)] = (left[(2) * 4] * right[(0)]) + (left[(2) * 4 + 1] * right[4 + (0)]) + (left[(2) * 4 + 2] * right[8 + (0)]);
    out[(2) * 4 + (1)] = (left[(2) * 4] * right[(1)]) + (left[(2) * 4 + 1] * right[4 + (1)]) + (left[(2) * 4 + 2] * right[8 + (1)]);
    out[(2) * 4 + (2)] = (left[(2) * 4] * right[(2)]) + (left[(2) * 4 + 1] * right[4 + (2)]) + (left[(2) * 4 + 2] * right[8 + (2)]);
    out[12] = (left[12] * right[0]) + (left[13] * right[4]) +
              (left[14] * right[8]) + right[12];
    out[13] = (left[12] * right[1]) + (left[13] * right[5]) +
              (left[14] * right[9]) + right[13];
    out[14] = (left[12] * right[2]) + (left[13] * right[6]) +
              (left[14] * right[10]) + right[14];
    out[3] = out[7] = out[11] = 0.0f;
    out[15] = g_matrixUnpackHomogeneousScale;
}
/** Multiply two column-addressed 4x4 matrices into the output matrix. */
void Graphu64_MultiplyMatrices(f32 *out, f32 *left, f32 *right)
{
    out[(0) * 4 + (0)] = (left[(0) * 4] * right[(0)]) + (left[(0) * 4 + 1] * right[4 + (0)]) + (left[(0) * 4 + 2] * right[8 + (0)]) + (left[(0) * 4 + 3] * right[12 + (0)]);
    out[(0) * 4 + (1)] = (left[(0) * 4] * right[(1)]) + (left[(0) * 4 + 1] * right[4 + (1)]) + (left[(0) * 4 + 2] * right[8 + (1)]) + (left[(0) * 4 + 3] * right[12 + (1)]);
    out[(0) * 4 + (2)] = (left[(0) * 4] * right[(2)]) + (left[(0) * 4 + 1] * right[4 + (2)]) + (left[(0) * 4 + 2] * right[8 + (2)]) + (left[(0) * 4 + 3] * right[12 + (2)]);
    out[(0) * 4 + (3)] = (left[(0) * 4] * right[(3)]) + (left[(0) * 4 + 1] * right[4 + (3)]) + (left[(0) * 4 + 2] * right[8 + (3)]) + (left[(0) * 4 + 3] * right[12 + (3)]);
    out[(1) * 4 + (0)] = (left[(1) * 4] * right[(0)]) + (left[(1) * 4 + 1] * right[4 + (0)]) + (left[(1) * 4 + 2] * right[8 + (0)]) + (left[(1) * 4 + 3] * right[12 + (0)]);
    out[(1) * 4 + (1)] = (left[(1) * 4] * right[(1)]) + (left[(1) * 4 + 1] * right[4 + (1)]) + (left[(1) * 4 + 2] * right[8 + (1)]) + (left[(1) * 4 + 3] * right[12 + (1)]);
    out[(1) * 4 + (2)] = (left[(1) * 4] * right[(2)]) + (left[(1) * 4 + 1] * right[4 + (2)]) + (left[(1) * 4 + 2] * right[8 + (2)]) + (left[(1) * 4 + 3] * right[12 + (2)]);
    out[(1) * 4 + (3)] = (left[(1) * 4] * right[(3)]) + (left[(1) * 4 + 1] * right[4 + (3)]) + (left[(1) * 4 + 2] * right[8 + (3)]) + (left[(1) * 4 + 3] * right[12 + (3)]);
    out[(2) * 4 + (0)] = (left[(2) * 4] * right[(0)]) + (left[(2) * 4 + 1] * right[4 + (0)]) + (left[(2) * 4 + 2] * right[8 + (0)]) + (left[(2) * 4 + 3] * right[12 + (0)]);
    out[(2) * 4 + (1)] = (left[(2) * 4] * right[(1)]) + (left[(2) * 4 + 1] * right[4 + (1)]) + (left[(2) * 4 + 2] * right[8 + (1)]) + (left[(2) * 4 + 3] * right[12 + (1)]);
    out[(2) * 4 + (2)] = (left[(2) * 4] * right[(2)]) + (left[(2) * 4 + 1] * right[4 + (2)]) + (left[(2) * 4 + 2] * right[8 + (2)]) + (left[(2) * 4 + 3] * right[12 + (2)]);
    out[(2) * 4 + (3)] = (left[(2) * 4] * right[(3)]) + (left[(2) * 4 + 1] * right[4 + (3)]) + (left[(2) * 4 + 2] * right[8 + (3)]) + (left[(2) * 4 + 3] * right[12 + (3)]);
    out[(3) * 4 + (0)] = (left[(3) * 4] * right[(0)]) + (left[(3) * 4 + 1] * right[4 + (0)]) + (left[(3) * 4 + 2] * right[8 + (0)]) + (left[(3) * 4 + 3] * right[12 + (0)]);
    out[(3) * 4 + (1)] = (left[(3) * 4] * right[(1)]) + (left[(3) * 4 + 1] * right[4 + (1)]) + (left[(3) * 4 + 2] * right[8 + (1)]) + (left[(3) * 4 + 3] * right[12 + (1)]);
    out[(3) * 4 + (2)] = (left[(3) * 4] * right[(2)]) + (left[(3) * 4 + 1] * right[4 + (2)]) + (left[(3) * 4 + 2] * right[8 + (2)]) + (left[(3) * 4 + 3] * right[12 + (2)]);
    out[(3) * 4 + (3)] = (left[(3) * 4] * right[(3)]) + (left[(3) * 4 + 1] * right[4 + (3)]) + (left[(3) * 4 + 2] * right[8 + (3)]) + (left[(3) * 4 + 3] * right[12 + (3)]);
}

/* Converts a float matrix element to its 16.16 fixed-point word; values past the threshold constant wrap into the sign bit. */
static s32 Graphu64_FloatToFixed(f32 element, const f32 *constants) {
    f32 scaled = element * constants[0];
    if (constants[1] <= scaled) {
        return (s32)(scaled - constants[1]) | SIGN_BIT_32;
    }
    return (s32)scaled;
}

void GraphU64_PackFixedMatrix(f32 *src, FixedPointMatrix *dst) {
    u32 *upper = dst->upper;
    u32 *lower = dst->lower;
    s32 firstWord;
    s32 secondWord;
    firstWord = Graphu64_FloatToFixed(src[(0) * 2], g_fullMatrixFixedConversionPairs[0]);
    secondWord = Graphu64_FloatToFixed(src[(0) * 2 + 1], g_fullMatrixFixedConversionPairs[1]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;
    firstWord = Graphu64_FloatToFixed(src[(1) * 2], g_fullMatrixFixedConversionPairs[2]);
    secondWord = Graphu64_FloatToFixed(src[(1) * 2 + 1], g_fullMatrixFixedConversionPairs[3]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;
    firstWord = Graphu64_FloatToFixed(src[(2) * 2], g_fullMatrixFixedConversionPairs[4]);
    secondWord = Graphu64_FloatToFixed(src[(2) * 2 + 1], g_fullMatrixFixedConversionPairs[5]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;
    firstWord = Graphu64_FloatToFixed(src[(3) * 2], g_fullMatrixFixedConversionPairs[6]);
    secondWord = Graphu64_FloatToFixed(src[(3) * 2 + 1], g_fullMatrixFixedConversionPairs[7]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;
    firstWord = Graphu64_FloatToFixed(src[(4) * 2], g_fullMatrixFixedConversionPairs[8]);
    secondWord = Graphu64_FloatToFixed(src[(4) * 2 + 1], g_fullMatrixFixedConversionPairs[9]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;
    firstWord = Graphu64_FloatToFixed(src[(5) * 2], g_fullMatrixFixedConversionPairs[10]);
    secondWord = Graphu64_FloatToFixed(src[(5) * 2 + 1], g_fullMatrixFixedConversionPairs[11]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;
    firstWord = Graphu64_FloatToFixed(src[(6) * 2], g_fullMatrixFixedConversionPairs[12]);
    secondWord = Graphu64_FloatToFixed(src[(6) * 2 + 1], g_fullMatrixFixedConversionPairs[13]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;
    firstWord = Graphu64_FloatToFixed(src[(7) * 2], g_fullMatrixFixedConversionPairs[14]);
    secondWord = Graphu64_FloatToFixed(src[(7) * 2 + 1], g_fullMatrixFixedConversionPairs[15]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;
}

void Graphu64_ConvertMatrixToFixed(f32 *src, FixedPointMatrix *dst) {
    u32 *upper = dst->upper;
    u32 *lower = dst->lower;
    s32 firstWord;
    s32 secondWord;
    firstWord = Graphu64_FloatToFixed(src[0], g_affineMatrixFixedConversionPairs[0]);
    secondWord = Graphu64_FloatToFixed(src[1], g_affineMatrixFixedConversionPairs[1]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;

    firstWord = Graphu64_FloatToFixed(src[2], g_affineMatrixFixedConversionPairs[2]);
    *upper = firstWord & 0xFFFF0000;
    *lower = firstWord << 16;
    upper++;
    lower++;

    firstWord = Graphu64_FloatToFixed(src[4], g_affineMatrixFixedConversionPairs[3]);
    secondWord = Graphu64_FloatToFixed(src[5], g_affineMatrixFixedConversionPairs[4]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;

    firstWord = Graphu64_FloatToFixed(src[6], g_affineMatrixFixedConversionPairs[5]);
    *upper = firstWord & 0xFFFF0000;
    *lower = firstWord << 16;
    upper++;
    lower++;

    firstWord = Graphu64_FloatToFixed(src[8], g_affineMatrixFixedConversionPairs[6]);
    secondWord = Graphu64_FloatToFixed(src[9], g_affineMatrixFixedConversionPairs[7]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;

    firstWord = Graphu64_FloatToFixed(src[10], g_affineMatrixFixedConversionPairs[8]);
    *upper = firstWord & 0xFFFF0000;
    *lower = firstWord << 16;
    upper++;
    lower++;

    firstWord = Graphu64_FloatToFixed(src[12], g_affineMatrixFixedConversionPairs[9]);
    secondWord = Graphu64_FloatToFixed(src[13], g_affineMatrixFixedConversionPairs[10]);
    *upper = (firstWord & 0xFFFF0000) | ((u32)secondWord >> 16);
    *lower = (firstWord << 16) | (secondWord & 0xFFFF);
    upper++;
    lower++;

    firstWord = Graphu64_FloatToFixed(src[14], g_affineMatrixFixedConversionPairs[11]);
    *upper = (firstWord & 0xFFFF0000) | 1;
    *lower = firstWord << 16;
}

void Graphu64_UnpackFixedMatrix(f32 *dst, FixedPointMatrix *src) {
    u32 upper;
    u32 lower;
    f32 scale = g_quaternionMatrixUnitScale;

    upper = src->upper[0];
    lower = src->lower[0];
    dst[(0) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(0) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    upper = src->upper[1];
    lower = src->lower[1];
    dst[(1) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(1) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    upper = src->upper[2];
    lower = src->lower[2];
    dst[(2) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(2) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    upper = src->upper[3];
    lower = src->lower[3];
    dst[(3) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(3) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    upper = src->upper[4];
    lower = src->lower[4];
    dst[(4) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(4) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    upper = src->upper[5];
    lower = src->lower[5];
    dst[(5) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(5) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    upper = src->upper[6];
    lower = src->lower[6];
    dst[(6) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(6) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    upper = src->upper[7];
    lower = src->lower[7];
    dst[(7) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(7) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
}

/* Unpacks a fixed-point 4x4 matrix held as separate integer and fraction halves into floats scaled by g_quaternionInterpolationUnitScale, zeroing the fourth column and setting the last element to g_matrixAndSlerpUnitConstants. */

void Graphu64_ConvertMatrixToFloat(f32 *dst, FixedPointMatrix *src) {
    u32 upper;
    u32 lower;
    f32 scale = g_quaternionInterpolationUnitScale;
    upper = src->upper[0];
    lower = src->lower[0];
    dst[(0) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(0) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    upper = src->upper[1];
    lower = src->lower[1];
    dst[(1) * 2] = (f32)(s32)(upper | (lower >> 16)) * scale;
    dst[(1) * 2 + 1] = 0.0f;
    upper = src->upper[2];
    lower = src->lower[2];
    dst[(2) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(2) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    upper = src->upper[3];
    lower = src->lower[3];
    dst[(3) * 2] = (f32)(s32)(upper | (lower >> 16)) * scale;
    dst[(3) * 2 + 1] = 0.0f;
    upper = src->upper[4];
    lower = src->lower[4];
    dst[(4) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(4) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    upper = src->upper[5];
    lower = src->lower[5];
    dst[(5) * 2] = (f32)(s32)(upper | (lower >> 16)) * scale;
    dst[(5) * 2 + 1] = 0.0f;
    upper = src->upper[6];
    lower = src->lower[6];
    dst[(6) * 2] = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
    dst[(6) * 2 + 1] = (f32)(s32)((upper << 16) | (lower & 0xFFFF)) * scale;
    {
        f32 last;
        upper = src->upper[7];
        lower = src->lower[7];
        last = (f32)(s32)((upper & 0xFFFF0000) | (lower >> 16)) * scale;
        dst[15] = g_matrixAndSlerpUnitConstants;
        dst[14] = last;
    }
}

void Graphu64_InterpolateQuaternionArc(CQuatern *out, f32 amount, CQuatern *a, CQuatern *b) {
    CQuatern negative;
    CQuatern *other;
    f32 dot;
    f32 negativeDot;
    f32 angle;
    f32 sine;
    f32 inverseSine;
    f32 scaleA;
    f32 scaleB;

    other = b;
    negative = *b;
    negative.x = -negative.x;
    negative.y = -negative.y;
    negative.z = -negative.z;
    negative.w = -negative.w;

    dot = (a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w);
    negativeDot = (a->x * negative.x) + (a->y * negative.y) +
                  (a->z * negative.z) + (a->w * negative.w);
    if (dot < negativeDot) {
        dot = negativeDot;
        other = &negative;
    }

    angle = Graphu64_ArcCos(dot);
    sine = Gu_Sinf(angle);
    if (sine == 0.0f) {
        *out = *a;
        return;
    }

    inverseSine = *(&g_matrixAndSlerpUnitConstants + 1) / sine;
    scaleA = Gu_Sinf((*(&g_matrixAndSlerpUnitConstants + 1) - amount) * angle) * inverseSine;
    scaleB = Gu_Sinf(amount * angle) * inverseSine;
    if (dot < negativeDot) {
        other = &negative;
    }

    out->x = (scaleA * a->x) + (scaleB * other->x);
    out->y = (scaleA * a->y) + (scaleB * other->y);
    out->z = (scaleA * a->z) + (scaleB * other->z);
    out->w = (scaleA * a->w) + (scaleB * other->w);
}

void Graphu64_InterpolateQuaternionWithLinearFallback(CQuatern *out, f32 amount, CQuatern *a, CQuatern *b) {
    CQuatern negative;
    CQuatern *other;
    f32 dot;
    f32 negativeDot;
    f32 angle;
    f32 sine;
    f32 inverseSine;
    f32 scaleA;
    f32 scaleB;

    other = b;
    negative = *b;
    negative.x = -negative.x;
    negative.y = -negative.y;
    negative.z = -negative.z;
    negative.w = -negative.w;

    dot = (a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w);
    negativeDot = (a->x * negative.x) + (a->y * negative.y) +
                  (a->z * negative.z) + (a->w * negative.w);
    if (dot < negativeDot) {
        dot = negativeDot;
        other = &negative;
    }

    if (g_quaternionInterpolationThresholdConstants < dot) {
        f32 magnitude;
        f32 scale;

        out->x = a->x + amount * (other->x - a->x);
        out->y = a->y + amount * (other->y - a->y);
        out->z = a->z + amount * (other->z - a->z);
        out->w = a->w + amount * (other->w - a->w);
        magnitude = Gu_Sqrtf((out->x * out->x) + (out->y * out->y) +
                                  (out->z * out->z) + (out->w * out->w));
        if (magnitude != 0.0f) {
            scale = *(&g_quaternionInterpolationThresholdConstants + 1) / magnitude;
            out->x *= scale;
            out->y *= scale;
            out->z *= scale;
            out->w *= scale;
        }
    } else {
        angle = Graphu64_ArcCos(dot);
        sine = Gu_Sinf(angle);
        if (sine == 0.0f) {
            *out = *a;
            return;
        }

        inverseSine = g_quaternionSlerpUnitScale / sine;
        scaleA = Gu_Sinf((g_quaternionSlerpUnitScale - amount) * angle) * inverseSine;
        scaleB = Gu_Sinf(amount * angle) * inverseSine;
        if (dot < negativeDot) {
            other = &negative;
        }

        out->x = (scaleA * a->x) + (scaleB * other->x);
        out->y = (scaleA * a->y) + (scaleB * other->y);
        out->z = (scaleA * a->z) + (scaleB * other->z);
        out->w = (scaleA * a->w) + (scaleB * other->w);
    }
}

CVector3 Graphu64_BlendRandomDirection(CVector3 *in, f32 amount) {
    CVector3 random;
    CVector3 result;
    CVector3 *randomPtr;
    f32 randomMagnitude;
    f32 randomScale;
    f32 inputMagnitude;
    f32 inputScale;

    random.x = (f32)((Graphu64_NextRandom() % 20000) - 10000);
    random.y = (f32)((Graphu64_NextRandom() % 20000) - 10000);
    random.z = (f32)((Graphu64_NextRandom() % 20000) - 10000);
    randomPtr = &random;

    randomMagnitude = Gu_Sqrtf((randomPtr->x * randomPtr->x) +
                                    (randomPtr->y * randomPtr->y) +
                                    (randomPtr->z * randomPtr->z));
    if (randomMagnitude != 0.0f) {
        randomScale = g_randomDirectionNormalizeScale / randomMagnitude;
        randomPtr->x *= randomScale;
        randomPtr->y *= randomScale;
        randomPtr->z *= randomScale;
    }

    inputMagnitude = Gu_Sqrtf((in->x * in->x) +
                                   (in->y * in->y) +
                                   (in->z * in->z));
    if (inputMagnitude != 0.0f) {
        inputScale = g_inputDirectionNormalizeScale / inputMagnitude;
        in->x *= inputScale;
        in->y *= inputScale;
        in->z *= inputScale;
    }

    result.x = in->x + amount * (randomPtr->x - in->x);
    result.y = in->y + amount * (randomPtr->y - in->y);
    result.z = in->z + amount * (randomPtr->z - in->z);
    return result;
}

CVector3 Graphu64_BlendRandomXDirection(CVector3 *in, f32 amount) {
    CVector3 random;
    CVector3 result;
    CVector3 *randomPtr;
    f32 randomMagnitude;
    f32 randomScale;
    f32 inputMagnitude;
    f32 inputScale;

    random.x = (f32)((Graphu64_NextRandom() % 20000) - 10000) *
               *(&g_inputDirectionNormalizeScale + 1);
    random.y = in->y;
    random.z = in->z;
    randomPtr = &random;

    randomMagnitude = Gu_Sqrtf((randomPtr->x * randomPtr->x) +
                                    (randomPtr->y * randomPtr->y) +
                                    (randomPtr->z * randomPtr->z));
    if (randomMagnitude != 0.0f) {
        randomScale = g_randomDirectionPairNormalizeConstants / randomMagnitude;
        randomPtr->x *= randomScale;
        randomPtr->y *= randomScale;
        randomPtr->z *= randomScale;
    }

    inputMagnitude = Gu_Sqrtf((in->x * in->x) +
                                   (in->y * in->y) +
                                   (in->z * in->z));
    if (inputMagnitude != 0.0f) {
        inputScale = *(&g_randomDirectionPairNormalizeConstants + 1) / inputMagnitude;
        in->x *= inputScale;
        in->y *= inputScale;
        in->z *= inputScale;
    }

    result.x = in->x + amount * (randomPtr->x - in->x);
    result.y = in->y + amount * (randomPtr->y - in->y);
    result.z = in->z + amount * (randomPtr->z - in->z);
    return result;
}

CVector3 Graphu64_BlendRandomYDirection(CVector3 *in, f32 amount) {
    CVector3 random;
    CVector3 result;
    CVector3 *randomPtr;
    f32 randomMagnitude;
    f32 randomScale;
    f32 inputMagnitude;
    f32 inputScale;

    random.x = in->x;
    random.y = ((f32)(Graphu64_NextRandom() % 20000) - g_randomDirectionYRangeConstants) * *(&g_randomDirectionYRangeConstants + 1);
    random.z = in->z;
    randomPtr = &random;

    randomMagnitude = Gu_Sqrtf((randomPtr->x * randomPtr->x) +
                                    (randomPtr->y * randomPtr->y) +
                                    (randomPtr->z * randomPtr->z));
    if (randomMagnitude != 0.0f) {
        randomScale = g_randomDirectionRotationNormalizeConstants / randomMagnitude;
        randomPtr->x *= randomScale;
        randomPtr->y *= randomScale;
        randomPtr->z *= randomScale;
    }

    inputMagnitude = Gu_Sqrtf((in->x * in->x) +
                                   (in->y * in->y) +
                                   (in->z * in->z));
    if (inputMagnitude != 0.0f) {
        inputScale = *(&g_randomDirectionRotationNormalizeConstants + 1) / inputMagnitude;
        in->x *= inputScale;
        in->y *= inputScale;
        in->z *= inputScale;
    }

    result.x = in->x + amount * (randomPtr->x - in->x);
    result.y = in->y + amount * (randomPtr->y - in->y);
    result.z = in->z + amount * (randomPtr->z - in->z);
    return result;
}

CVector3 *Graphu64_BlendRandomZDirection(CVector3 *out, CVector3 *in, f32 amount) {
    CVector3 random;
    CVector3 result;
    CVector3 *randomPtr;

    random.x = in->x;
    random.y = in->y;
    random.z = ((f32)(Graphu64_NextRandom() % 20000) - g_randomDirectionZRangeConstants) *
               *(&g_randomDirectionZRangeConstants + 1);

    randomPtr = &random;
    {
        f32 magnitude;
        f32 scale;

        magnitude = Gu_Sqrtf((randomPtr->x * randomPtr->x) +
                                  (randomPtr->y * randomPtr->y) +
                                  (randomPtr->z * randomPtr->z));
        if (magnitude != 0.0f) {
            scale = g_quaternionNormalizeConstants / magnitude;
            randomPtr->x *= scale;
            randomPtr->y *= scale;
            randomPtr->z *= scale;
        }
    }
    {
        f32 magnitude;
        f32 scale;

        magnitude = Gu_Sqrtf((in->x * in->x) +
                                  (in->y * in->y) +
                                  (in->z * in->z));
        if (magnitude != 0.0f) {
            scale = *(&g_quaternionNormalizeConstants + 1) / magnitude;
            in->x *= scale;
            in->y *= scale;
            in->z *= scale;
        }
    }

    result.x = in->x + amount * (randomPtr->x - in->x);
    result.y = in->y + amount * (randomPtr->y - in->y);
    result.z = in->z + amount * (randomPtr->z - in->z);
    *out = result;
    return out;
}

CQuatern Graphu64_BuildDirectionQuaternion(CVector3 *input) {
    CQuatern result;
    CVector3 normalized;
    CVector3 basis;
    CVector3 axis;
    f32 magnitude;
    f32 angle;
    f32 axisMagnitude;

    magnitude = Gu_Sqrtf((input->x * input->x) +
                              (input->y * input->y) +
                              (input->z * input->z));
    if (magnitude == 0.0f) {
        result.z = 0.0f;
        result.y = 0.0f;
        result.x = 0.0f;
        result.w = g_quaternionIdentityW;
    } else {
        f32 normalizationScale;

        normalizationScale = g_quaternionDirectionUnitScale / magnitude;
        normalized.x = input->x * normalizationScale;
        normalized.y = input->y * normalizationScale;
        normalized.z = input->z * normalizationScale;

        basis.x = 0.0f;
        basis.y = 0.0f;
        basis.z = g_quaternionDirectionUnitScale;

        if (normalized.z < 0.0f) {
            if (g_quaternionOppositeDirectionThreshold < -normalized.z) {
                goto pole;
            }
            goto general;
        }
        if (g_quaternionParallelDirectionThreshold < normalized.z) {
pole:
        {
            f32 halfAngle;
            f32 scale;

            halfAngle = 0.0f;
            scale = Gu_Sinf(halfAngle);
            result.z = normalized.z * scale;
            g_turretAimSine = scale;
            result.x = halfAngle;
            result.y = halfAngle;
            result.w = Math_Cosf(halfAngle);
        }
        } else {
general:
        {
            f32 halfAngle;
            f32 scale;

            angle = Graphu64_ArcCos((normalized.x * basis.x) +
                                  (normalized.y * basis.y) +
                                  (normalized.z * basis.z));
            axis.x = (basis.y * normalized.z) - (basis.z * normalized.y);
            axis.y = (basis.z * normalized.x) - (basis.x * normalized.z);
            axis.z = (basis.x * normalized.y) - (basis.y * normalized.x);

            axisMagnitude = Gu_Sqrtf((axis.x * axis.x) +
                                          (axis.y * axis.y) +
                                          (axis.z * axis.z));
            if (axisMagnitude != 0.0f) {
                f32 axisScale;

                axisScale = g_quaternionAxisNormalizeScale / axisMagnitude;
                axis.x *= axisScale;
                axis.y *= axisScale;
                axis.z *= axisScale;
            }

            halfAngle = angle * g_quaternionHalfAngleScale;
            scale = Gu_Sinf(halfAngle);
            result.x = axis.x * scale;
            result.y = axis.y * scale;
            result.z = axis.z * scale;
            g_turretAimSine = scale;
            result.w = Math_Cosf(halfAngle);
        }
        }
    }
    return result;
}

/* GRAPHU64_GETANGLEDISTANCE.CPP */

/** Heading of a direction in the XZ plane: acos of the dominant axis, clamped to [-1, 1]. */
f32 Graphu64_GetHorizontalAngle(CVector3 *direction) {
    f32 x = direction->x;
    f32 z = direction->z;
    f32 length = x * x + z * z;
    f32 angle;
    f32 arcCosAngle;
    if (length == 0.0f) {
        return 0.0f;
    }
    length = Gu_Sqrtf(length);
    if (length == 0.0f) {
        return 0.0f;
    }
    if (RW_ABS(x) < RW_ABS(z)) {
        x /= length;
        x = RW_MAX_GT(-1.0f, RW_MIN(x, 1.0f));
        arcCosAngle = Graphu64_ArcCos(x);
        angle = -arcCosAngle;
        if (z < 0.0f) {
            angle = arcCosAngle;
        }
        angle -= 1.5707964f;
    } else {
        z /= length;
        z = RW_MAX_GT(-1.0f, RW_MIN(z, 1.0f));
        arcCosAngle = Graphu64_ArcCos(-z);
        angle = -arcCosAngle;
        if (x < 0.0f) {
            angle = arcCosAngle;
        }
    }
    return angle;
}



/** Wrap an angle into [-pi, pi]. */
static inline f32 WrapAngle(f32 angle) {
    while (angle < -3.1415927f) {
        angle += 6.2831855f;
    }
    while (angle > 3.1415927f) {
        angle -= 6.2831855f;
    }
    return angle;
}
#define ANGLE_ABS(arcCosAngle) (-(arcCosAngle) < 0.0f ? (arcCosAngle) : -(arcCosAngle))
/** Absolute angle between two headings, each wrapped into [-pi, pi]. */
f32 Graphu64_GetAngleDistance(f32 target, f32 current) {
    return ANGLE_ABS(WrapAngle(target - WrapAngle(current)));
}

/** Component-wise multiply two 3-vectors. */
void Graphu64_MultiplyVectorComponents(CVector3 *result, CVector3 *left, CVector3 *right) {
    result->x = left->x * right->x;
    result->y = left->y * right->y;
    result->z = left->z * right->z;
}

/** Add two three-component vectors. */
void Graphu64_AddVec3(CVector3 *result, CVector3 *left, CVector3 *right) {
    result->x = left->x + right->x;
    result->y = left->y + right->y;
    result->z = left->z + right->z;
}

/** Subtract the right vector from the left vector. */
void Graphu64_SubtractVectors(CVector3 *difference, CVector3 *leftVector, CVector3 *rightVector) {
    difference->x = leftVector->x - rightVector->x;
    difference->y = leftVector->y - rightVector->y;
    difference->z = leftVector->z - rightVector->z;
}

/** Scale a 3-vector (inputVector) by a scalar (scaleFactor), store into scaledVector. */
void Graphu64_ScaleVector(void *output, void *input, f32 scaleFactor) {
    CVector3 *scaledVector = output;
    CVector3 *inputVector = input;
    (scaledVector)->x = (inputVector)->x * scaleFactor;
    (scaledVector)->y = (inputVector)->y * scaleFactor;
    (scaledVector)->z = (inputVector)->z * scaleFactor;
}

/** Lerp a 3-component vector: out = a + t * (b - a). */
void Graphu64_InterpolateVector(CVector3 *result, f32 t, CVector3 *start, CVector3 *end) {
    result->x = (start)->x + (t * ((end)->x - (start)->x));
    result->y = (start)->y + (t * ((end)->y - (start)->y));
    result->z = (start)->z + (t * ((end)->z - (start)->z));
}

/** Cross product of two vectors, written directly to the output (no aliasing guard). */
void Graphu64_CrossVectors(CVector3 *out, CVector3 *left, CVector3 *right) {
    out->x = (left->y * right->z) - (left->z * right->y);
    out->y = (left->z * right->x) - (left->x * right->z);
    out->z = (left->x * right->y) - (left->y * right->x);
}

void Graphu64_NormalizeVec3(f32 *vectorComponents) {
    f32 mag;
    f32 scale;

    mag = Gu_Sqrtf((vectorComponents[0] * vectorComponents[0]) + (vectorComponents[1] * vectorComponents[1]) + (vectorComponents[2] * vectorComponents[2]));
    if (mag != 0.0f) {
        scale = g_vectorNormalizeUnitScale / mag;
        vectorComponents[0] = vectorComponents[0] * scale;
        vectorComponents[1] = vectorComponents[1] * scale;
        vectorComponents[2] = vectorComponents[2] * scale;
    }
}

/** Intersect a line segment with a horizontal plane and write the point. */
void Graphu64_InterpolateAtHeight(CVector3 *out, CVector3 *start, CVector3 *end, f32 y) {
    f32 dy = end->y - start->y;

    if (dy == 0.0f) {
        *out = *start;
        return;
    }

    {
        f32 t = (y - start->y) / dy;
        out->x = start->x + (t * (end->x - start->x));
        out->y = y;
        out->z = start->z + (t * (end->z - start->z));
    }
}

void *Graphu64_ReflectVector(CVector3 *result, CVector3 *remaining, CVector3 *planeNormal, f32 restitution) {
    CVector3 projectedVector;
    f32 normalScale;
    f32 normalDot;
    f32 normalX;
    f32 inputX;

    inputX = remaining->x;
    normalX = planeNormal->x;
    normalDot = (inputX * normalX) + (remaining->y * planeNormal->y) + (remaining->z * planeNormal->z);
    normalScale = (restitution * normalDot) + normalDot;
    projectedVector.x = inputX - (normalScale * normalX);
    projectedVector.y = remaining->y - (normalScale * planeNormal->y);
    projectedVector.z = remaining->z - (normalScale * planeNormal->z);
    *result = projectedVector;
    return result;
}

void *Graphu64_ProjectVectorOntoPlane(CVector3 *result, CVector3 *remaining, CVector3 *planeNormal) {
    CVector3 projectedVector;
    f32 normalDot;
    f32 normalX;
    f32 inputX;

    inputX = remaining->x;
    normalX = planeNormal->x;
    normalDot = (inputX * normalX) + (remaining->y * planeNormal->y) + (remaining->z * planeNormal->z);
    projectedVector.x = inputX - (normalDot * normalX);
    projectedVector.y = remaining->y - (normalDot * planeNormal->y);
    projectedVector.z = remaining->z - (normalDot * planeNormal->z);
    *result = projectedVector;
    return result;
}

/* Keep this source unit's macros local to its body. */
#undef ANGLE_ABS

/* GRAPHU64_PROJECTONTOCROSSNORMAL.CPP */

static inline void normalizeProjectionNormal(CVector3 *normal) {
    f32 length;
    f32 inverse;
    length = Gu_Sqrtf(normal->x * normal->x + normal->y * normal->y + normal->z * normal->z);
    if (length != 0.0f) {
        inverse = g_vectorVerticalAngleLowerConstants / length;
        normal->x *= inverse;
        normal->y *= inverse;
        normal->z *= inverse;
    }
}

static inline void projectionCross(CVector3 *normal, CVector3 *a, CVector3 *b) {
    normal->x = a->y * b->z - a->z * b->y;
    normal->y = a->z * b->x - a->x * b->z;
    normal->z = a->x * b->y - a->y * b->x;
}

static inline void projectionScale(CVector3 *out, CVector3 *normal, f32 projection) {
    out->x = normal->x * projection;
    out->y = normal->y * projection;
    out->z = normal->z * projection;
}

CVector3 *Graphu64_ProjectOntoCrossNormal(CVector3 *out, CVector3 *value, CVector3 *a, CVector3 *b) {
    CVector3 normal;
    CVector3 projected;
    f32 length;
    f32 projection;
    projectionCross(&normal, a, b);
    normalizeProjectionNormal(&normal);
    projection = value->x * normal.x + value->y * normal.y + value->z * normal.z;
    projectionScale(&projected, &normal, projection);
    *out = projected;
    return out;
}

/* GRAPHU64_MATRIXFROMEULERXYZ.CPP */


static __inline__ CVector3 project(CVector3 *vector, CVector3 *planeNormal) {
    CVector3 projected;
    f32 dot;

    dot = (vector->x * planeNormal->x) + (vector->y * planeNormal->y) + (vector->z * planeNormal->z);
    projected.x = vector->x - (dot * planeNormal->x);
    projected.y = vector->y - (dot * planeNormal->y);
    projected.z = vector->z - (dot * planeNormal->z);
    return projected;
}


CVector3 Graphu64_ProjectVectorPreservingLength(CVector3 *remaining, CVector3 *planeNormal) {
    CVector3 projected;
    f32 projectedMagnitude;
    f32 magnitudeRatio;

    projected = project(remaining, planeNormal);

    projectedMagnitude = Gu_Sqrtf((projected.x * projected.x) +
                                       (projected.y * projected.y) +
                                       (projected.z * projected.z));
    if (projectedMagnitude != 0.0f) {
        magnitudeRatio = Gu_Sqrtf((remaining->x * remaining->x) +
                                       (remaining->y * remaining->y) +
                                       (remaining->z * remaining->z)) / projectedMagnitude;

        projected.x *= magnitudeRatio;
        projected.y *= magnitudeRatio;
        projected.z *= magnitudeRatio;
    }

    return projected;
}

s32 Graphu64_LimitVectorLength(f32 *vectorComponents, f32 maximumLength) {
    f32 magSq;
    f32 mag;
    f32 scale;

    magSq = (vectorComponents[0] * vectorComponents[0]) + (vectorComponents[1] * vectorComponents[1]) + (vectorComponents[2] * vectorComponents[2]);
    if ((maximumLength * maximumLength) < magSq) {
        mag = Gu_Sqrtf(magSq);
        if (mag == 0.0f) {
            return 0;
        }
        scale = maximumLength / mag;
        vectorComponents[0] = vectorComponents[0] * scale;
        vectorComponents[1] = vectorComponents[1] * scale;
        vectorComponents[2] = vectorComponents[2] * scale;
        return 1;
    }
    return 0;
}

void Graphu64_NoOperation(void) {
}

f32 Graphu64_GetVerticalAngle(f32 *delta) {
    f32 y;
    f32 zero;
    f32 x;
    f32 z;
    f32 magnitudeSquared;
    f32 ratio;

    y = delta[1];
    zero = 0.0f;
    x = delta[0];
    z = delta[2];
    if (y == zero) {
        return zero;
    }
    magnitudeSquared = (x * x) + (y * y) + (z * z);
    if (magnitudeSquared == zero) {
        return zero;
    }
    ratio = y / Gu_Sqrtf(magnitudeSquared);
    if (ratio < *(&g_vectorVerticalAngleLowerConstants + 1)) {
        return zero;
    }
    if (g_vectorVerticalAngleUpperConstants < ratio) {
        goto return_zero;
    }
    return Graphu64_ArcCos(ratio) - *(&g_vectorVerticalAngleUpperConstants + 1);

return_zero:
    return zero;
}

f32 Graphu64_GetSquaredDistance(f32 *a, f32 *b) {
    f32 dx = a[0] - b[0];
    f32 dy = a[1] - b[1];
    f32 dz = a[2] - b[2];
    return (dx * dx) + (dy * dy) + (dz * dz);
}

f32 Graphu64_GetPointDistance(f32 *a, f32 *b) {
    f32 dx = a[0] - b[0];
    f32 dy = a[1] - b[1];
    f32 dz = a[2] - b[2];
    return Gu_Sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

void Graphu64_ClampMotionLength(CVector3 *motion, f32 maximumLength) {
    f32 magSq;
    f32 mag;
    f32 scale;

    magSq = (motion->x * motion->x) + (motion->y * motion->y) + (motion->z * motion->z);
    if ((maximumLength * maximumLength) < magSq) {
        mag = Gu_Sqrtf(magSq);
        scale = maximumLength / mag;
        motion->x = motion->x * scale;
        motion->y = motion->y * scale;
        motion->z = motion->z * scale;
    }
}

/** Reset the matrix to identity-diagonal * g_identityAndFixedMatrixConstants, zeroing the rest. */
void Graphu64_IdentityMatrix(Matrix *matrixStorage) {
    f32 zero = 0.0f;

    matrixStorage->m[15] = g_identityAndFixedMatrixConstants;
    matrixStorage->m[10] = g_identityAndFixedMatrixConstants;
    matrixStorage->m[5] = g_identityAndFixedMatrixConstants;
    matrixStorage->m[0] = g_identityAndFixedMatrixConstants;
    matrixStorage->m[14] = zero;
    matrixStorage->m[13] = zero;
    matrixStorage->m[12] = zero;
    matrixStorage->m[11] = zero;
    matrixStorage->m[9] = zero;
    matrixStorage->m[8] = zero;
    matrixStorage->m[7] = zero;
    matrixStorage->m[6] = zero;
    matrixStorage->m[4] = zero;
    matrixStorage->m[3] = zero;
    matrixStorage->m[2] = zero;
    matrixStorage->m[1] = zero;
}

void Graphu64_ClampMatrixToFixedRange(f32 *matrixComponents) {
    f32 *rowCursor;
    f32 *elementCursor;
    f32 elementValue;
    s32 i;
    s32 j;
    f32 maxVal;
    f32 minVal;

    maxVal = *(&g_identityAndFixedMatrixConstants + 1);
    minVal = g_matrixClampAndProjectionConstants;
    rowCursor = matrixComponents;
    j = 0;
    do {
        i = 0;
        elementCursor = rowCursor;
        do {
            elementValue = *elementCursor;
            if (maxVal < elementValue) {
                *elementCursor = maxVal;
            } else if (elementValue < minVal) {
                *elementCursor = minVal;
            }
            i += 1;
            elementCursor += 1;
        } while (i < 4);
        j += 1;
        rowCursor += 4;
    } while (j < 4);
}

void Graphu64_TransformPoint(Matrix *matrix, void *inputPoint, void *transformedPoint) {
    CVector3 *v = inputPoint;
    CVector3 *out = transformedPoint;

    out->x = (matrix->m[0] * v->x)
           + (matrix->m[4] * v->y)
           + (matrix->m[8] * v->z)
           + matrix->m[12];
    out->y = (matrix->m[1] * v->x)
           + (matrix->m[5] * v->y)
           + (matrix->m[9] * v->z)
           + matrix->m[13];
    out->z = (matrix->m[2] * v->x)
           + (matrix->m[6] * v->y)
           + (matrix->m[10] * v->z)
           + matrix->m[14];
}

/* Transforms a count of points by the affine part of a 4x4 matrix, writing each transformed point to an output array. */
void Graphu64_TransformPoints(f32 *m, f32 *in, f32 *out, u32 count) {
    f32 vx, vy, vz;

    while (count-- != 0) {
        vx = in[0];
        vy = in[1];
        vz = in[2];
        out[0] = (m[0] * vx) + (m[4] * vy) + (m[8] * vz) + m[12];
        out[1] = (m[1] * vx) + (m[5] * vy) + (m[9] * vz) + m[13];
        out[2] = (m[2] * vx) + (m[6] * vy) + (m[10] * vz) + m[14];
        in += 3;
        out += 3;
    }
}

void Graphu64_ProjectPoint(Matrix *matrix, void *inputPoint, CVector3 *localDirection) {
    CVector3 *v = inputPoint;
    f32 w;
    f32 scale;

    localDirection->x = (matrix->m[0] * v->x)
                       + (matrix->m[4] * v->y)
                       + (matrix->m[8] * v->z)
                       + matrix->m[12];
    localDirection->y = (matrix->m[1] * v->x)
                       + (matrix->m[5] * v->y)
                       + (matrix->m[9] * v->z)
                       + matrix->m[13];
    localDirection->z = (matrix->m[2] * v->x)
                       + (matrix->m[6] * v->y)
                       + (matrix->m[10] * v->z)
                       + matrix->m[14];
    w = (matrix->m[3] * v->x)
        + (matrix->m[7] * v->y)
        + (matrix->m[11] * v->z)
        + matrix->m[15];
    if (w != 0.0f) {
        scale = *(&g_matrixClampAndProjectionConstants + 1) / w;
        localDirection->x = localDirection->x * scale;
        localDirection->y = localDirection->y * scale;
        localDirection->z = localDirection->z * scale;
    }
}

void Graphu64_TransformDirection(Matrix *matrix, void *inputDirection, void *transformedDirection) {
    CVector3 *v = inputDirection;
    CVector3 *out = transformedDirection;

    out->x = (matrix->m[0] * v->x)
                       + (matrix->m[4] * v->y)
                       + (matrix->m[8] * v->z);
    out->y = (matrix->m[1] * v->x)
                       + (matrix->m[5] * v->y)
                       + (matrix->m[9] * v->z);
    out->z = (matrix->m[2] * v->x)
                       + (matrix->m[6] * v->y)
                       + (matrix->m[10] * v->z);
}

void Graphu64_TransformDirectionTranspose(Matrix *matrix, void *inputDirection, void *outputDirection) {
    CVector3 *v = inputDirection;
    CVector3 *out = outputDirection;

    out->x = (matrix->m[0] * v->x)
                       + (matrix->m[1] * v->y)
                       + (matrix->m[2] * v->z);
    out->y = (matrix->m[4] * v->x)
                       + (matrix->m[5] * v->y)
                       + (matrix->m[6] * v->z);
    out->z = (matrix->m[8] * v->x)
                       + (matrix->m[9] * v->y)
                       + (matrix->m[10] * v->z);
}

void Graphu64_BuildTranslationMatrix(Matrix *matrix, f32 translationX, f32 translationY, f32 translationZ) {
    f32 val = g_translationAndScaleMatrixUnitConstants;
    f32 zero = 0.0f;

    matrix->m[12] = translationX;
    matrix->m[13] = translationY;
    matrix->m[14] = translationZ;
    matrix->m[15] = val;
    matrix->m[10] = val;
    matrix->m[5] = val;
    matrix->m[0] = val;
    matrix->m[11] = zero;
    matrix->m[9] = zero;
    matrix->m[8] = zero;
    matrix->m[7] = zero;
    matrix->m[6] = zero;
    matrix->m[4] = zero;
    matrix->m[3] = zero;
    matrix->m[2] = zero;
    matrix->m[1] = zero;
}

void Graphu64_BuildScaleMatrix(Matrix *matrix, f32 scaleX, f32 scaleY, f32 scaleZ) {
    f32 val = *(&g_translationAndScaleMatrixUnitConstants + 1);
    f32 zero = 0.0f;

    matrix->m[0] = scaleX;
    matrix->m[5] = scaleY;
    matrix->m[10] = scaleZ;
    matrix->m[15] = val;
    matrix->m[14] = zero;
    matrix->m[13] = zero;
    matrix->m[12] = zero;
    matrix->m[11] = zero;
    matrix->m[9] = zero;
    matrix->m[8] = zero;
    matrix->m[7] = zero;
    matrix->m[6] = zero;
    matrix->m[4] = zero;
    matrix->m[3] = zero;
    matrix->m[2] = zero;
    matrix->m[1] = zero;
}

void Graphu64_BuildAxisAngleMatrix(f32 (*mfThis)[4], f32 Theta, f32 X, f32 Y, f32 Z) {
    f32 sine;
    f32 cosine;
    f32 ab, bc, ca, t, one;

    sine = Gu_Sinf(Theta);
    cosine = Math_Cosf(Theta);

    one = g_inverseAffineHomogeneousScale;
    t = one - cosine;
    ab = X * Y * t;
    bc = Y * Z * t;
    ca = Z * X * t;

    mfThis[0][3] = mfThis[1][3] = mfThis[2][3] =
    mfThis[3][0] = mfThis[3][1] = mfThis[3][2] = 0.0f;
    mfThis[3][3] = one;

    t = X * X;
    X *= sine;
    mfThis[0][0] = t + cosine * (one - t);
    mfThis[2][1] = bc - X;
    mfThis[1][2] = bc + X;

    t = Y * Y;
    Y *= sine;
    mfThis[1][1] = t + cosine * (one - t);
    mfThis[2][0] = ca + Y;
    mfThis[0][2] = ca - Y;

    t = Z * Z;
    Z *= sine;
    mfThis[2][2] = t + cosine * (one - t);
    mfThis[1][0] = ab - Z;
    mfThis[0][1] = ab + Z;
}

void Graphu64_MatrixFromEulerXYZ(f32 *m, f32 x, f32 y, f32 z)
{
  f32 zero;
  f32 ax = Gu_Sinf(x);
  f32 bx = Math_Cosf(x);
  f32 ay = Gu_Sinf(y);
  f32 by = Math_Cosf(y);
  int firstMatrixElement;
  f32 az = Gu_Sinf(z);
  f32 bz = Math_Cosf(z);
  firstMatrixElement = 0;
  m[firstMatrixElement] = by * bz;
  m[1] = by * az;
  m[2] = -ay;
  zero = 0.0f;
  m[14] = zero;
  m[13] = zero;
  m[12] = zero;
  m[11] = zero;
  m[7] = zero;
  m[3] = zero;
  m[4] = ((ax * ay) * bz) - (bx * az);
  m[5] = ((ax * ay) * az) + (bx * bz);
  m[6] = ax * by;
  m[8] = ((bx * ay) * bz) + (ax * az);
  m[9] = ((bx * ay) * az) - (ax * bz);
  m[10] = bx * by;
  m[15] = g_eulerMatrixHomogeneousScale;
}

/** Trivial busy-wait delay loop (no side effects). */
void Graphu64_RunCountdown(void) {
    s32 count;

    count = 3;
    do {
        count -= 1;
    } while (count >= 0);
}

/* BUILDDIRECTIONMATRIX.CPP */

/* Builds an orientation matrix whose third row is the given direction: the first row is the cross product of the up vector g_directionMatrixUnitConstants_us_rev1 with it, or the X axis when the direction is within the vertical thresholds, the second row is the cross product of the first row with it, all three rows are normalised and the rest is identity. */

/* Copies a 4x4 float matrix while scaling its first three rows by three per-row factors, zeroing their fourth column and setting the last element to the canonical unit constant. */

/* Expands a 4x4 transform into an affine 4x4 matrix with its second and third rows swapped, a zero last column and the pooled corner g_translationAndSwappedBasisUnitConstants[1]. */

/* Expands a 4x4 transform into an affine 4x4 matrix with its second and third columns swapped, a zero last column and the pooled corner g_swappedCoordinatesAndWrapConstants. */

void CopyMatrix(float *destinationMatrix, float *sourceMatrix) {
    destinationMatrix[0] = sourceMatrix[0];
    destinationMatrix[1] = sourceMatrix[1];
    destinationMatrix[2] = sourceMatrix[2];
    destinationMatrix[3] = sourceMatrix[3];
    destinationMatrix[4] = sourceMatrix[4];
    destinationMatrix[5] = sourceMatrix[5];
    destinationMatrix[6] = sourceMatrix[6];
    destinationMatrix[7] = sourceMatrix[7];
    destinationMatrix[8] = sourceMatrix[8];
    destinationMatrix[9] = sourceMatrix[9];
    destinationMatrix[10] = sourceMatrix[10];
    destinationMatrix[11] = sourceMatrix[11];
    destinationMatrix[12] = sourceMatrix[12];
    destinationMatrix[13] = sourceMatrix[13];
    destinationMatrix[14] = sourceMatrix[14];
    destinationMatrix[15] = sourceMatrix[15];
}

void Graphu64_TransposeMatrixBasis(f32 *destination, f32 *source) {
    s32 col;
    s32 row;

    for (col = 0; col < 16; col++) {
        destination[col] = source[col];
    }

    for (col = 0; col < 3; col++) {
        for (row = 0; row < 3; row++) {
            destination[col * 4 + row] = source[row * 4 + col];
        }
    }
}

void Graphu64_BuildPlaneProjectionMatrix(void *projection, CVector3 *projectionDirection, f32 plane) {
    Matrix *o = projection;
    f32 zero = 0.0f;
    f32 unit;
    f32 slopeZ;
    f32 slopeX;
    f32 inverseVertical;

    unit = g_planeProjectionAndDirectionConstants;
    o->m[15] = unit;
    o->m[10] = unit;
    o->m[0] = unit;
    o->m[14] = zero;
    o->m[13] = zero;
    o->m[12] = zero;
    o->m[11] = zero;
    o->m[9] = zero;
    o->m[8] = zero;
    o->m[7] = zero;
    o->m[3] = zero;
    o->m[2] = zero;
    o->m[1] = zero;
    inverseVertical = unit / projectionDirection->y;
    slopeX = projectionDirection->x * inverseVertical;
    slopeZ = projectionDirection->z * inverseVertical;
    o->m[13] = plane;
    o->m[5] = zero;
    o->m[4] = -slopeX;
    o->m[6] = -slopeZ;
    o->m[12] = plane * slopeX;
    o->m[14] = plane * slopeZ;
}

void BuildDirectionMatrix(CMatrix4 *matrix, CVector3 *direction) {
    CVector3 up;
    CVector3 *upVector = (void *)&g_directionMatrixUnitConstants_de[0].y;

    up = *upVector;
    if (direction->y < 0.0f ? (&g_planeProjectionAndDirectionConstants)[1] <= -direction->y : g_directionVerticalThreshold.value <= direction->y) {
        matrix->right.y = 0;
        matrix->right.z = 0;
        matrix->right.x = g_directionFallbackAxisScale;
    } else {
        Graphu64_CrossVectors(&matrix->right, &up, direction);
    }
    Graphu64_CrossVectors(&matrix->up, &matrix->right, direction);
    matrix->forward = *direction;
    Graphu64_NormalizeVec3(&matrix->right);
    Graphu64_NormalizeVec3(&matrix->up);
    Graphu64_NormalizeVec3(&matrix->forward);
    matrix->m03 = matrix->m13 = matrix->m23 = matrix->m30 = matrix->m31 = matrix->m32 = 0.0f;
    matrix->m33 = g_directionMatrixHomogeneousScale;
}

/** Copy the three floating components. */
void Graphu64_GetMatrixTranslation(char *object, float *output) {
    Matrix *matrix = (void *)object;
    output[0] = matrix->m[12];
    output[1] = matrix->m[13];
    output[2] = matrix->m[14];
}

void Graphu64_GetMatrixScale(Matrix *matrix, f32 *scaleOutput) {
    CVector3 axisVector;

    axisVector.x = matrix->m[0];
    axisVector.y = matrix->m[1];
    axisVector.z = matrix->m[2];
    scaleOutput[0] = Gu_Sqrtf((axisVector.x * axisVector.x) + (axisVector.y * axisVector.y) + (axisVector.z * axisVector.z));

    axisVector.x = matrix->m[4];
    axisVector.y = matrix->m[5];
    axisVector.z = matrix->m[6];
    scaleOutput[1] = Gu_Sqrtf((axisVector.x * axisVector.x) + (axisVector.y * axisVector.y) + (axisVector.z * axisVector.z));

    axisVector.x = matrix->m[8];
    axisVector.y = matrix->m[9];
    axisVector.z = matrix->m[10];
    scaleOutput[2] = Gu_Sqrtf((axisVector.x * axisVector.x) + (axisVector.y * axisVector.y) + (axisVector.z * axisVector.z));
}

void TranslateMatrixLocal(Matrix *matrix, f32 tiltX, f32 lift, f32 translationZ) {

    matrix->m[12] = matrix->m[12] + (tiltX * matrix->m[0] + lift * matrix->m[4] + translationZ * matrix->m[8]);
    matrix->m[13] = matrix->m[13] + (tiltX * matrix->m[1] + lift * matrix->m[5] + translationZ * matrix->m[9]);
    matrix->m[14] = matrix->m[14] + (tiltX * matrix->m[2] + lift * matrix->m[6] + translationZ * matrix->m[10]);
}

/** Add three floating arguments to the vector. */
void TranslateMatrix(char *object, float x, float y, float z) {
    Matrix *matrix = (void *)object;
    matrix->m[12] += x;
    matrix->m[13] += y;
    matrix->m[14] += z;
}

/** Scale the first three rows of a matrix's basis columns by sx, sy, sz. */
void ScaleMatrixLocal(Matrix *matrix, f32 sx, f32 sy, f32 sz) {

    matrix->m[0] = matrix->m[0] * sx;
    matrix->m[1] = matrix->m[1] * sx;
    matrix->m[2] = matrix->m[2] * sx;
    matrix->m[4] = matrix->m[4] * sy;
    matrix->m[5] = matrix->m[5] * sy;
    matrix->m[6] = matrix->m[6] * sy;
    matrix->m[8] = matrix->m[8] * sz;
    matrix->m[9] = matrix->m[9] * sz;
    matrix->m[10] = matrix->m[10] * sz;
}

void Graphu64_CopyScaledMatrix(f32 *destination, f32 *source, f32 sx, f32 sy, f32 sz) {
    destination[0] = source[0] * sx;
    destination[1] = source[1] * sx;
    destination[2] = source[2] * sx;
    destination[4] = source[4] * sy;
    destination[5] = source[5] * sy;
    destination[6] = source[6] * sy;
    destination[8] = source[8] * sz;
    destination[9] = source[9] * sz;
    destination[10] = source[10] * sz;
    destination[12] = source[12];
    destination[13] = source[13];
    destination[14] = source[14];
    destination[3] = destination[7] = destination[11] = 0.0f;
    destination[15] = g_scaledMatrixHomogeneousScale;
}

/** Scale the xyz columns of a 4-row matrix by sx, sy, sz. */
void Graphu64_ScaleMatrixWorld(Matrix *matrix, f32 sx, f32 sy, f32 sz) {

    matrix->m[0] = matrix->m[0] * sx;
    matrix->m[4] = matrix->m[4] * sx;
    matrix->m[8] = matrix->m[8] * sx;
    matrix->m[12] = matrix->m[12] * sx;
    matrix->m[1] = matrix->m[1] * sy;
    matrix->m[5] = matrix->m[5] * sy;
    matrix->m[9] = matrix->m[9] * sy;
    matrix->m[13] = matrix->m[13] * sy;
    matrix->m[2] = matrix->m[2] * sz;
    matrix->m[6] = matrix->m[6] * sz;
    matrix->m[10] = matrix->m[10] * sz;
    matrix->m[14] = matrix->m[14] * sz;
}

void BuildPitchMatrix(struct CMatrix4 *rest, f32 pitchAngle) {
    f32 sinAngle;
    f32 cosAngle;
    f32 zero;
    f32 identity;

    sinAngle = Gu_Sinf(pitchAngle);
    zero = 0;
    identity = g_pitchAndRollMatrixUnitConstants[0];
    rest->forward.y = -sinAngle;
    rest->up.z = sinAngle;
    rest->right.y = zero;
    rest->up.x = zero;
    rest->right.z = zero;
    rest->forward.x = zero;
    rest->m32 = zero;
    rest->m31 = zero;
    rest->m30 = zero;
    rest->m23 = zero;
    rest->m13 = zero;
    rest->m03 = zero;
    rest->m33 = identity;
    rest->right.x = identity;
    cosAngle = Math_Cosf(pitchAngle);
    rest->forward.z = cosAngle;
    rest->up.y = cosAngle;
}

void BuildYawMatrix(CMatrix4 *matrixStorage, f32 yawAngle)
{
  struct CMatrix4 *matrix = matrixStorage;
  f32 sinAngle;
  f32 cosAngle;
  f32 zero;
  f32 identity;
  zero = 0;
  sinAngle = Gu_Sinf(yawAngle);
  identity = g_pitchAndRollMatrixUnitConstants[1];
  matrix->forward.x = sinAngle;
  matrix->right.y = zero;
  matrix->right.z = -sinAngle;
  matrix->up.x = zero;
  matrix->up.z = zero;
  matrix->forward.y = zero;
  matrix->m32 = zero;
  matrix->m31 = zero;
  matrix->m30 = zero;
  matrix->m23 = zero;
  matrix->m13 = zero;
  matrix->m03 = zero;
  matrix->m33 = identity;
  matrix->up.y = identity;
  cosAngle = Math_Cosf(yawAngle);
  matrix->forward.z = cosAngle;
  matrix->right.x = cosAngle;
}

void BuildRollMatrix(struct CMatrix4 *matrix, f32 rollAngle) {
    f32 sinAngle;
    f32 cosAngle;
    f32 zero;
    f32 one;

    sinAngle = Gu_Sinf(rollAngle);
    zero = (f32) 0;
    one = g_translationAndSwappedBasisUnitConstants[0];
    matrix->right.z = zero;
    matrix->forward.x = zero;
    matrix->up.z = zero;
    matrix->forward.y = zero;
    matrix->m32 = zero;
    matrix->m31 = zero;
    matrix->m30 = zero;
    matrix->m23 = zero;
    matrix->m13 = zero;
    matrix->m03 = zero;
    matrix->forward.z = one;
    matrix->m33 = one;
    cosAngle = Math_Cosf(rollAngle);
    matrix->up.y = cosAngle;
    matrix->right.x = cosAngle;
    matrix->up.x = -sinAngle;
    matrix->right.y = sinAngle;
}

void PitchMatrixLocal(CMatrix4 *matrixStorage, f32 pitchAngle) {
    struct CMatrix4 *matrix = matrixStorage;
    f32 sinAngle;
    f32 cosAngle;
    f32 negatedSin;
    f32 savedComponent;

    sinAngle = Gu_Sinf(pitchAngle);
    cosAngle = Math_Cosf(pitchAngle);
    negatedSin = -sinAngle;

    savedComponent = matrix->up.x;
    matrix->up.x = (cosAngle * savedComponent) + (sinAngle * matrix->forward.x);
    matrix->forward.x = (negatedSin * savedComponent) + (cosAngle * matrix->forward.x);

    savedComponent = matrix->up.y;
    matrix->up.y = (cosAngle * savedComponent) + (sinAngle * matrix->forward.y);
    matrix->forward.y = (negatedSin * savedComponent) + (cosAngle * matrix->forward.y);

    savedComponent = matrix->up.z;
    matrix->up.z = (cosAngle * savedComponent) + (sinAngle * matrix->forward.z);
    matrix->forward.z = (negatedSin * savedComponent) + (cosAngle * matrix->forward.z);
}

void PitchMatrix(CMatrix4 *matrixStorage, f32 pitchAngle) {
    struct CMatrix4 *matrix = matrixStorage;
    f32 sinAngle;
    f32 cosAngle;
    f32 negatedSin;
    f32 savedComponent;

    sinAngle = Gu_Sinf(pitchAngle);
    cosAngle = Math_Cosf(pitchAngle);
    negatedSin = -sinAngle;

    savedComponent = matrix->right.y;
    matrix->right.y = (savedComponent * cosAngle) + (matrix->right.z * negatedSin);
    matrix->right.z = (savedComponent * sinAngle) + (matrix->right.z * cosAngle);

    savedComponent = matrix->up.y;
    matrix->up.y = (savedComponent * cosAngle) + (matrix->up.z * negatedSin);
    matrix->up.z = (savedComponent * sinAngle) + (matrix->up.z * cosAngle);

    savedComponent = matrix->forward.y;
    matrix->forward.y = (savedComponent * cosAngle) + (matrix->forward.z * negatedSin);
    matrix->forward.z = (savedComponent * sinAngle) + (matrix->forward.z * cosAngle);

    savedComponent = matrix->m31;
    matrix->m31 = (savedComponent * cosAngle) + (matrix->m32 * negatedSin);
    matrix->m32 = (savedComponent * sinAngle) + (matrix->m32 * cosAngle);
}

void YawMatrixLocal(CMatrix4 *matrix, f32 yawAngle) {
    struct CMatrix4 *matrixView = matrix;
    f32 sinAngle;
    f32 cosAngle;
    f32 negatedSin;
    f32 savedComponent;

    sinAngle = Gu_Sinf(yawAngle);
    cosAngle = Math_Cosf(yawAngle);
    negatedSin = -sinAngle;

    savedComponent = matrixView->right.x;
    matrixView->right.x = (cosAngle * savedComponent) + (negatedSin * matrixView->forward.x);
    matrixView->forward.x = (sinAngle * savedComponent) + (cosAngle * matrixView->forward.x);

    savedComponent = matrixView->right.y;
    matrixView->right.y = (cosAngle * savedComponent) + (negatedSin * matrixView->forward.y);
    matrixView->forward.y = (sinAngle * savedComponent) + (cosAngle * matrixView->forward.y);

    savedComponent = matrixView->right.z;
    matrixView->right.z = (cosAngle * savedComponent) + (negatedSin * matrixView->forward.z);
    matrixView->forward.z = (sinAngle * savedComponent) + (cosAngle * matrixView->forward.z);
}

void YawMatrix(CMatrix4 *matrix, f32 yawAngle) {
    struct CMatrix4 *matrixView = matrix;
    f32 sinAngle;
    f32 cosAngle;
    f32 negatedSin;
    f32 savedComponent;

    sinAngle = Gu_Sinf(yawAngle);
    cosAngle = Math_Cosf(yawAngle);
    negatedSin = -sinAngle;

    savedComponent = matrixView->right.x;
    matrixView->right.x = (savedComponent * cosAngle) + (matrixView->right.z * sinAngle);
    matrixView->right.z = (savedComponent * negatedSin) + (matrixView->right.z * cosAngle);

    savedComponent = matrixView->up.x;
    matrixView->up.x = (savedComponent * cosAngle) + (matrixView->up.z * sinAngle);
    matrixView->up.z = (savedComponent * negatedSin) + (matrixView->up.z * cosAngle);

    savedComponent = matrixView->forward.x;
    matrixView->forward.x = (savedComponent * cosAngle) + (matrixView->forward.z * sinAngle);
    matrixView->forward.z = (savedComponent * negatedSin) + (matrixView->forward.z * cosAngle);

    savedComponent = matrixView->m30;
    matrixView->m30 = (savedComponent * cosAngle) + (matrixView->m32 * sinAngle);
    matrixView->m32 = (savedComponent * negatedSin) + (matrixView->m32 * cosAngle);
}

void RollMatrixLocal(CMatrix4 *matrix, f32 rollAngle) {
    struct CMatrix4 *matrixView = matrix;
    f32 sinAngle;
    f32 cosAngle;
    f32 negatedSin;
    f32 savedComponent;

    sinAngle = Gu_Sinf(rollAngle);
    cosAngle = Math_Cosf(rollAngle);
    negatedSin = -sinAngle;

    savedComponent = matrixView->right.x;
    matrixView->right.x = (cosAngle * savedComponent) + (sinAngle * matrixView->up.x);
    matrixView->up.x = (negatedSin * savedComponent) + (cosAngle * matrixView->up.x);

    savedComponent = matrixView->right.y;
    matrixView->right.y = (cosAngle * savedComponent) + (sinAngle * matrixView->up.y);
    matrixView->up.y = (negatedSin * savedComponent) + (cosAngle * matrixView->up.y);

    savedComponent = matrixView->right.z;
    matrixView->right.z = (cosAngle * savedComponent) + (sinAngle * matrixView->up.z);
    matrixView->up.z = (negatedSin * savedComponent) + (cosAngle * matrixView->up.z);
}

void RollMatrix(CMatrix4 *matrixStorage, f32 rollAngle) {
    struct CMatrix4 *matrix = matrixStorage;
    f32 sinAngle;
    f32 cosAngle;
    f32 negatedSin;
    f32 savedComponent;

    sinAngle = Gu_Sinf(rollAngle);
    cosAngle = Math_Cosf(rollAngle);
    negatedSin = -sinAngle;

    savedComponent = matrix->right.x;
    matrix->right.x = (savedComponent * cosAngle) + (matrix->right.y * negatedSin);
    matrix->right.y = (savedComponent * sinAngle) + (matrix->right.y * cosAngle);

    savedComponent = matrix->up.x;
    matrix->up.x = (savedComponent * cosAngle) + (matrix->up.y * negatedSin);
    matrix->up.y = (savedComponent * sinAngle) + (matrix->up.y * cosAngle);

    savedComponent = matrix->forward.x;
    matrix->forward.x = (savedComponent * cosAngle) + (matrix->forward.y * negatedSin);
    matrix->forward.y = (savedComponent * sinAngle) + (matrix->forward.y * cosAngle);

    savedComponent = matrix->m30;
    matrix->m30 = (savedComponent * cosAngle) + (matrix->m31 * negatedSin);
    matrix->m31 = (savedComponent * sinAngle) + (matrix->m31 * cosAngle);
}

/** Swap the two float-groups and 0x20 (three floats each). */
void SwapMatrixUpForward(struct CMatrix4 *object) {
    float t;
    t = object->up.x;
    object->up.x = object->forward.x;
    object->forward.x = t;

    t = object->up.y;
    object->up.y = object->forward.y;
    object->forward.y = t;

    t = object->up.z;
    object->up.z = object->forward.z;
    object->forward.z = t;
}

void Graphu64_CopySwappedMatrixBasis(f32 *dst, f32 *src) {
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[4] = src[8];
    dst[5] = src[9];
    dst[6] = src[10];
    dst[8] = src[4];
    dst[9] = src[5];
    dst[10] = src[6];
    dst[12] = src[12];
    dst[13] = src[13];
    dst[14] = src[14];
    dst[3] = dst[7] = dst[11] = 0.0f;
    dst[15] = g_translationAndSwappedBasisUnitConstants[1];
}

/** Swap the two floats within each of the object's four 0x10-byte records. */
void Graphu64_SwapMatrixCoordinates(struct CMatrix4 *object) {
    float t;
    t = object->right.y;
    object->right.y = object->right.z;
    object->right.z = t;

    t = object->up.y;
    object->up.y = object->up.z;
    object->up.z = t;

    t = object->forward.y;
    object->forward.y = object->forward.z;
    object->forward.z = t;

    t = object->m31;
    object->m31 = object->m32;
    object->m32 = t;
}

void Graphu64_CopySwappedMatrixCoordinates(f32 *dst, f32 *src) {
    dst[0] = src[0];
    dst[1] = src[2];
    dst[2] = src[1];
    dst[4] = src[4];
    dst[5] = src[6];
    dst[6] = src[5];
    dst[8] = src[8];
    dst[9] = src[10];
    dst[10] = src[9];
    dst[12] = src[12];
    dst[13] = src[14];
    dst[14] = src[13];
    dst[3] = dst[7] = dst[11] = 0.0f;
    dst[15] = g_swappedCoordinatesAndWrapConstants[0];
}

f32 Graphu64_InterpolateWrappedValue(f32 fraction, f32 first, f32 second) {
    f32 wrappedDifference;
    f32 result;

    Graphu64_WrapPeriodicValue(&first);
    Graphu64_WrapPeriodicValue(&second);
    if (first > second) {
        wrappedDifference = second + g_swappedCoordinatesAndWrapConstants[1];
        if ((wrappedDifference - first) < (first - second)) {
            second = wrappedDifference;
        }
    } else {
        wrappedDifference = second - g_wrappedInterpolationPeriod;
        if ((first - wrappedDifference) < (second - first)) {
            second = wrappedDifference;
        }
    }
    result = first + (fraction * (second - first));
    Graphu64_WrapPeriodicValue(&result);
    return result;
}

f32 Graphu64_GetWrappedDifference(f32 firstValue, f32 secondValue) {
    f32 wrappedSecond;

    Graphu64_WrapPeriodicValue(&firstValue);
    Graphu64_WrapPeriodicValue(&secondValue);
    if (firstValue > secondValue) {
        wrappedSecond = secondValue + g_wrappedDifferenceUpperPeriod;
        if ((wrappedSecond - firstValue) < (firstValue - secondValue)) {
            secondValue = wrappedSecond;
        }
    } else {
        wrappedSecond = secondValue - g_wrappedDifferenceAndApproachConstants[0];
        if ((firstValue - wrappedSecond) < (secondValue - firstValue)) {
            secondValue = wrappedSecond;
        }
    }
    return firstValue - secondValue;
}

void Graphu64_WrapPeriodicValue(f32 *value)
{
    {
        f32 wrappedValue;
        f32 limit;
        f32 step;

        wrappedValue = *value;
        limit = g_wrappedDifferenceAndApproachConstants[1];
        if (wrappedValue < limit) {
            step = g_boundedApproachStepConstants;
            do {
                wrappedValue += step;
                *value = wrappedValue;
            } while (wrappedValue < limit);
        }
    }
    {
        f32 wrappedValue;
        f32 limit;
        f32 step;

        wrappedValue = *value;
        limit = *(&g_boundedApproachStepConstants + 1);
        if (limit <= wrappedValue) {
            step = g_wrappedApproachStep;
            do {
                wrappedValue -= step;
                *value = wrappedValue;
            } while (limit <= wrappedValue);
        }
    }
}

void MultiplyQuaternions(void *productQuaternion, void *leftQuaternion, void *rightQuaternion) {
    f32 *out = (f32 *)productQuaternion;
    f32 *savedComponent = (f32 *)leftQuaternion;
    f32 *b = (f32 *)rightQuaternion;

    out[0] = ((b[3] * savedComponent[0]) - (b[2] * savedComponent[1]))
             + (b[1] * savedComponent[2]) + (b[0] * savedComponent[3]);
    out[1] = ((b[2] * savedComponent[0]) + (b[3] * savedComponent[1]))
             - (b[0] * savedComponent[2]) + (b[1] * savedComponent[3]);
    out[2] = (-b[1] * savedComponent[0]) + (b[0] * savedComponent[1])
             + (b[3] * savedComponent[2]) + (b[2] * savedComponent[3]);
    out[3] = ((-b[0] * savedComponent[0]) - (b[1] * savedComponent[1]))
             - (b[2] * savedComponent[2]) + (b[3] * savedComponent[3]);
}

void Graphu64_NormalizeQuaternion(f32 *rotation) {
    f32 mag;
    f32 scale;

    mag = Gu_Sqrtf((rotation[0] * rotation[0]) + (rotation[1] * rotation[1]) + (rotation[2] * rotation[2]) + (rotation[3] * rotation[3]));
    if (mag != 0.0f) {
        scale = g_planeProjectionNormalScale / mag;
        rotation[0] = rotation[0] * scale;
        rotation[1] = rotation[1] * scale;
        rotation[2] = rotation[2] * scale;
        rotation[3] = rotation[3] * scale;
    }
}

/* Builds a rotation matrix from a quaternion with zero translation and a unit homogeneous corner. */

void MatrixFromQuaternion(f32 *q, f32 *m)
{
  f32 x = q[0];
  f32 xx = x * x;
  f32 y = q[1];
  f32 yy = y * y;
  f32 z = q[2];
  f32 zz = z * z;
  f32 w = q[3];
  f32 ww = w * w;
  f32 x2 = x + x;
  f32 xy = x2 * y;
  f32 w2 = w + w;
  f32 wz = w2 * z;
  f32 xz = x2 * z;
  f32 wy = w2 * y;
  f32 yz = (y + y) * z;
  f32 r0 = ((ww + xx) - yy) - zz;
  f32 r1 = xy + wz;
  f32 r2 = xz - wy;
  f32 r4 = xy - wz;
  f32 r5 = ((ww - xx) + yy) - zz;
  f32 r6 = yz + (w2 * x);
  f32 r8 = xz + wy;
  f32 r9 = yz - (w2 * x);
  f32 r10 = ((ww - xx) - yy) + zz;
  m[3] = 0.0f;
  m[7] = 0.0f;
  m[11] = 0.0f;
  m[12] = 0.0f;
  m[13] = 0.0f;
  m[14] = 0.0f;
  m[15] = g_axisAngleMatrixHomogeneousScale;
  m[0] = r0;
  m[1] = r1;
  m[2] = r2;
  m[4] = r4;
  m[5] = r5;
  m[6] = r6;
  m[8] = r8;
  m[9] = r9;
  m[10] = r10;
}

/** Lerp a 4-component vector: out = a + t * (b - a). */
void Graphu64_InterpolateQuaternionComponents(CQuatern *cQuatern, f32 t, void *savedComponent, void *b) {
    CQuatern *left = savedComponent;
    CQuatern *right = b;

    cQuatern->x = left->x + (t * (right->x - left->x));
    cQuatern->y = left->y + (t * (right->y - left->y));
    cQuatern->z = left->z + (t * (right->z - left->z));
    cQuatern->w = left->w + (t * (right->w - left->w));
}

void Graphu64_ApproachQuaternion(CQuatern *rotation, CQuatern *target) {
    CQuatern result;
    f32 angle;
    f32 blend;
    f32 t;

    angle = Graphu64_ArcCos((rotation->x * target->x) + (rotation->y * target->y) + (rotation->z * target->z) + (rotation->w * target->w));
    if (angle != 0.0f) {
        t = 1.0f - ((angle - (((angle * 0.1388889f) + 1.7453293e-4f) * g_frameElapsedTime)) / angle);
        if ((1.0f < t) || !(t < 0.0f)) {
            blend = 1.0f;
            if (!(blend < t)) {
                blend = t;
            }
        } else {
            blend = 0.0f;
        }
        Graphu64_InterpolateQuaternionWithLinearFallback(&result, blend, rotation, target);
        *rotation = result;
    }
}

/* GRAPHU64_BUILDLOOKATMATRIX.CPP */

/* Random results keep 31 bits so they are never negative. */
#define RANDOM_VALUE_MASK 0x7FFFFFFF

/* Builds a look-at view matrix (ultralib guLookAtF) from an eye, a target and an up vector,
   substituting a fallback x component when the up vector is parallel to the view direction.
 */

/* Returns the normalised cross product of a path node's two edge vectors, cached in g_cachedSurfaceNormal for the last node seen, with a default up vector for a null node. */

static inline CVector3 *cross_edges(CVector3 *out, Node75 *node) {
    CVector3 a;
    CVector3 b;
    CollisionBuildVertex *p;
    CollisionBuildVertex *q;

    if (node == 0) {
        g_cachedCeilingCrossProduct.x = 0;
        g_cachedCeilingCrossProduct.z = 0;
        g_cachedCeilingCrossProduct.y = g_defaultCeilingNormalY;
    } else if ((int)node != g_cachedCeilingCrossProductNode) {
        p = node->cur;
        q = node->prev;
        a.x = (p)->x - (q)->x;
        p = node->cur;
        q = node->prev;
        a.y = (p)->ceiling - (q)->ceiling;
        p = node->cur;
        q = node->prev;
        a.z = (p)->z - (q)->z;
        p = node->next;
        q = node->cur;
        b.x = (p)->x - (q)->x;
        p = node->next;
        q = node->cur;
        b.y = (p)->ceiling - (q)->ceiling;
        p = node->next;
        q = node->cur;
        b.z = (p)->z - (q)->z;
        Graphu64_CrossVectors(&g_cachedCeilingCrossProduct, &b, &a);
    }
    g_cachedCeilingCrossProductNode = (int)node;
    *out = g_cachedCeilingCrossProduct;
    return out;
}

/** Perform the no-op callback. */
void Graphu64_ReturnWithoutWork(void) {
}

/** Store a fill pattern into two paired global words. */
void Graphu64_ResetRandomSeeds(void) {
    g_primaryRandomSeed = 0xE3F635E3;
    g_secondaryRandomSeed = 0xE3F635E3;
}

s32 Graphu64_NextRandom(void) {
    u32 seed;

    seed = (g_primaryRandomSeed * 0xA84A5B53) + 0x58348C2D;
    g_primaryRandomSeed = seed;
    return ((seed << 16) | (seed >> 16)) & RANDOM_VALUE_MASK;
}

s32 Graphu64_NextRandomValue(void) {
    u32 seed;

    seed = (g_secondaryRandomSeed * 0xA84A5B53) + 0x58348C2D;
    g_secondaryRandomSeed = seed;
    return ((seed << 16) | (seed >> 16)) & RANDOM_VALUE_MASK;
}

/** LCG PRNG step scaled into [0, range * g_randomFloatRangeScale) as a float. */
f32 Graphu64_RandomFloat(f32 range) {
    f64 value;
    s32 randomBits;
    u32 seed;

    seed = (g_primaryRandomSeed * 0xA84A5B53) + 0x58348C2D;
    randomBits = (s32)((seed >> 16) & 0x7FFF);
    value = (f64)randomBits;
    g_primaryRandomSeed = seed;
    if (randomBits < 0) {
        value = value + g_randomUnsignedFloatCorrection;
    }
    return (f32)value * range * g_randomFloatRangeScale;
}

f32 Graphu64_ArcCos(f32 cosineValue) {
    f32 tableCoordinate;
    f32 interpolatedAngle;
    f32 lowerSample;
    s32 sampleIndex;
    s32 negativeInput;

    negativeInput = 1;
    if (cosineValue < 0.0f) {
        tableCoordinate = cosineValue * g_arcCosNegativeInputScale;
    } else {
        tableCoordinate = cosineValue * g_arcCosPositiveInputScale;
        negativeInput = 0;
    }
    sampleIndex = (s32) tableCoordinate;
    if ((f32) sampleIndex < g_arcCosInterpolationLimit) {
        lowerSample = g_arcCosLowerSamples[sampleIndex];
        interpolatedAngle = lowerSample + ((tableCoordinate - (f32) sampleIndex) * (g_arcCosUpperSamples[sampleIndex] - lowerSample));
        if (negativeInput != 0) {
            return g_arcCosNegativeAngleBase - interpolatedAngle;
        }
        return interpolatedAngle;
    }
    if (negativeInput != 0) {
        tableCoordinate = g_arcCosEndpoint;
        return g_arcCosNegativeEndpointBase - tableCoordinate;
    }
    return g_arcCosEndpoint;
}

f32 Graphu64_IntegrateBoundedValue(f32 value, f32 velocity, f32 limit) {
    if (velocity < 0.0f) {
        if (value <= -limit) {
            return value;
        }
    }
    if (0.0f < velocity) {
        if (limit <= value) {
            return value;
        }
    }
    if ((value < 0.0f && 0.0f < velocity) ||
        (0.0f < value && velocity < 0.0f)) {
        velocity *= g_boundedIntegrationAndEaseConstants[0];
    }
    value += velocity * g_frameElapsedTime;
    if (velocity < 0.0f) {
        if (value < -limit) {
            value = -limit;
        }
    } else if (limit < value) {
        value = limit;
    }
    return value;
}

f32 Graphu64_DecayToZero(f32 value, f32 rate) {
    f32 zero;

    zero = 0.0f;
    if (zero < value) {
        value -= rate * g_frameElapsedTime;
        if (value < zero) {
            value = zero;
        }
    } else if (value < zero) {
        value += rate * g_frameElapsedTime;
        if (zero < value) {
            value = zero;
        }
    }
    return value;
}

f32 Graphu64_ApproachValue(f32 current, f32 target, f32 rate) {
    f32 value;
    value = current;
    if (value < target) {
        value += rate * g_frameElapsedTime;
        if (target < value) {
            value = target;
        }
    }
    else if (target < value) {
        value -= rate * g_frameElapsedTime;
        if (value < target) {
            value = target;
        }
    }
    return value;
}

void Graphu64_EaseValueToward(f32 *value, f32 target, f32 rate) {
    f32 current;
    f32 next;

    current = *value;
    next = (target - current) * rate * g_frameElapsedTime;
    if (rate == g_boundedIntegrationAndEaseConstants[1]) {
        *value = target;
    } else if (current < target) {
        *value += next;
        if (target < *value) {
            *value = target;
        }
    } else if (target < current) {
        *value += next;
        if (*value < target) {
            *value = target;
        }
    }
}

s32 Graphu64_IntegrateBoundedInteger(s32 value, s32 velocity, s32 limit)
{
  f32 velocityFloat;
  s32 nextValue;
  s32 directionalLimit;
  s32 exceedsLimit;
  directionalLimit = limit;
  velocityFloat = (f32) velocity;
  nextValue = value + ((s32) (velocityFloat * g_frameElapsedTime));
  if (velocityFloat < 0.0f)
  {
    directionalLimit = -directionalLimit;
    exceedsLimit = nextValue < directionalLimit;
  }
  else
  {
    exceedsLimit = directionalLimit < nextValue;
  }
  if (exceedsLimit != 0)
  {
    directionalLimit = directionalLimit;
    nextValue = directionalLimit;
  }
  if (directionalLimit)
  {
    return nextValue;
  }
  else
  {
    return nextValue;
  }
}

f32 Graphu64_NegateWrappedValue(f32 value)
{
  unsigned char lowerBoundIndex;
  f32 val;
  val = value;
  lowerBoundIndex = 0;
  if (val < g_wrappedValueLowerConstants[lowerBoundIndex])
  {
    do
    {
      val += g_wrappedValueLowerConstants[1];
    }
    while (val < g_wrappedValueLowerConstants[lowerBoundIndex]);
  }
  if (g_wrappedValueUpperConstants[lowerBoundIndex] < val)
  {
    do
    {
      val -= g_wrappedValueUpperConstants[1];
    }
    while (g_wrappedValueUpperConstants[lowerBoundIndex] < val);
  }
  return -val;
}

f32 Graphu64_GetNegatedWrappedDifference(f32 angleA, f32 angleB) {
    f32 difference;
    f32 wrappedB;

    wrappedB = angleB;
    if (wrappedB < g_wrappedAngleLowerConstants) {
        do {
            wrappedB += *(&g_wrappedAngleLowerConstants + 1);
        } while (wrappedB < g_wrappedAngleLowerConstants);
    }
    if (g_wrappedAngleUpperConstants < wrappedB) {
        do {
            wrappedB -= *(&g_wrappedAngleUpperConstants + 1);
        } while (g_wrappedAngleUpperConstants < wrappedB);
    }
    difference = angleA - wrappedB;
    if (difference < g_wrappedDifferenceLowerConstants) {
        do {
            difference += *(&g_wrappedDifferenceLowerConstants + 1);
        } while (difference < g_wrappedDifferenceLowerConstants);
    }
    if (g_wrappedDifferenceUpperConstants < difference) {
        do {
            difference -= *(&g_wrappedDifferenceUpperConstants + 1);
        } while (g_wrappedDifferenceUpperConstants < difference);
    }
    return -difference;
}

f32 Graphu64_RandomBetween(f32 shakeMin, f32 shakeMax) {
    f32 blend;
    u32 seed;
    s32 randomValue;

    seed = (g_primaryRandomSeed * 0xA84A5B53) + 0x58348C2D;
    randomValue = ((seed << 16) | (seed >> 16)) & RANDOM_VALUE_MASK;
    randomValue = randomValue % 10000;
    blend = (f32)randomValue * g_randomBlendScale;
    g_primaryRandomSeed = seed;
    return (blend * shakeMin) + ((g_randomBlendUnitScale - blend) * shakeMax);
}

s32 Graphu64_UpdateCountdown(f32 *countdown)
{
  f32 *expiredCountdown;
  float zeroCountdown;
  f32 *countdownPointer;
  f32 remaining;
  remaining = (*countdown) - g_frameElapsedTime;
  *countdown = remaining;
  countdownPointer = countdown;
  expiredCountdown = countdownPointer;
  zeroCountdown = 0.0f;
  if ((remaining <= 0.0f) == 0)
  {
    if (g_frameElapsedTime)
    {
      remaining = 0;
      return remaining;
    }
    else
    {
      remaining = 0;
      return remaining;
    }
  }
  *expiredCountdown = zeroCountdown;
  return 1;
}

/** Copy two 3-vectors, then derive an edge vector, its z-component twice, and a negated x. */
void Graphu64_InitializeEdge(GeometryEdge *geometryEdge, void *startPoint, void *endPoint) {
    CVector3 *a = startPoint;
    CVector3 *b = endPoint;
    f32 zdiff;

    geometryEdge->start = *a;
    geometryEdge->end = *b;
    geometryEdge->direction.x = b->x - a->x;
    geometryEdge->direction.y = b->y - a->y;
    zdiff = b->z - a->z;
    geometryEdge->normal.y = 0.0f;
    geometryEdge->normal.z = -geometryEdge->direction.x;
    geometryEdge->direction.z = zdiff;
    geometryEdge->normal.x = zdiff;
}

void Graphu64_NormalizeEdgeHorizontal(GeometryEdgeDirectionView *geometryEdge)
{
    f32 magSq;
    f32 mag;
    f32 zOut;

    magSq = (geometryEdge->directionX * geometryEdge->directionX) +
            (geometryEdge->directionZ * geometryEdge->directionZ);
    zOut = 0.0f;
    if (magSq != 0.0f) {
        mag = Gu_Sqrtf(magSq);
        magSq = *(f32 *)&g_horizontalEdgeNormalizeScale / mag;
        geometryEdge->unitDirectionX = geometryEdge->directionX * magSq;
        geometryEdge->unitDirectionY = geometryEdge->directionY * magSq;
        zOut = geometryEdge->directionZ * magSq;
    } else {
        geometryEdge->unitDirectionX = 0.0f;
        geometryEdge->unitDirectionY = 0.0f;
    }
    geometryEdge->unitDirectionZ = zOut;
}

void Graphu64_NormalizeEdgeDirection(GeometryEdgeDirectionView *geometryEdge)
{
    f32 magSq;
    f32 mag;
    f32 zOut;

    magSq = (geometryEdge->directionX * geometryEdge->directionX) +
            (geometryEdge->directionY * geometryEdge->directionY) +
            (geometryEdge->directionZ * geometryEdge->directionZ);
    zOut = 0.0f;
    if (magSq != 0.0f) {
        mag = Gu_Sqrtf(magSq);
        magSq = g_edgeDirectionNormalizeScale / mag;
        geometryEdge->unitDirectionX = geometryEdge->directionX * magSq;
        geometryEdge->unitDirectionY = geometryEdge->directionY * magSq;
        zOut = geometryEdge->directionZ * magSq;
    } else {
        geometryEdge->unitDirectionX = 0.0f;
        geometryEdge->unitDirectionY = 0.0f;
    }
    geometryEdge->unitDirectionZ = zOut;
}

s32 Graphu64_GetHorizontalIntersectionParameter(f32 *edgePlane, f32 *intersectingEdge, f32 *parameterOutput) {
    CVector3 delta;
    f32 directionDotNormal;
    s32 result;

    delta.x = intersectingEdge[0] - edgePlane[0];
    delta.z = intersectingEdge[2] - edgePlane[2];
    directionDotNormal = (intersectingEdge[6] * edgePlane[12]) + (intersectingEdge[8] * edgePlane[14]);
    result = 0;
    if (directionDotNormal != 0.0f) {
        result = 1;
        *parameterOutput = ((delta.x * edgePlane[12]) + (delta.z * edgePlane[14])) / -directionDotNormal;
    }
    return result;
}

/** Half-plane test: is pointPosition on the positive side of geometryEdge's normal? */
s32 Graphu64_IsPointOnPositiveEdgeSide(GeometryEdge *geometryEdge, void *pointPosition) {
    CVector3 *point = pointPosition;
    CVector3 normal;
    CVector3 delta;
    s32 result;

    normal = geometryEdge->normal;
    delta.x = point->x - geometryEdge->start.x;
    delta.z = point->z - geometryEdge->start.z;
    result = 0;
    if (!(((normal.x * delta.x) + (normal.z * delta.z)) <= 0.0f)) {
        result = 1;
    }
    return result;
}

void Graphu64_BuildLookAtMatrix(float mf[4][4], float xEye, float yEye, float zEye,
                   float xAt, float yAt, float zAt,
                   float xUp, float yUp, float zUp)
{
    float one, len, xLook, yLook, zLook, xRight, yRight, zRight;

    guMtxIdentF(mf);

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;

    len = g_lookAtNormalizeAndFallbackConstants / Gu_Sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    if (xRight == 0.0f && yRight == 0.0f && zRight == 0.0f) {
        xRight = (&g_lookAtNormalizeAndFallbackConstants)[1];
    }
    one = g_lookAtHomogeneousScale;
    len = one / Gu_Sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = one / Gu_Sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    mf[0][0] = xRight;
    mf[1][0] = yRight;
    mf[2][0] = zRight;
    mf[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);

    mf[0][1] = xUp;
    mf[1][1] = yUp;
    mf[2][1] = zUp;
    mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);

    mf[0][2] = xLook;
    mf[1][2] = yLook;
    mf[2][2] = zLook;
    mf[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);

    mf[0][3] = 0;
    mf[1][3] = 0;
    mf[2][3] = 0;
    mf[3][3] = one;
}

CVector3 *Graphu64_GetCachedSurfaceNormal(CVector3 *out, Node75 *node) {
    if (node == 0) {
        ((CVector3 *)&g_cachedSurfaceNormal)->x = 0;
        ((CVector3 *)&g_cachedSurfaceNormal)->z = 0;
        ((CVector3 *)&g_cachedSurfaceNormal)->y = g_cachedSurfaceDefaultNormalY;
    } else if ((int)node != g_cachedSurfaceNormalNode) {
        cross_edges((CVector3 *)&g_cachedSurfaceNormal, node);
        Graphu64_NormalizeVec3((CVector3 *)&g_cachedSurfaceNormal);
    }
    *out = *(CVector3 *)&g_cachedSurfaceNormal;
    g_cachedSurfaceNormalNode = (int)node;
    return out;
}

f32 Graphu64_GetTrianglePlaneHeight(Node75 *node, f32 x, f32 z) {
    CVector3 normal;
    CVector3 point;
    CVector3 a;
    CVector3 b;
    CollisionBuildVertex *p;
    CollisionBuildVertex *q;

    if (node == 0) {
        return 0.0f;
    }
    if ((int)node != g_cachedCeilingCrossProductNode) {
        p = node->cur;
        q = node->prev;
        a.x = (p)->x - (q)->x;
        p = node->cur;
        q = node->prev;
        a.y = (p)->ceiling - (q)->ceiling;
        p = node->cur;
        q = node->prev;
        a.z = (p)->z - (q)->z;
        p = node->next;
        q = node->cur;
        b.x = (p)->x - (q)->x;
        p = node->next;
        q = node->cur;
        b.y = (p)->ceiling - (q)->ceiling;
        p = node->next;
        q = node->cur;
        b.z = (p)->z - (q)->z;
        Graphu64_CrossVectors(&g_cachedCeilingCrossProduct, &b, &a);
    }
    normal = g_cachedCeilingCrossProduct;
    g_cachedCeilingCrossProductNode = (int)node;
    if (normal.y == 0.0f) {
        return (((CollisionBuildVertex *)node->prev)->ceiling +
                ((CollisionBuildVertex *)node->cur)->ceiling +
                ((CollisionBuildVertex *)node->next)->ceiling) * g_cachedSurfaceCeilingAverageScale;
    }
    p = node->prev;
    point.x = (p)->x;
    p = node->prev;
    point.y = (p)->ceiling;
    p = node->prev;
    point.z = (p)->z;
    return (((point.z - z) * normal.z) +
            ((point.x - x) * normal.x) + (point.y * normal.y)) /
           normal.y;
}

/* Keep this source unit's macros local to its body. */
#undef RANDOM_VALUE_MASK

/* GRAPHU64_INVERTAFFINEMATRIX_DATA.CPP */



/* DIRECTION_MATRIX_DEFAULT_UP_WORDS_DATA.CPP */

extern float g_directionMatrixDefaultUp[3];

/* GRAPHU64.CPP */



#if defined(VERSION_US_REV1)
/* Scale and clamp pair per element of a full 4x4 matrix packed to s15.16 fixed point. */
const float g_fullMatrixFixedConversionPairs[16][2] = {
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f,
};
#endif

#if defined(VERSION_US_REV1)
/* Scale and clamp pair per element of the 3x4 affine part of a matrix (rows 0-2 and translation, column 3 skipped). */
const float g_affineMatrixFixedConversionPairs[12][2] = {
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
};
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const float g_fullMatrixFixedConversionPairs[16][2] = {
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f,
};
#endif


#if defined(VERSION_EU)
const float g_affineMatrixFixedConversionPairs[12][2] = {
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
};
#endif

/* GRAPHU64_CONVERT_MATRIX_TO_FIXED_CONSTANT_WORDS3_DATA.CPP */

#if defined(VERSION_US)
const float g_affineMatrixFixedConversionPairs[12][2] = {
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
};
#endif

#if defined(VERSION_DE)
const float g_fullMatrixFixedConversionPairs[16][2] = {
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f,
};
#endif

#if defined(VERSION_DE)
const float g_affineMatrixFixedConversionPairs[12][2] = {
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
};
#endif

/* G_VECTORNORMALIZEUNITSCALE.CPP */

extern const float g_vectorNormalizeUnitScale;

/* GRAPHU64_PROJECTONTOCROSSNORMAL_DATA.CPP */



/* K_GRAPHU64ENCODEDWORDS.CPP */



/* GRAPHU64_IDENTITYMATRIX_DATA.CPP */



/* G_MATRIXFIXEDRANGELIMITS.CPP */



/* GRAPHU64_PROJECT_POINT_CONSTANT_WORDS_DATA.CPP */



/* GRAPHU64_BUILDTRANSLATIONMATRIX_DATA.CPP */



/* GRAPHU64_BUILD_SCALE_MATRIX_CONSTANT_WORDS_DATA.CPP */



/* GRAPHU64_BUILDAXISANGLEMATRIX_DATA.CPP */



/* GRAPHU64_MATRIXFROMEULERXYZ_DATA.CPP */



/* GRAPHU64_BUILDPLANEPROJECTIONMATRIX_DATA.CPP */



/* K_GRAPHU64NEARONEANDONEFLOATS_US_REV1.CPP */



/* GRAPHU64_COPYSCALEDMATRIX_DATA.CPP */



/* BUILDPITCHMATRIX_DATA.CPP */



/* BUILD_YAW_MATRIX_CONSTANT_WORDS_DATA.CPP */



/* BUILDROLLMATRIX_DATA.CPP */



/* GRAPHU64_COPY_SWAPPED_MATRIX_BASIS_CONSTANT_WORDS_DATA.CPP */



/* GRAPHU64_COPYSWAPPEDMATRIXCOORDINATES_DATA.CPP */



/* GRAPHU64_INTERPOLATE_WRAPPED_VALUE_CONSTANT_WORDS_DATA.CPP */



/* GRAPHU64_GETWRAPPEDDIFFERENCE_DATA.CPP */



/* GRAPHU64_NORMALIZEQUATERNION_DATA.CPP */



/* MATRIXFROMQUATERNION_DATA.CPP */



/* GRAPHU64_NEGATEWRAPPEDVALUE_DATA.CPP */











/* GRAPHU64_GETNEGATEDWRAPPEDDIFFERENCE_DATA.CPP */





/* GRAPHU64_NORMALIZEEDGEHORIZONTAL_DATA.CPP */



/* GRAPHU64_NORMALIZEEDGEDIRECTION_DATA.CPP */



/* GRAPHU64_BUILDLOOKATMATRIX_DATA.CPP */









/* GRAPHU64_GETCACHEDSURFACENORMAL_DATA.CPP */





/* G_ARCCOSINETABLE_DE.CPP */



/* G_ARCCOSENDPOINT.CPP */


/* GRAPHU64_CONVERTMATRIXTOFIXED_DATA.CPP */

#if defined(VERSION_EU_X)
const float g_affineMatrixFixedConversionPairs[12][2] = {
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
};
#endif

/* G_ARCCOSTABLE_EU_X.CPP */



/* G_PICKUPTRAILINGRODATAEUX.CPP */

#if defined(VERSION_EU_X)
extern void * k_enemyFragment[1];
#endif

/* GRAPHU64_PACKFIXEDMATRIX_DATA.CPP */

#if defined(VERSION_US)

#endif

/* STATINST_ADVANCERESOURCEKEY_DATA.CPP */


/* XPLUS_NEXTRANDOMINTEGER_DATA.CPP */

/* Retained data for this translation unit. */

const float g_invertAffineMatrixConstants[1] = {
    1.0f,
};

const float g_multiplyAffineMatricesConstants[1] = {
    1.0f,
};

const float g_projectOntoCrossNormalConstants[1] = {
    1.0f,
};

const float g_graphicsAngleConstants[3] = {
    -1.0f, 1.0f, 1.5707964f,
};

const float g_identityMatrixConstants[1] = {
    1.0f,
};

const float g_matrixFixedRangeLimits[2] = {
    32767.0f, -32767.0f,
};

const float g_projectPointConstants[1] = {
    1.0f,
};

const float g_buildTranslationMatrixConstants[1] = {
    1.0f,
};

const float g_buildScaleMatrixConstants[1] = {
    1.0f,
};

const float g_buildAxisAngleMatrixConstants[1] = {
    1.0f,
};

const float g_matrixFromEulerXYZConstants[1] = {
    1.0f,
};

const float g_buildPlaneProjectionMatrixConstants[1] = {
    1.0f,
};

const float k_nearUnitThresholdAndUnitFloats[4] = {
    0.999999f, 0.999999f, 1.0f, 1.0f,
};

const float g_copyScaledMatrixConstants[1] = {
    1.0f,
};

const float k_buildPitchMatrixUnit[1] = {
    1.0f,
};

const float g_buildYawMatrixConstants[1] = {
    1.0f,
};

const float k_buildRollMatrixUnit[1] = {
    1.0f,
};

const float g_copySwappedMatrixBasisConstants[1] = {
    1.0f,
};

const float g_copySwappedMatrixCoordinatesConstants[1] = {
    1.0f,
};

const float g_interpolateWrappedValueConstants[2] = {
    6.2831855f, 6.2831855f,
};

const float g_getWrappedDifferenceConstants[2] = {
    6.2831855f, 6.2831855f,
};

const float g_normalizeQuaternionConstants[1] = {
    1.0f,
};

const float k_matrixFromQuaternionUnit[1] = {
    1.0f,
};

const float g_wrappedValueScaleConstants[3] = {
    3.0e+01f, 0.0f, 3.051851e-05f,
};

const float g_arcCosConstants[5] = {
    -1023.0f, 1023.0f, 1023.0f, 3.1415927f, 3.1415927f,
};

const float g_integrateBoundedValueConstants[1] = {
    1.5f,
};

const float g_decayToZeroUnitConstant[1] = {
    1.0f,
};

const float g_graphuNegatewrappedvalueData[4] = {
    -3.1415927f, 6.2831855f, 3.1415927f, 6.2831855f,
};

const float g_graphuGetnegatedwrappeddifferenceData[8] = {
    -3.1415927f, 6.2831855f, 3.1415927f, 6.2831855f, -3.1415927f, 6.2831855f,
    3.1415927f, 6.2831855f,
};

const float g_randomBetweenConstants[2] = {
    0.00010001f, 1.0f,
};

const float g_normalizeEdgeHorizontalConstants[1] = {
    1.0f,
};

const float g_normalizeEdgeDirectionConstants[1] = {
    1.0f,
};

const float g_graphuBuildlookatmatrixData[3] = {
    -1.0f, 1.0f, 1.0f,
};

const float g_getCachedSurfaceNormalConstants[2] = {
    -1.0f, -1.0f,
};

const float g_getTrianglePlaneHeightConstants[1] = {
    0.33333334f,
};
#if defined(VERSION_US)
const float g_graphU_PackFixedMatrixConstantWords[32] = {
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f, 65536.0f, 2.1474836e+09f,
    65536.0f, 2.1474836e+09f,
};
#endif

const float g_vectorNormalizeUnitScale = 1.0f;
