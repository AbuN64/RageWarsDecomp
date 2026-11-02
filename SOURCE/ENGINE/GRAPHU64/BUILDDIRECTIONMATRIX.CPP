#include "include_asm.h"
#include "COMMON/MTX.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "COMMON/POOLED_FLOATS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/BALLISTICPARAMS.H"

/* Builds an orientation matrix whose third row is the given direction: the first row is the cross product of the up vector g_directionMatrixUnitConstants_us_rev1 with it, or the X axis when the direction is within the vertical thresholds, the second row is the cross product of the first row with it, all three rows are normalised and the rest is identity. */





extern CVector3 g_directionMatrixUnitConstants_de[2];


extern void Graphu64_CrossVectors(CVector3 *out, CVector3 *a, CVector3 *b);



/* Copies a 4x4 float matrix while scaling its first three rows by three per-row factors, zeroing their fourth column and setting the last element to the canonical unit constant. Adapted from CopyMatrix with the row scaling, the zeroed column and the constant corner changed. */

/* Expands a 4x4 transform into an affine 4x4 matrix with its second and third rows swapped, a zero last column and the pooled corner g_translationAndSwappedBasisUnitConstants[1]. */



/* Expands a 4x4 transform into an affine 4x4 matrix with its second and third columns swapped, a zero last column and the pooled corner g_swappedCoordinatesAndWrapConstants. Adapted from Graphu64_CopySwappedMatrixBasis with the row swap replaced by a column swap and the corner taken from g_swappedCoordinatesAndWrapConstants. */



extern f32 g_wrappedApproachStep;

extern f32 g_planeProjectionNormalScale;

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
    char *a0;
    char *a2;
    char *v1;
    s32 col;
    s32 row;
    s32 coloff;
    f32 last;

    destination[0] = source[0];
    destination[1] = source[1];
    destination[2] = source[2];
    destination[3] = source[3];
    destination[4] = source[4];
    destination[5] = source[5];
    destination[6] = source[6];
    destination[7] = source[7];
    destination[8] = source[8];
    destination[9] = source[9];
    destination[10] = source[10];
    destination[11] = source[11];
    destination[12] = source[12];
    destination[13] = source[13];
    destination[14] = source[14];
    last = source[15];
    col = 0;
    destination[15] = last;

    a0 = (char *)destination;
    do {
        row = 0;
        coloff = col * 4;
        a2 = a0;
        v1 = (char *)source;
        do {
            *(f32 *)a2 = *(f32 *)(coloff + (s32)v1);
            v1 += sizeof(CQuatern);
            row += 1;
            a2 += 4;
        } while (row < 3);
        col += 1;
        a0 += sizeof(CQuatern);
    } while (col < 3);
}

void Graphu64_BuildPlaneProjectionMatrix(void *projection, void *projectionDirection, f32 plane) {
    CVector3 *direction = projectionDirection;
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
    inverseVertical = unit / direction->y;
    slopeX = direction->x * inverseVertical;
    slopeZ = direction->z * inverseVertical;
    o->m[13] = plane;
    o->m[5] = zero;
    o->m[4] = -slopeX;
    o->m[6] = -slopeZ;
    o->m[12] = plane * slopeX;
    o->m[14] = plane * slopeZ;
}

void BuildDirectionMatrix(CMatrix4 *m, CVector3 *direction) {
    CVector3 up;
    CVector3 *upVector = (void *)&g_directionMatrixUnitConstants_de[0].y;

    up = *upVector;
    if (direction->y < 0.0f ? (&g_planeProjectionAndDirectionConstants)[1] <= -direction->y : g_directionVerticalThreshold.value <= direction->y) {
        m->right.y = 0;
        m->right.z = 0;
        m->right.x = g_directionFallbackAxisScale;
    } else {
        Graphu64_CrossVectors(&m->right, &up, direction);
    }
    Graphu64_CrossVectors(&m->up, &m->right, direction);
    m->forward = *direction;
    Graphu64_NormalizeVec3(&m->right);
    Graphu64_NormalizeVec3(&m->up);
    Graphu64_NormalizeVec3(&m->forward);
    m->m03 = m->m13 = m->m23 = m->m30 = m->m31 = m->m32 = 0.0f;
    m->m33 = g_directionMatrixHomogeneousScale;
}

/** Copy the three floating components at offset 0x30. */
void Graphu64_GetMatrixTranslation(char *object, float *output) {
    Matrix *matrix = (void *)object;
    output[0] = matrix->m[12];
    output[1] = matrix->m[13];
    output[2] = matrix->m[14];
}

