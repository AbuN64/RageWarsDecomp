#include "include_asm.h"
#include "COMMON/GRAPHICS_MATRIX_AND_VECTOR_MATH.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"

#include "COMMON/MATH_HELPERS.H"
extern f32 Gu_Sqrtf(f32);
/** Heading of a direction in the XZ plane: acos of the dominant axis, clamped to [-1, 1]. */
f32 Graphu64_GetHorizontalAngle(CVector3 *direction) {
    f32 x = direction->x;
    f32 z = direction->z;
    f32 length = x * x + z * z;
    f32 angle;
    f32 a;
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
        a = Graphu64_ArcCos(x);
        angle = -a;
        if (z < 0.0f) {
            angle = a;
        }
        angle -= 1.5707964f;
    } else {
        z /= length;
        z = RW_MAX_GT(-1.0f, RW_MIN(z, 1.0f));
        a = Graphu64_ArcCos(-z);
        angle = -a;
        if (x < 0.0f) {
            angle = a;
        }
    }
    return angle;
}


extern const float g_vectorNormalizeUnitScale;

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
#define ANGLE_ABS(a) (-(a) < 0.0f ? (a) : -(a))
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
void Graphu64_ScaleVector(void *scaledVector, void *inputVector, f32 scaleFactor) {
    ((CVector3 *)(scaledVector))->x = ((CVector3 *)(inputVector))->x * scaleFactor;
    ((CVector3 *)(scaledVector))->y = ((CVector3 *)(inputVector))->y * scaleFactor;
    ((CVector3 *)(scaledVector))->z = ((CVector3 *)(inputVector))->z * scaleFactor;
}

/** Lerp a 3-component vector: out = a + t * (b - a). */
void Graphu64_InterpolateVector(CVector3 *result, f32 t, void *a, void *b) {
    result->x = ((CVector3 *)(a))->x + (t * (((CVector3 *)(b))->x - ((CVector3 *)(a))->x));
    result->y = ((CVector3 *)(a))->y + (t * (((CVector3 *)(b))->y - ((CVector3 *)(a))->y));
    result->z = ((CVector3 *)(a))->z + (t * (((CVector3 *)(b))->z - ((CVector3 *)(a))->z));
}

/** Cross product of two vectors, written directly to the output (no aliasing guard). */
void Graphu64_CrossVectors(CVector3 *out, CVector3 *a, CVector3 *b) {
    out->x = (a->y * b->z) - (a->z * b->y);
    out->y = (a->z * b->x) - (a->x * b->z);
    out->z = (a->x * b->y) - (a->y * b->x);
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
void Graphu64_InterpolateAtHeight(CVector3 *out, CVector3 *a, CVector3 *b, f32 y) {
    f32 dy = b->y - a->y;

    if (dy == 0.0f) {
        *out = *a;
        return;
    }

    {
        f32 t = (y - a->y) / dy;
        out->x = a->x + (t * (b->x - a->x));
        out->y = y;
        out->z = a->z + (t * (b->z - a->z));
    }
}

void *Graphu64_ReflectVector(CVector3 *result, CVector3 *remaining, CVector3 *planeNormal, f32 restitution) {
    CVector3 tmp;
    f32 normalScale;
    f32 normalDot;
    f32 normalX;
    f32 inputX;

    inputX = remaining->x;
    normalX = planeNormal->x;
    normalDot = (inputX * normalX) + (remaining->y * planeNormal->y) + (remaining->z * planeNormal->z);
    normalScale = (restitution * normalDot) + normalDot;
    tmp.x = inputX - (normalScale * normalX);
    tmp.y = remaining->y - (normalScale * planeNormal->y);
    tmp.z = remaining->z - (normalScale * planeNormal->z);
    *result = tmp;
    return result;
}

void *Graphu64_ProjectVectorOntoPlane(CVector3 *result, CVector3 *remaining, CVector3 *planeNormal) {
    CVector3 tmp;
    f32 normalDot;
    f32 normalX;
    f32 inputX;

    inputX = remaining->x;
    normalX = planeNormal->x;
    normalDot = (inputX * normalX) + (remaining->y * planeNormal->y) + (remaining->z * planeNormal->z);
    tmp.x = inputX - (normalDot * normalX);
    tmp.y = remaining->y - (normalDot * planeNormal->y);
    tmp.z = remaining->z - (normalDot * planeNormal->z);
    *result = tmp;
    return result;
}
