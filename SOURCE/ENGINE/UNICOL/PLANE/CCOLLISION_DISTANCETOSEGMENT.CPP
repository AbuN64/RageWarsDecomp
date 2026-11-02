#include "include_asm.h"
#include "TYPES.H"
#include "ENGINE/UNICOL/PLANE.H"
#include "COMMON/MEASURED_STORAGE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OUTPUT.H"
#include "ANIM/RAY180.H"
#include <ultra64.h>

extern f32 Gu_Sqrtf(f32);

/* Returns the distance from point p to the segment from a to b: the offset of p from a is reduced by
 * its projection onto the segment direction, clamped to the segment ends, before taking the length. */





extern void Graphu64_ScaleVector(CVector3 *, CVector3 *, f32);

f32 CCollision_DistanceToSegment(CVector3 *a, CVector3 *b, CVector3 *p) {
    extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
    CVector3 offset;
    CVector3 dir;
    f32 value;
    f32 len;

    Graphu64_SubtractVectors(&offset, p, a);
    Graphu64_SubtractVectors(&dir, b, a);
    value = dir.x * offset.x + dir.y * offset.y + dir.z * offset.z;
    if (!(value < 0.0f)) {
        len = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
        if (!(len <= value)) {
            Graphu64_ScaleVector(&dir, &dir, value / len);
        }
        Graphu64_SubtractVectors(&offset, &offset, &dir);
    }
    value = offset.x * offset.x + offset.y * offset.y + offset.z * offset.z;
    return Gu_Sqrtf(value);
}