void Graphu64_GetMatrixScale(void *matrix, f32 *scaleOutput) {
    Matrix *m = matrix;
    CVector3 tmp;

    tmp.x = m->m[0];
    tmp.y = m->m[1];
    tmp.z = m->m[2];
    scaleOutput[0] = Gu_Sqrtf((tmp.x * tmp.x) + (tmp.y * tmp.y) + (tmp.z * tmp.z));

    tmp.x = m->m[4];
    tmp.y = m->m[5];
    tmp.z = m->m[6];
    scaleOutput[1] = Gu_Sqrtf((tmp.x * tmp.x) + (tmp.y * tmp.y) + (tmp.z * tmp.z));

    tmp.x = m->m[8];
    tmp.y = m->m[9];
    tmp.z = m->m[10];
    scaleOutput[2] = Gu_Sqrtf((tmp.x * tmp.x) + (tmp.y * tmp.y) + (tmp.z * tmp.z));
}

void TranslateMatrixLocal(void *matrix, f32 tiltX, f32 lift, f32 translationZ) {
    Matrix *o = matrix;

    o->m[12] = o->m[12] + (tiltX * o->m[0] + lift * o->m[4] + translationZ * o->m[8]);
    o->m[13] = o->m[13] + (tiltX * o->m[1] + lift * o->m[5] + translationZ * o->m[9]);
    o->m[14] = o->m[14] + (tiltX * o->m[2] + lift * o->m[6] + translationZ * o->m[10]);
}

/** Add three floating arguments to the vector at offset 0x30. */
void TranslateMatrix(char *object, float x, float y, float z) {
    Matrix *matrix = (void *)object;
    matrix->m[12] += x;
    matrix->m[13] += y;
    matrix->m[14] += z;
}

