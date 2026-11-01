#include "TYPES.H"
#include "ENGINE/UNICOL/PLANE.H"
#include "COMMON/MEASURED_STORAGE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OUTPUT.H"
#include "ANIM/RAY180.H"
#include <ultra64.h>
#include "COMMON/BALLISTICPARAMS.H"

/* 80241170_2.CPP */
s32 Graphu64_InterpolateVector(CVector3 *, u32, void *, void *);

/* Tests a point against every edge plane of a polygon. */

 /* extern */
void Graphu64_CrossVectors(f32 *, void *, f32 *);

s32 CCollision_IntersectFrontPlaneFraction(void *poly, void *start, void *segmentEnd, f32 *outputFraction) {
    f32 segmentDirection[3];
    f32 planeToStart[3];
    f32 normalDotDirection;
    f32 hitFraction;
    s32 result;

    if (((struct CollisionPlaneEnabledView *)(poly))->value == 0) {
        return 0;
    }
    Graphu64_SubtractVectors(segmentDirection, segmentEnd, start);
    normalDotDirection = (((struct CollisionPlaneNormalXView *)(poly))->value * segmentDirection[0]) + (((struct Measured *)(poly))->value * segmentDirection[1]) + (((struct CollisionPlaneNormalZView *)(poly))->value * segmentDirection[2]);
    result = 0;
    if (!(normalDotDirection >= (f32)0)) {
        Graphu64_SubtractVectors(planeToStart, start, &((Polygon *)poly)->vertices[0]);
        result = 1;
        hitFraction = -((((struct CollisionPlaneNormalXView *)(poly))->value * planeToStart[0]) + (((struct Measured *)(poly))->value * planeToStart[1]) + (((struct CollisionPlaneNormalZView *)(poly))->value * planeToStart[2])) / normalDotDirection;
    } else {
        hitFraction = g_frontPlaneIntersectionInitialFraction;
    }
    *outputFraction = hitFraction;
    return result;
}

s32 CCollision_IntersectFrontPlanePoint(void *contactPlane, void *segmentStart, void *segmentEnd, void *outputPoint) {
    f32 segmentDirection[3];
    f32 planeToStart[3];
    f32 hitFraction;
    f32 normalDotDirection;
    s32 intersectsPlane;

    if (((struct CollisionPlaneEnabledView *)(contactPlane))->value == 0) {
        intersectsPlane = 0;
    } else {
        Graphu64_SubtractVectors(segmentDirection, segmentEnd, segmentStart);
        normalDotDirection = (((struct CollisionPlaneNormalXView *)(contactPlane))->value * segmentDirection[0]) + (((struct Measured *)(contactPlane))->value * segmentDirection[1]) + (((struct CollisionPlaneNormalZView *)(contactPlane))->value * segmentDirection[2]);
        intersectsPlane = 0;
        if (normalDotDirection >= (f32)0) {
            hitFraction = g_frontPlaneIntersectionFallbackFraction;
        } else {
            Graphu64_SubtractVectors(planeToStart, segmentStart, &((Polygon *)contactPlane)->vertices[0]);
            intersectsPlane = 1;
            hitFraction = -((((struct CollisionPlaneNormalXView *)(contactPlane))->value * planeToStart[0]) + (((struct Measured *)(contactPlane))->value * planeToStart[1]) + (((struct CollisionPlaneNormalZView *)(contactPlane))->value * planeToStart[2])) / normalDotDirection;
        }
    }
    if (intersectsPlane != 0) {
        Graphu64_InterpolateVector(outputPoint, *(u32 *)&hitFraction, segmentStart, segmentEnd);
        return 1;
    }
    return 0;
}

/* extern */
s32 CCollision_IsPointInsidePolygon(LinkedWorldFlagsView *poly, void *testPoint) {
    f32 edgePlaneNormal[3];
    f32 edgeVector[3];
    f32 vertexToPoint[3];
    s32 vertexTotal;
    void *vertexCursor;
    s32 remainingEdges;
    void *previousVertex;
    vertexTotal = ((PolygonCCollisionTestSegmentPolygon *)poly)->vertexCount;
    if (vertexTotal == 1) {
        return 1;
    }
    previousVertex = &((Polygon *)poly)->vertices[vertexTotal - 1];
    vertexCursor = ((PolygonCCollisionTestSegmentPolygon *)poly)->vertices;
    remainingEdges = vertexTotal;
    remainingEdges = remainingEdges - 1;
    for (; remainingEdges != -1; vertexCursor += sizeof(CVector3), remainingEdges--) {
        Graphu64_SubtractVectors(edgeVector, vertexCursor, previousVertex);
        Graphu64_CrossVectors(edgePlaneNormal, &((PolygonCCollisionTestSegmentPolygon *)poly)->normal, edgeVector);
        Graphu64_SubtractVectors(vertexToPoint, testPoint, previousVertex);
        previousVertex = vertexCursor;
        if (edgePlaneNormal[0]*vertexToPoint[0]+edgePlaneNormal[1]*vertexToPoint[1]+edgePlaneNormal[2]*vertexToPoint[2] > 0.0f) return 0;
    }
    return 1;
}

s32 CCollision_IsPointInsideDisk(void *poly, void *point, f32 radius, void *testPoint) {
    CVector3 *first = point;
    CVector3 *second = testPoint;
    f32 dx = first->x - second->x;
    f32 dz = first->z - second->z;
    s32 result = 1;
    if (!((dx * dx + dz * dz) <= (radius * radius))) {
        result = 0;
    }
    return result;
}

/* Tests whether a point lies inside an object's four-sided footprint: for each edge of the corners at 0x18 it checks the side the point falls on in the x-z plane, walking the edges in reverse when the winding value at 0x4C is negative. */

s32 CCollision_IsPointInsideFootprint(Footprint *fp, CVector3 *p)
{
    s32 i;
    CVector3 *a;
    CVector3 *b;
    f32 ax;

    for (i = 0; i < 4; i++) {
        if (fp->winding < 0.0f) {
            b = &fp->corner[i];
            a = &fp->corner[(i + 1) & 3];
        } else {
            a = &fp->corner[i];
            b = &fp->corner[(i + 1) & 3];
        }
        ax = a->x;
        if (0.0f < (b->z - a->z) * (p->x - ax) + (ax - b->x) * (p->z - a->z)) {
            return 0;
        }
    }
    return 1;
}

f32 CCollision_GetSurfaceHeight(void *query, f32 x, f32 z) {
    CVector3 normal;
    CVector3 point;

    normal = ((SurfaceHit *)query)->normal;
    if (normal.y == 0.0f) {
        return ((SurfaceHit *)query)->point.y;
    }
    point = ((SurfaceHit *)query)->point;
    return (((point.z - z) * normal.z) + ((point.x - x) * normal.x) + (point.y * normal.y)) / normal.y;
}

/* 802412C0.CPP */
f32 CCollision_GetContactYaw(f32 *contactRecord) {
    f32 magnitude;
    f32 result;
    f32 zero;

    magnitude = Gu_Sqrtf((contactRecord[18] * contactRecord[18]) + (contactRecord[20] * contactRecord[20]));
    zero = 0.0f;
    if (magnitude == zero) {
        return zero;
    }
    result = Graphu64_ArcCos(contactRecord[20] / magnitude);
    if (!(zero < contactRecord[18])) {
        result = -result;
    }
    return result;
}
