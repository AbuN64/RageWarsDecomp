#include "COMMON/DESCRIPTORRECAT29.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OUTPUT.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "ENGINE/UNICOL/COLLIDE.H"

extern f32 CCollision_GetSurfaceHeight(struct Query *, f32, f32);

extern f32 Gu_Sqrtf(f32);

extern void Graphu64_ScaleVector(struct CVector3_t *,struct CVector3_t *,f32);


/* Tests a ray against a polygon: intersects the ray from 0x44 to 0x50 with the polygon's plane through
 * CCollision_IntersectFrontPlaneFraction and accepts a parameter nearer than the ray's current nearest hit, also allowing a slightly negative
 * one (above -g_collisionSlackThreshold * g_collisionSegmentPolygonSlackFactor scaled by the ray's 0x80 factor) except for kind 7 and types 5 and
 * 6; the hit point is then placed with Graphu64_InterpolateVector and must lie inside the polygon (CCollision_IsPointInsidePolygon). On a
 * hit the polygon record is optionally kept as the ray's nearest hit at 0xB0. */









extern s32 CCollision_IntersectFrontPlaneFraction(PolygonCCollisionTestSegmentPolygon *, CVector3 *, CVector3 *, f32 *);

extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);

extern s32 CCollision_IsPointInsidePolygon(PolygonCCollisionTestSegmentPolygon *, CVector3 *);

static inline s32 accepts(CapsuleSweep *ray, PolygonCCollisionTestSegmentPolygon *poly) {
    if (poly->t <= 0.0f) {
        if (poly->kind == 7) {
            return 0;
        }
        if ((u32)(poly->type - 5) < 2) {
            return 0;
        }
        if (poly->t * ray->slack < -(g_collisionSlackThreshold * g_collisionSegmentPolygonSlackFactor)) {
            return 0;
        }
    }
    if (poly->t >= ray->nearest.t) {
        return 0;
    }
    return 1;
}

/* Clips a segment against a query: measures the heights of its two ends through CCollision_GetSurfaceHeight,
   raises the far end by k_collisionSurfaceOffsetScales[1] scaled to 10.24, and when the squared flat length plus the
   squared height difference is not zero, moves the far end to the fraction Gu_Sqrtf_TurretMove returns
   for the flat share of that length, writing the interpolated height at 0x54 and position at 0x50
   and 0x58. The node at 0x74 is then faded by what is left of one after the limit at 0x10 of the
   record at 0x40, and not at all once that limit passes one. */

struct Query;

void CCollision_ProjectSegmentOntoSurface(CollisionSegmentSurface *segment, struct Query *query) {
    f32 start;
    f32 span;
    f32 flat;
    f32 total;
    f32 dx;
    f32 dy;
    f32 share;
    f32 limit;
    f32 nx;
    void *target;
    f32 fade;
    void *node;

    start = CCollision_GetSurfaceHeight(query, segment->x0, segment->y0);
    span = (CCollision_GetSurfaceHeight(query, segment->x1, segment->y1) + (k_collisionSurfaceOffsetScales[1] * 10.24f)) - start;
    dx = segment->x1 - segment->x0;
    dy = segment->y1 - segment->y0;
    flat = (dx * dx) + (dy * dy);
    total = flat + (span * span);
    if (total == 0.0f) {
        segment->height = start;
        return;
    }
    share = Gu_Sqrtf(flat / total);
    node = segment->node;
    nx = segment->x0 + (share * (segment->x1 - segment->x0));
    segment->height = start + (share * span);
    segment->x1 = nx;
    segment->y1 = segment->y0 + (share * (segment->y1 - segment->y0));
    limit = segment->limits->value;
    target = node;
    if (1.0f < limit) {
        fade = 0.0f;
    } else {
        fade = 1.0f - limit;
    }
    Graphu64_ScaleVector(target, node, fade);
}

/** Thin wrapper around CCollision_ClearContactNormal. */
void CCollision_ResetContactNormal(void *contactInput) {
    CCollision_ClearContactNormal(contactInput);
}

void CCollision_ClearContactNormal(void *contactStorage) {
    struct Input *input = contactStorage;
    input->contactNormal.x = 0.0f;
    input->contactNormal.y = 0.0f;
    input->contactNormal.z = 0.0f;
}

s32 CCollision_HasMatchingNormal(struct Input *input, PolygonCCollisionTestSegmentPolygon *polygon) {
    s32 same;

    same = 0;
    if ((input->contactNormal.x == polygon->normal.x) &&
        (input->contactNormal.y == polygon->normal.y) &&
        (input->contactNormal.z == polygon->normal.z)) {
        same = 1;
    }
    return same;
}

/** Copy three words from offsets 0x48..0x50 to offsets 0x18C..0x194. */
void CCollision_CopyPolygonNormal(void *contactStorage, void *polygonStorage) {
    CollisionPolygonNormalView *polygon = polygonStorage;
    CollisionContactVectorView *contact = contactStorage;
    contact->contactVector = polygon->normal;
}

s32 CCollision_TestSegmentPolygon(CapsuleSweep *ray, PolygonCCollisionTestSegmentPolygon *poly, s32 keep) {
    if (CCollision_IntersectFrontPlaneFraction(poly, &ray->start, &ray->end, &poly->t) == 0) {
        return 0;
    }
    if (accepts(ray, poly) == 0) {
        return 0;
    }
    Graphu64_InterpolateVector(&poly->hit, poly->t, &ray->start, &ray->end);
    if (CCollision_IsPointInsidePolygon(poly, &poly->hit) == 0) {
        return 0;
    }
    if (keep != 0) {
        ray->nearest = *poly;
    }
    return 1;
}