/** Scale the first three rows of a matrix's basis columns by sx, sy, sz. */
void ScaleMatrixLocal(void *matrix, f32 sx, f32 sy, f32 sz) {
    Matrix *o = matrix;

    o->m[0] = o->m[0] * sx;
    o->m[1] = o->m[1] * sx;
    o->m[2] = o->m[2] * sx;
    o->m[4] = o->m[4] * sy;
    o->m[5] = o->m[5] * sy;
    o->m[6] = o->m[6] * sy;
    o->m[8] = o->m[8] * sz;
    o->m[9] = o->m[9] * sz;
    o->m[10] = o->m[10] * sz;
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
void Graphu64_ScaleMatrixWorld(void *matrix, f32 sx, f32 sy, f32 sz) {
    Matrix *o = matrix;

    o->m[0] = o->m[0] * sx;
    o->m[4] = o->m[4] * sx;
    o->m[8] = o->m[8] * sx;
    o->m[12] = o->m[12] * sx;
    o->m[1] = o->m[1] * sy;
    o->m[5] = o->m[5] * sy;
    o->m[9] = o->m[9] * sy;
    o->m[13] = o->m[13] * sy;
    o->m[2] = o->m[2] * sz;
    o->m[6] = o->m[6] * sz;
    o->m[10] = o->m[10] * sz;
    o->m[14] = o->m[14] * sz;
}

void BuildPitchMatrix(void *rest, f32 pitchAngle) {
    struct CMatrix4 *m = rest;
    f32 sin_v;
    f32 cos_v;
    f32 zero;
    f32 identity;

    sin_v = Gu_Sinf(pitchAngle);
    zero = 0;
    identity = g_pitchAndRollMatrixUnitConstants[0];
    m->forward.y = -sin_v;
    m->up.z = sin_v;
    m->right.y = zero;
    m->up.x = zero;
    m->right.z = zero;
    m->forward.x = zero;
    m->m32 = zero;
    m->m31 = zero;
    m->m30 = zero;
    m->m23 = zero;
    m->m13 = zero;
    m->m03 = zero;
    m->m33 = identity;
    m->right.x = identity;
    cos_v = Math_Cosf(pitchAngle);
    m->forward.z = cos_v;
    m->up.y = cos_v;
}

void BuildYawMatrix(void *matrixStorage, f32 yawAngle)
{
  struct CMatrix4 *m = (char *) matrixStorage;
  f32 sin_v;
  f32 cos_v;
  f32 zero;
  f32 identity;
  zero = 0;
  sin_v = Gu_Sinf(yawAngle);
  identity = g_pitchAndRollMatrixUnitConstants[1];
  m->forward.x = sin_v;
  m->right.y = zero;
  m->right.z = -sin_v;
  m->up.x = zero;
  m->up.z = zero;
  m->forward.y = zero;
  m->m32 = zero;
  m->m31 = zero;
  m->m30 = zero;
  m->m23 = zero;
  m->m13 = zero;
  m->m03 = zero;
  m->m33 = identity;
  m->up.y = identity;
  cos_v = Math_Cosf(yawAngle);
  m->forward.z = cos_v;
  m->right.x = cos_v;
}

void BuildRollMatrix(void *matrix, f32 rollAngle) {
    struct CMatrix4 *m = matrix;
    f32 sin_v;
    f32 cos_v;
    f32 zero;
    f32 one;

    sin_v = Gu_Sinf(rollAngle);
    zero = (f32) 0;
    one = g_translationAndSwappedBasisUnitConstants[0];
    m->right.z = zero;
    m->forward.x = zero;
    m->up.z = zero;
    m->forward.y = zero;
    m->m32 = zero;
    m->m31 = zero;
    m->m30 = zero;
    m->m23 = zero;
    m->m13 = zero;
    m->m03 = zero;
    m->forward.z = one;
    m->m33 = one;
    cos_v = Math_Cosf(rollAngle);
    m->up.y = cos_v;
    m->right.x = cos_v;
    m->up.x = -sin_v;
    m->right.y = sin_v;
}

void PitchMatrixLocal(void *matrixStorage, f32 pitchAngle) {
    struct CMatrix4 *m = (char *) matrixStorage;
    f32 sin_v;
    f32 cos_v;
    f32 neg_sin;
    f32 a;

    sin_v = Gu_Sinf(pitchAngle);
    cos_v = Math_Cosf(pitchAngle);
    neg_sin = -sin_v;

    a = m->up.x;
    m->up.x = (cos_v * a) + (sin_v * m->forward.x);
    m->forward.x = (neg_sin * a) + (cos_v * m->forward.x);

    a = m->up.y;
    m->up.y = (cos_v * a) + (sin_v * m->forward.y);
    m->forward.y = (neg_sin * a) + (cos_v * m->forward.y);

    a = m->up.z;
    m->up.z = (cos_v * a) + (sin_v * m->forward.z);
    m->forward.z = (neg_sin * a) + (cos_v * m->forward.z);
}

void PitchMatrix(void *matrixStorage, f32 pitchAngle) {
    struct CMatrix4 *m = (char *) matrixStorage;
    f32 sin_v;
    f32 cos_v;
    f32 neg_sin;
    f32 a;

    sin_v = Gu_Sinf(pitchAngle);
    cos_v = Math_Cosf(pitchAngle);
    neg_sin = -sin_v;

    a = m->right.y;
    m->right.y = (a * cos_v) + (m->right.z * neg_sin);
    m->right.z = (a * sin_v) + (m->right.z * cos_v);

    a = m->up.y;
    m->up.y = (a * cos_v) + (m->up.z * neg_sin);
    m->up.z = (a * sin_v) + (m->up.z * cos_v);

    a = m->forward.y;
    m->forward.y = (a * cos_v) + (m->forward.z * neg_sin);
    m->forward.z = (a * sin_v) + (m->forward.z * cos_v);

    a = m->m31;
    m->m31 = (a * cos_v) + (m->m32 * neg_sin);
    m->m32 = (a * sin_v) + (m->m32 * cos_v);
}

void YawMatrixLocal(void *matrix, f32 yawAngle) {
    struct CMatrix4 *m = (char *) matrix;
    f32 sin_v;
    f32 cos_v;
    f32 neg_sin;
    f32 a;

    sin_v = Gu_Sinf(yawAngle);
    cos_v = Math_Cosf(yawAngle);
    neg_sin = -sin_v;

    a = m->right.x;
    m->right.x = (cos_v * a) + (neg_sin * m->forward.x);
    m->forward.x = (sin_v * a) + (cos_v * m->forward.x);

    a = m->right.y;
    m->right.y = (cos_v * a) + (neg_sin * m->forward.y);
    m->forward.y = (sin_v * a) + (cos_v * m->forward.y);

    a = m->right.z;
    m->right.z = (cos_v * a) + (neg_sin * m->forward.z);
    m->forward.z = (sin_v * a) + (cos_v * m->forward.z);
}

void YawMatrix(void *matrix, f32 yawAngle) {
    struct CMatrix4 *m = (char *) matrix;
    f32 sin_v;
    f32 cos_v;
    f32 neg_sin;
    f32 a;

    sin_v = Gu_Sinf(yawAngle);
    cos_v = Math_Cosf(yawAngle);
    neg_sin = -sin_v;

    a = m->right.x;
    m->right.x = (a * cos_v) + (m->right.z * sin_v);
    m->right.z = (a * neg_sin) + (m->right.z * cos_v);

    a = m->up.x;
    m->up.x = (a * cos_v) + (m->up.z * sin_v);
    m->up.z = (a * neg_sin) + (m->up.z * cos_v);

    a = m->forward.x;
    m->forward.x = (a * cos_v) + (m->forward.z * sin_v);
    m->forward.z = (a * neg_sin) + (m->forward.z * cos_v);

    a = m->m30;
    m->m30 = (a * cos_v) + (m->m32 * sin_v);
    m->m32 = (a * neg_sin) + (m->m32 * cos_v);
}

void RollMatrixLocal(void *matrix, f32 rollAngle) {
    struct CMatrix4 *m = (char *) matrix;
    f32 sin_v;
    f32 cos_v;
    f32 neg_sin;
    f32 a;

    sin_v = Gu_Sinf(rollAngle);
    cos_v = Math_Cosf(rollAngle);
    neg_sin = -sin_v;

    a = m->right.x;
    m->right.x = (cos_v * a) + (sin_v * m->up.x);
    m->up.x = (neg_sin * a) + (cos_v * m->up.x);

    a = m->right.y;
    m->right.y = (cos_v * a) + (sin_v * m->up.y);
    m->up.y = (neg_sin * a) + (cos_v * m->up.y);

    a = m->right.z;
    m->right.z = (cos_v * a) + (sin_v * m->up.z);
    m->up.z = (neg_sin * a) + (cos_v * m->up.z);
}

void RollMatrix(void *matrixStorage, f32 rollAngle) {
    struct CMatrix4 *m = (char *) matrixStorage;
    f32 sin_v;
    f32 cos_v;
    f32 neg_sin;
    f32 a;

    sin_v = Gu_Sinf(rollAngle);
    cos_v = Math_Cosf(rollAngle);
    neg_sin = -sin_v;

    a = m->right.x;
    m->right.x = (a * cos_v) + (m->right.y * neg_sin);
    m->right.y = (a * sin_v) + (m->right.y * cos_v);

    a = m->up.x;
    m->up.x = (a * cos_v) + (m->up.y * neg_sin);
    m->up.y = (a * sin_v) + (m->up.y * cos_v);

    a = m->forward.x;
    m->forward.x = (a * cos_v) + (m->forward.y * neg_sin);
    m->forward.y = (a * sin_v) + (m->forward.y * cos_v);

    a = m->m30;
    m->m30 = (a * cos_v) + (m->m31 * neg_sin);
    m->m31 = (a * sin_v) + (m->m31 * cos_v);
}

/** Swap the two float-groups at offsets 0x10 and 0x20 (three floats each). */
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
        f32 val;
        f32 limit;
        f32 step;

        val = *value;
        limit = g_wrappedDifferenceAndApproachConstants[1];
        if (val < limit) {
            step = g_boundedApproachStepConstants;
            do {
                val += step;
                *value = val;
            } while (val < limit);
        }
    }
    {
        f32 val;
        f32 limit;
        f32 step;

        val = *value;
        limit = *(&g_boundedApproachStepConstants + 1);
        if (limit <= val) {
            step = g_wrappedApproachStep;
            do {
                val -= step;
                *value = val;
            } while (limit <= val);
        }
    }
}

