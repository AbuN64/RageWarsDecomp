#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/resident_event_handler.h"
#include "Common/box_contact.h"
#include "Common/rendersortrecord.h"
#include "Game/ccollision_copypositionandgetmodelflags.h"
#include "Common/output.h"
#include "Common/approachlocation.h"
#include "Common/ballisticparams.h"
#include "Engine/Unicol/plane.h"
#include "Common/math_helpers.h"
#include "Anim/collision_ray.h"
#include "Anim/cplane_resetcontact.h"
#include "Fx/normalize_vector.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Common/measured_storage.h"
#include <platform_sdk.h>
#include "Plane/ccollision_intersectfrontplanepoint.h"
#include "Collide/ccollision_testsegmentdisk.h"
#include "include_asm.h"
#include "Rsp/random_direction_and_affine_math.h"

/* CCOLLISION_COPYPOSITIONANDGETMODELFLAGS.CPP */

s32 CCollision_CopyProbePosition(struct LevelActor *unusedActor, CVector3 t, s32 room, s32 unusedRadius, CVector3 *outputPoint) {
    char frameScratch[0xB60];
    *outputPoint = t;
    return 1;
}

s32 CCollision_CopyPositionAndGetModelFlags(void *modelStorage, s32 unusedFlags, CVector3 t, s32 unusedRoom, s32 unusedRadius, void *outputStorage) {
    struct Model *model = modelStorage;
    CVector3 *output = outputStorage;
    Triple scratchPositionA;
    Triple scratchPositionB;
    *output = t;
    return model->flags;
}

/* PLANE.CPP */

/* Is `point` inside the polygon prism, or within `radius` of its edges?
 * Each edge's outward normal (normal x edge) splits off the outside half-space; a point outside an edge
 * passes only when its distance to that edge is at most `radius`. Types 3 and 4 measure the distance
 * to the edge segment (clamped at its end vertex); other types measure it to the edge line and let the
 * projection run past either end by at most `radius`. */
