#include "COMMON/GRAPHICS_MATRIX_AND_VECTOR_MATH.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "COMMON/POOLED_FLOATS.H"

extern f32 Gu_Sqrtf(f32);

static __inline__ CVector3 project(CVector3 *vector, CVector3 *planeNormal) {
    CVector3 projected;
    f32 dot;

    dot = (vector->x * planeNormal->x) + (vector->y * planeNormal->y) + (vector->z * planeNormal->z);
    projected.x = vector->x - (dot * planeNormal->x);
    projected.y = vector->y - (dot * planeNormal->y);
    projected.z = vector->z - (dot * planeNormal->z);
    return projected;
}

extern f32 Gu_Sqrtf(f32 value);

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
    f32 magnitude_squared;
    f32 ratio;

    y = delta[1];
    zero = 0.0f;
    x = delta[0];
    z = delta[2];
    if (y == zero) {
        return zero;
    }
    magnitude_squared = (x * x) + (y * y) + (z * z);
    if (magnitude_squared == zero) {
        return zero;
    }
    ratio = y / Gu_Sqrtf(magnitude_squared);
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
void Graphu64_IdentityMatrix(void *matrixStorage) {
    Matrix *matrix = matrixStorage;
    f32 zero = 0.0f;

    matrix->m[15] = g_identityAndFixedMatrixConstants;
    matrix->m[10] = g_identityAndFixedMatrixConstants;
    matrix->m[5] = g_identityAndFixedMatrixConstants;
    matrix->m[0] = g_identityAndFixedMatrixConstants;
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

void Graphu64_TransformPoint(void *matrix, void *inputPoint, void *transformedPoint) {
    Matrix *m = matrix;
    CVector3 *v = inputPoint;
    CVector3 *out = transformedPoint;

    out->x = (m->m[0] * v->x)
           + (m->m[4] * v->y)
           + (m->m[8] * v->z)
           + m->m[12];
    out->y = (m->m[1] * v->x)
           + (m->m[5] * v->y)
           + (m->m[9] * v->z)
           + m->m[13];
    out->z = (m->m[2] * v->x)
           + (m->m[6] * v->y)
           + (m->m[10] * v->z)
           + m->m[14];
}

/* Transforms a count of points by the affine part of a 4x4 matrix, writing each transformed point to an output array. Adapted from XMath_TransformPointArray with the input and output arguments swapped and the indexed loop replaced by a loop counting down an unsigned count while advancing an input and an output pointer. */
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

void Graphu64_ProjectPoint(void *matrix, void *inputPoint, CVector3 *localDirection) {
    Matrix *m = matrix;
    CVector3 *v = inputPoint;
    f32 w;
    f32 scale;

    localDirection->x = (m->m[0] * v->x)
                       + (m->m[4] * v->y)
                       + (m->m[8] * v->z)
                       + m->m[12];
    localDirection->y = (m->m[1] * v->x)
                       + (m->m[5] * v->y)
                       + (m->m[9] * v->z)
                       + m->m[13];
    localDirection->z = (m->m[2] * v->x)
                       + (m->m[6] * v->y)
                       + (m->m[10] * v->z)
                       + m->m[14];
    w = (m->m[3] * v->x)
        + (m->m[7] * v->y)
        + (m->m[11] * v->z)
        + m->m[15];
    if (w != 0.0f) {
        scale = *(&g_matrixClampAndProjectionConstants + 1) / w;
        localDirection->x = localDirection->x * scale;
        localDirection->y = localDirection->y * scale;
        localDirection->z = localDirection->z * scale;
    }
}

void Graphu64_TransformDirection(void *matrix, void *inputDirection, void *transformedDirection) {
    Matrix *m = matrix;
    CVector3 *v = inputDirection;
    CVector3 *out = transformedDirection;

    out->x = (m->m[0] * v->x)
                       + (m->m[4] * v->y)
                       + (m->m[8] * v->z);
    out->y = (m->m[1] * v->x)
                       + (m->m[5] * v->y)
                       + (m->m[9] * v->z);
    out->z = (m->m[2] * v->x)
                       + (m->m[6] * v->y)
                       + (m->m[10] * v->z);
}

void Graphu64_TransformDirectionTranspose(void *matrix, void *inputDirection, void *outputDirection) {
    Matrix *m = matrix;
    CVector3 *v = inputDirection;
    CVector3 *out = outputDirection;

    out->x = (m->m[0] * v->x)
                       + (m->m[1] * v->y)
                       + (m->m[2] * v->z);
    out->y = (m->m[4] * v->x)
                       + (m->m[5] * v->y)
                       + (m->m[6] * v->z);
    out->z = (m->m[8] * v->x)
                       + (m->m[9] * v->y)
                       + (m->m[10] * v->z);
}

void Graphu64_BuildTranslationMatrix(void *matrix, f32 translationX, f32 translationY, f32 translationZ) {
    Matrix *o = matrix;
    f32 val = g_translationAndScaleMatrixUnitConstants;
    f32 zero = 0.0f;

    o->m[12] = translationX;
    o->m[13] = translationY;
    o->m[14] = translationZ;
    o->m[15] = val;
    o->m[10] = val;
    o->m[5] = val;
    o->m[0] = val;
    o->m[11] = zero;
    o->m[9] = zero;
    o->m[8] = zero;
    o->m[7] = zero;
    o->m[6] = zero;
    o->m[4] = zero;
    o->m[3] = zero;
    o->m[2] = zero;
    o->m[1] = zero;
}

void Graphu64_BuildScaleMatrix(void *matrix, f32 scaleX, f32 scaleY, f32 scaleZ) {
    Matrix *o = matrix;
    f32 val = *(&g_translationAndScaleMatrixUnitConstants + 1);
    f32 zero = 0.0f;

    o->m[0] = scaleX;
    o->m[5] = scaleY;
    o->m[10] = scaleZ;
    o->m[15] = val;
    o->m[14] = zero;
    o->m[13] = zero;
    o->m[12] = zero;
    o->m[11] = zero;
    o->m[9] = zero;
    o->m[8] = zero;
    o->m[7] = zero;
    o->m[6] = zero;
    o->m[4] = zero;
    o->m[3] = zero;
    o->m[2] = zero;
    o->m[1] = zero;
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
