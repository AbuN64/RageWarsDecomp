#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "COMMON/ENTRYRECAT8V4.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* Computes the second derivatives of a natural cubic spline through n points (ys over xs) into out: builds the tridiagonal diagonal, interval widths and right-hand side in three scratch arrays from Cache_AllocateMemory, eliminates forward, zeroes out and back-substitutes unless a zero diagonal or width was replaced by one, then frees the arrays through Cache_FreeMemory. */

extern struct Record *Cache_AllocateMemory(s32 size);


extern void Graphu64_SubtractVectors(CVector3 *out, CVector3 *a, CVector3 *b);


extern void Track_SolveSplineSecondDerivatives(s32 n, f32 *ys, f32 *xs, f32 *out);

void Track_SolveSplineSecondDerivatives(s32 n, f32 *ys, f32 *xs, f32 *out) {
    f32 *diagonal;
    f32 *rhs;
    f32 *width;
    s32 singular;
    s32 i;

    singular = 0;
    if (n == 1) {
        out[0] = 0;
        return;
    }
    diagonal = Cache_AllocateMemory(n * 4);
    rhs = Cache_AllocateMemory(n * 4);
    width = Cache_AllocateMemory(n * 4);
    for (i = 1; i < n - 1; i++) {
        diagonal[i] = 2.0f * (xs[i + 1] - xs[i - 1]);
        if (diagonal[i] == 0.0f) {
            diagonal[i] = 1.0f;
            singular = 1;
        }
    }
    for (i = 0; i < n - 1; i++) {
        width[i] = xs[i + 1] - xs[i];
        if (width[i] == 0.0f) {
            width[i] = 1.0f;
            singular = 1;
        }
    }
    for (i = 1; i < n - 1; i++) {
        rhs[i] = ((ys[i + 1] - ys[i]) / width[i] - (ys[i] - ys[i - 1]) / width[i - 1]) * 6.0f;
    }
    for (i = 1; i < n - 2; i++) {
        rhs[i + 1] -= rhs[i] * width[i] / diagonal[i];
        diagonal[i + 1] -= width[i] * width[i] / diagonal[i];
    }
    for (i = 0; i < n; i++) {
        out[i] = 0;
    }
    if (!singular) {
        for (i = n - 2; i > 0; i--) {
            out[i] = (rhs[i] - width[i] * out[i + 1]) / diagonal[i];
        }
    }
    Cache_FreeMemory(diagonal);
    Cache_FreeMemory(rhs);
    Cache_FreeMemory(width);
}

void Track_BuildWeightedSpline(s32 count, CVector3 *points, f32 *weights, Spline *spline) {
    CVector3 delta;
    f32 *ys;
    f32 *xs;
    f32 *d2;
    SplineNode *nodes;
    f32 length;
    s32 i;

    ys = Cache_AllocateMemory(count * 4);
    xs = Cache_AllocateMemory(count * 4);
    d2 = Cache_AllocateMemory(count * 4);
    nodes = spline->nodes;
    length = 0.0f;
    spline->nodeSize = 36;
    spline->count = count;
    if (count == 1) {
        spline->nodes[0].p.x = points->x;
        nodes->p.y = points->y;
        nodes->p.z = points->z;
        nodes->d2p.x = 0.0f;
        nodes->d2p.y = 0.0f;
        nodes->d2p.z = 0.0f;
        nodes->d2s = 0.0f;
        nodes->w = 0.0f;
        return;
    }
    for (i = 0; i < count; i++) {
        nodes[i].p.x = points[i].x;
        nodes[i].p.y = points[i].y;
        nodes[i].p.z = points[i].z;
        nodes[i].w = weights[i];
    }
    for (i = 0; i < count; i++) {
        nodes[i].s = length;
        if (i == count - 1) {
            break;
        }
        Graphu64_SubtractVectors(&delta, &nodes[i].p, &nodes[i + 1].p);
        length += Gu_Sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    }
    for (i = 0; i < count; i++) {
        ys[i] = nodes[i].p.x;
        xs[i] = nodes[i].s;
    }
    Track_SolveSplineSecondDerivatives(count, ys, xs, d2);
    for (i = 0; i < count; i++) {
        nodes[i].d2p.x = d2[i];
    }
    for (i = 0; i < count; i++) {
        ys[i] = nodes[i].p.y;
        xs[i] = nodes[i].s;
    }
    Track_SolveSplineSecondDerivatives(count, ys, xs, d2);
    for (i = 0; i < count; i++) {
        nodes[i].d2p.y = d2[i];
    }
    for (i = 0; i < count; i++) {
        ys[i] = nodes[i].p.z;
        xs[i] = nodes[i].s;
    }
    Track_SolveSplineSecondDerivatives(count, ys, xs, d2);
    for (i = 0; i < count; i++) {
        nodes[i].d2p.z = d2[i];
    }
    for (i = 0; i < count; i++) {
        ys[i] = nodes[i].s;
        xs[i] = nodes[i].w;
    }
    Track_SolveSplineSecondDerivatives(count, ys, xs, d2);
    for (i = 0; i < count; i++) {
        nodes[i].d2s = d2[i];
    }
    Cache_FreeMemory(ys);
    Cache_FreeMemory(xs);
    Cache_FreeMemory(d2);
}