void MultiplyQuaternions(void *productQuaternion, void *leftQuaternion, void *rightQuaternion) {
    f32 *out = (f32 *)productQuaternion;
    f32 *a = (f32 *)leftQuaternion;
    f32 *b = (f32 *)rightQuaternion;

    out[0] = ((b[3] * a[0]) - (b[2] * a[1]))
             + (b[1] * a[2]) + (b[0] * a[3]);
    out[1] = ((b[2] * a[0]) + (b[3] * a[1]))
             - (b[0] * a[2]) + (b[1] * a[3]);
    out[2] = (-b[1] * a[0]) + (b[0] * a[1])
             + (b[3] * a[2]) + (b[2] * a[3]);
    out[3] = ((-b[0] * a[0]) - (b[1] * a[1]))
             - (b[2] * a[2]) + (b[3] * a[3]);
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
void Graphu64_InterpolateQuaternionComponents(void *cQuatern, f32 t, void *a, void *b) {
    CQuatern *out = cQuatern;
    CQuatern *left = a;
    CQuatern *right = b;

    out->x = left->x + (t * (right->x - left->x));
    out->y = left->y + (t * (right->y - left->y));
    out->z = left->z + (t * (right->z - left->z));
    out->w = left->w + (t * (right->w - left->w));
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
