#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "TYPES.H"
#include "UI/X_FILES/X_MATH.H"
#include "RESMGR/resmgr_string_memory.H"

/* Clips a polygon of n vertices against the plane a*x + b*y + c*z + d >= 0 (Sutherland-Hodgman): walks each edge from the previous vertex, copies inside vertices to the output, and where an edge crosses the plane emits the intersection point (the edge midpoint when the edge is nearly parallel to the plane), storing the output count and returning whether any intersection was emitted. */



s32 XMath_ClipPolygonToPlane(CVector3 *out, s32 *outCount, CVector3 *in, s32 n, f32 a, f32 b, f32 c, f32 d) {
    CVector3 delta;
    CVector3 *prev;
    CVector3 *point;
    CVector3 *cur;
    s32 count;
    s32 clipped;
    s32 i;
    s32 prevInside;
    s32 inside;
    f32 dot;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 t;

    count = 0;
    clipped = 0;
    *outCount = 0;
    if (n == 0) {
        return 0;
    }
    prev = &in[n - 1];
    prevInside = prev->x * a + prev->y * b + prev->z * c + d >= 0.0f;
    for (i = 0; i < n; i++) {
        cur = &in[i];
        inside = cur->x * a + cur->y * b + cur->z * c + d >= 0.0f;
        if (prevInside) {
            *out++ = *prev;
            count++;
        }
        if (prevInside != inside) {
            dx = cur->x - prev->x;
            delta.x = dx;
            dx = a * delta.x;
            dy = cur->y - prev->y;
            delta.y = dy;
            dy = b * delta.y;
            dz = cur->z - prev->z;
            delta.z = dz;
            dz = c * delta.z;
            dot = dx + dy + dz;
            dist = a * prev->x + b * prev->y + c * prev->z + d;
            clipped = 1;
            point = out++;
            count++;
            dist = -dist;
            if (dot < 0.001f && (t = 0.5f, -0.001f < dot)) {
            } else {
                t = dist / dot;
            }
            point->x = prev->x + t * delta.x;
            point->y = prev->y + t * delta.y;
            point->z = prev->z + t * delta.z;
        }
        prev = cur;
        prevInside = inside;
    }
    *outCount = count;
    return clipped;
}

#include "COMMON/ITEMRECAT20V1.H"
extern float k_xmathFirstAngleMatrixUnit, k_xmathSecondAngleMatrixUnit, k_xmathThirdAngleMatrixUnit, k_xmathFourthAngleMatrixUnit, k_xmathAnglesMatrixHomogeneousUnit;

void MatrixFromAngles(MatrixF *matrix, f32 *angles) {
    u16 mask = 0;
    f32 sy, cy, sx, cx, sz, cz, one;
    if (angles[0] != 0.0f) mask = 4;
    if (angles[1] != 0.0f) mask |= 2;
    if (angles[2] != 0.0f) mask |= 1;
    switch (mask) {
    case 0:
        XPlus_FillBytes(matrix, 0, 64);
        one = k_xmathFirstAngleMatrixUnit;
        matrix->m[0][0] = one; matrix->m[1][1] = one; matrix->m[2][2] = one; matrix->m[3][3] = one;
        return;
    case 2:
        XPlus_FillBytes(matrix, 0, 64);
        one = k_xmathSecondAngleMatrixUnit;
        matrix->m[0][0] = one; matrix->m[1][1] = one; matrix->m[2][2] = one; matrix->m[3][3] = one;
        XMath_EvaluateSineCosine(angles[1], &sy, &cy);
        matrix->m[2][0] = sy; matrix->m[0][0] = cy; matrix->m[0][2] = -sy; matrix->m[2][2] = cy;
        return;
    case 4:
        XPlus_FillBytes(matrix, 0, 64);
        one = k_xmathThirdAngleMatrixUnit;
        matrix->m[0][0] = one; matrix->m[1][1] = one; matrix->m[2][2] = one; matrix->m[3][3] = one;
        XMath_EvaluateSineCosine(angles[0], &sx, &cx);
        matrix->m[1][1] = cx; matrix->m[2][1] = -sx; matrix->m[1][2] = sx; matrix->m[2][2] = cx;
        return;
    case 1:
        XPlus_FillBytes(matrix, 0, 64);
        one = k_xmathFourthAngleMatrixUnit;
        matrix->m[0][0] = one; matrix->m[1][1] = one; matrix->m[2][2] = one; matrix->m[3][3] = one;
        XMath_EvaluateSineCosine(angles[2], &sz, &cz);
        matrix->m[0][0] = cz; matrix->m[1][0] = -sz; matrix->m[0][1] = sz; matrix->m[1][1] = cz;
        return;
    }
    XMath_EvaluateSineCosine(angles[0], &sx, &cx);
    XMath_EvaluateSineCosine(angles[1], &sy, &cy);
    XMath_EvaluateSineCosine(angles[2], &sz, &cz);
    {
        f32 sxsy = sx * sy;
        f32 cxcz = cx * cz;
        f32 cxsz = cx * sz;
        matrix->m[0][0] = cy * cz;
        matrix->m[1][0] = sxsy * cz - cxsz;
        matrix->m[2][0] = cxcz * sy + sx * sz;
        matrix->m[0][1] = cy * sz;
        matrix->m[1][1] = sxsy * sz + cxcz;
        matrix->m[2][1] = cxsz * sy - sx * cz;
        matrix->m[0][2] = -sy;
        matrix->m[1][2] = sx * cy;
        matrix->m[2][2] = cx * cy;
        matrix->m[0][3] = matrix->m[1][3] = matrix->m[2][3] = matrix->m[3][0] = matrix->m[3][1] = matrix->m[3][2] = 0.0f;
        matrix->m[3][3] = k_xmathAnglesMatrixHomogeneousUnit;
    }
}