s32 Plane_TestPointNearPolygon(Polygon *polygon, CVector3 *point, f32 radius)
{
    CVector3 outward;
    CVector3 edge;
    CVector3 delta;
    CVector3 *previousVertex;
    CVector3 *vertex;
    f32 projection;
    f32 side;
    f32 lengthSquared;
    f32 radiusSquared;
    f32 limit;
    s32 remaining;

    if (polygon->vertexCount == 1) {
        return 1;
    }
    previousVertex = &polygon->vertices[polygon->vertexCount - 1];
    vertex = polygon->vertices;
    radiusSquared = radius * radius;
    remaining = polygon->vertexCount;
    if (polygon->type == 3 || polygon->type == 4) {
        for (; --remaining != -1; previousVertex = vertex++) {
            Graphu64_SubtractVectors(&edge, vertex, previousVertex);
            Graphu64_CrossVectors(&outward, &polygon->normal, &edge);
            Graphu64_SubtractVectors(&delta, point, previousVertex);
            side = outward.x * delta.x + outward.y * delta.y + outward.z * delta.z;
            if (side > 0.0f) {
                if (radius > 0.0f) {
                    projection = edge.x * delta.x + edge.y * delta.y + edge.z * delta.z;
                    if (projection > 0.0f) {
                        lengthSquared = edge.x * edge.x + edge.y * edge.y + edge.z * edge.z;
                        if (lengthSquared <= projection) {
                            Graphu64_SubtractVectors(&delta, &delta, &edge);
                        } else {
                            Graphu64_ScaleVector(&edge, &edge, projection / lengthSquared);
                            Graphu64_SubtractVectors(&delta, &delta, &edge);
                        }
                    }
                    if (!(radiusSquared < delta.x * delta.x + delta.y * delta.y + delta.z * delta.z)) {
                        continue;
                    }
                }
                return 0;
            }
        }
    } else {
        for (; --remaining != -1; previousVertex = vertex++) {
            Graphu64_SubtractVectors(&edge, vertex, previousVertex);
            Graphu64_CrossVectors(&outward, &polygon->normal, &edge);
            Graphu64_SubtractVectors(&delta, point, previousVertex);
            side = outward.x * delta.x + outward.y * delta.y + outward.z * delta.z;
            if (side > 0.0f) {
                if (radius > 0.0f) {
                    projection = edge.x * delta.x + edge.y * delta.y + edge.z * delta.z;
                    lengthSquared = edge.x * edge.x + edge.y * edge.y + edge.z * edge.z;
                    projection /= lengthSquared;
                    if (projection < 0.0f) {
                        limit = -radius / Gu_Sqrtf(lengthSquared);
                        if (projection < limit) {
                            return 0;
                        }
                    } else if (1.0f < projection) {
                        limit = 1.0f + radius / Gu_Sqrtf(lengthSquared);
                        if (limit < projection) {
                            return 0;
                        }
                    }
                    Graphu64_ScaleVector(&edge, &edge, projection);
                    Graphu64_SubtractVectors(&delta, &delta, &edge);
                    if (!(radiusSquared < delta.x * delta.x + delta.y * delta.y + delta.z * delta.z)) {
                        continue;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

/* Height of the plane above the horizontal point (x, z); a plane with a flat normal (y component zero) reports its anchor height. */
static inline f32 CPlane_GetHeightAt(Plane *plane, f32 x, f32 z) {
    CVector3 normal = plane->normal;
    CVector3 anchor;

    if (normal.y == 0) {
        return plane->pos.y;
    }
    anchor = plane->pos;
    return ((anchor.z - z) * normal.z + (anchor.x - x) * normal.x + anchor.y * normal.y) / normal.y;
}

/* Computes the signed incline between two horizontal points projected onto a plane. */
f32 CPlane_GetSlopeAngle(Plane *plane, f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 startHeight;
    f32 endHeight;
    f32 deltaX;
    f32 deltaZ;
    f32 deltaHeight;
    f32 horizontalSquared;
    f32 lengthSquared;
    f32 angle;

    if (plane == 0) {
        return 0;
    }
    startHeight = CPlane_GetHeightAt(plane, x0, z0);
    endHeight = CPlane_GetHeightAt(plane, x1, z1);
    deltaX = x1 - x0;
    deltaZ = z1 - z0;
    deltaHeight = endHeight - startHeight;
    horizontalSquared = deltaX * deltaX + deltaZ * deltaZ;
    lengthSquared = horizontalSquared + deltaHeight * deltaHeight;
    angle = 0.0f;
    if (lengthSquared != 0) {
        angle = Gu_Sqrtf(horizontalSquared / lengthSquared);
        angle = Graphu64_ArcCos(RW_MAX_GT(-1.0f, RW_MIN_LT(1.0f, angle)));
        if (!(startHeight < endHeight)) {
            angle = -angle;
        }
    }
    return angle;
}

void CPlane_ResetContact(void *contactStorage)
{
    PlaneContactStorageView *contact = contactStorage;
    int invalidContact;
    f32 initialContactDistance;
    initialContactDistance = (f32) g_planeInitialContactDistance;
    contact->clearedWordFirst = 0;
    contact->clearedWordSecond = 0;
    invalidContact = -1;
    contact->invalidContactIndex = invalidContact;
    contact->contactDistance = initialContactDistance;
}

/* Sets up one face of a box as a four-corner quad of kind 4, copying points 0, 1, 2 and 3 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */
static inline void quad_normal(struct Quad *quad) {
    CVector3 first;
    CVector3 second;

    Graphu64_SubtractVectors(&first, &quad->corner[1], &quad->corner[0]);
    Graphu64_SubtractVectors(&second, &quad->corner[2], &quad->corner[1]);
    Graphu64_CrossVectors(&quad->normal, &second, &first);
    Graphu64_NormalizeVec3(&quad->normal);
}

void CPlane_BuildTriangleNormal(void *query) {
    QueryE0 *object = query;
    CVector3 firstEdge;
    CVector3 secondEdge;
    CVector3 *middleVertex;
    CVector3 *outputNormal;

    middleVertex = &object->vectors[1];
    Graphu64_SubtractVectors(&firstEdge, middleVertex, &object->vectors[0]);
    Graphu64_SubtractVectors(&secondEdge, &object->vectors[2], middleVertex);
    outputNormal = &object->result;
    Graphu64_CrossVectors(outputNormal, &secondEdge, &firstEdge);
    Graphu64_NormalizeVec3(outputNormal);
}

void Plane_BuildBoxFace0(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[0];
    quad->corner[2] = points[1];
    quad->corner[1] = points[2];
    quad->corner[0] = points[3];
    quad_normal(quad);
}

/* Sets up one face of a box as a four-corner quad of kind 4, copying points 7, 6, 5 and 4 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */

void Plane_BuildBoxFace1(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[7];
    quad->corner[2] = points[6];
    quad->corner[1] = points[5];
    quad->corner[0] = points[4];
    quad_normal(quad);
}

/* Sets up one face of a box as a four-corner quad of kind 4, copying points 3, 2, 6 and 7 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */

void Plane_BuildBoxFace2(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[3];
    quad->corner[2] = points[2];
    quad->corner[1] = points[6];
    quad->corner[0] = points[7];
    quad_normal(quad);
}

/* Sets up one face of a box as a four-corner quad of kind 4, copying points 4, 5, 1 and 0 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */

void Plane_BuildBoxFace3(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[4];
    quad->corner[2] = points[5];
    quad->corner[1] = points[1];
    quad->corner[0] = points[0];
    quad_normal(quad);
}

/* Sets up one face of a box as a four-corner quad of kind 4, copying points 0, 3, 7 and 4 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */

void Plane_BuildBoxFace4(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[0];
    quad->corner[2] = points[3];
    quad->corner[1] = points[7];
    quad->corner[0] = points[4];
    quad_normal(quad);
}

/* Sets up one face of a box as a four-corner quad of kind 4, copying points 2, 1, 5 and 6 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */

void Plane_BuildBoxFace5(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[2];
    quad->corner[2] = points[1];
    quad->corner[1] = points[5];
    quad->corner[0] = points[6];
    quad_normal(quad);
}

s32 CPlane_IsPointBehind(void *plane, CVector3 *testPoint) {
    Plane *object = plane;
    CVector3 offset;
    s32 outside;

    Graphu64_SubtractVectors(&offset, testPoint, &object->pos);
    outside = 0;
    if (!((object->normal.x * offset.x) + (object->normal.y * offset.y) + (object->normal.z * offset.z) >= 0.0f)) {
        outside = 1;
    }
    return outside;
}

/* CCOLLISION_INTERSECTFRONTPLANEPOINT.CPP */

/* Tests a point against every edge plane of a polygon. */

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
        Graphu64_InterpolateVector(outputPoint, hitFraction, segmentStart, segmentEnd);
        return 1;
    }
    return 0;
}

/* extern */
s32 CCollision_IsPointInsidePolygon(Polygon *poly, void *testPoint) {
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

/* Tests whether a point lies inside an object's four-sided footprint: for each edge of the corners it checks the side the point falls on in the x-z plane, walking the edges in reverse when the winding value is negative. */

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

/* CCOLLISION_DISTANCETOSEGMENT.CPP */

/* Returns the distance from point p to the segment from a to b: the offset of p from a is reduced by
 * its projection onto the segment direction, clamped to the segment ends, before taking the length. */

f32 CCollision_DistanceToSegment(CVector3 *a, CVector3 *b, CVector3 *p) {
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

/* CCOLLISION_INTERSECTFRONTPLANEFRACTION_DATA.CPP */

const float k_CcollisionIntersectfrontplanefraction[3] = {
    1.0f, 1.0f, 1.0f,
};

#if defined(VERSION_US)
char s_CcollisionIntersectfrontplanefractionDwChText[8] =
    "\000\016m_dwCh";
#endif

#if defined(VERSION_DE)
float k_CcollisionIntersectfrontplanefractionConstants[2] = {
    0.4096f, 0.4096f,
};
#endif
