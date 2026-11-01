#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "ANIM/RAY180.H"
#include "ENGINE/UNICOL/POLYCOL.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* 800C886C.CPP */

/* 80241940_4.CPP */
extern s32 CCollision_TestSegmentPolygon(void *, s32 *, s32);

extern void Plane_BuildBoxFace0(s32 *, void *);

extern void Plane_BuildBoxFace1(s32 *, void *);

extern void Plane_BuildBoxFace2(s32 *, void *);

extern void Plane_BuildBoxFace3(s32 *, void *);

extern void Plane_BuildBoxFace4(s32 *, void *);

extern void Plane_BuildBoxFace5(s32 *, void *);

s32 CCollision_TestRayCylinder(void *, void *, f32, s32, f32, s32, s32 *, s32);

s32 CCollision_TestSegmentDisk(void *, s32 *, void *, f32, s32);

/* Gathers the pieces a ray sweeps through: for each entry of the counted table in g_worldCollisionElementTable whose
 * rectangle, grown by the ray's radius, overlaps the ray's rectangle and is hit by it, each visible element
 * of the entry's resource whose grown box overlaps the ray's box and is hit is recorded with its hit
 * parameter (at most 128). The hits are sorted and, while nearer than the ray's current nearest hit, each
 * is handed to CPolyCollision_TraceElementMesh with a context holding the ray, its look-at matrix and segment spacing. */
extern struct {
    char pad0[0x5AC];
    s32 count;
    EntryC entries[1];
} g_worldCollisionElementTable;

extern s32 CCollision_IntersectSegmentBox(Ray180 *, Box *, f32 *);

extern s32 CCollision_IntersectSegmentRectangle(Ray180 *, CQuatern *, f32 *);

extern void CPolyCollision_TraceElementMesh(ContextB0 *);

extern void PpDecom_QuickSortRecords(char *, u32, u32, void *, void *);

s32 CPolyCollision_TraceBoxFaces(void *ray, void *unusedPlatform, void *corners, s32 *quad) {
    s32 result;

    result = 0;
    if (((struct PlatformMovementView *) ray)->movementY > 0.0f) {
        *quad = 2;
        Plane_BuildBoxFace1(quad, corners);
        result = CCollision_TestSegmentPolygon(ray, quad, 1);
    }
    if ((((struct PlatformMovementView *) ray)->movementX != 0.0f) || (((struct PlatformMovementView *) ray)->movementZ != 0.0f)) {
        *quad = 3;
        Plane_BuildBoxFace2(quad, corners);
        result |= CCollision_TestSegmentPolygon(ray, quad, 1);
        Plane_BuildBoxFace3(quad, corners);
        result |= CCollision_TestSegmentPolygon(ray, quad, 1);
        Plane_BuildBoxFace4(quad, corners);
        result |= CCollision_TestSegmentPolygon(ray, quad, 1);
        Plane_BuildBoxFace5(quad, corners);
        result |= CCollision_TestSegmentPolygon(ray, quad, 1);
    }
    if (((struct PlatformMovementView *) ray)->movementY < 0.0f) {
        *quad = 9;
        Plane_BuildBoxFace0(quad, corners);
        result |= CCollision_TestSegmentPolygon(ray, quad, 1);
    }
    return result;
}

s32 CPolyCollision_TraceCylinderFaces(void *ray, void *platform, void *corners, s32 *contactPolygon) {
    f32 radius;
    s32 hitFound;
    void *point;

    hitFound = 0;
    point = platform + 8;
    radius = ((struct PlatformHeightView *) ((struct ActorDefinitionPointerView *) platform)->definition)->cylinderRadius + ((struct PlatformRadiusMovementView *) ray)->radius;
    if ((((struct PlatformRadiusMovementView *) ray)->movementX != 0.0f) || (((struct PlatformRadiusMovementView *) ray)->movementZ != 0.0f)) {
        *contactPolygon = 3;
        hitFound = CCollision_TestRayCylinder(ray, point, radius, ((struct PlatformActivityPhaseView *) corners)->top, ((struct PlatformActivityPhaseView *) corners)->bottom, 1, contactPolygon, 1);
    }
    if (((struct PlatformRadiusMovementView *) ray)->movementY > 0.0f) {
        *contactPolygon = 2;
        Plane_BuildBoxFace1(contactPolygon, corners);
        hitFound |= CCollision_TestSegmentDisk(ray, contactPolygon, point, radius, 1);
    }
    if (((struct PlatformRadiusMovementView *) ray)->movementY < 0.0f) {
        *contactPolygon = 9;
        Plane_BuildBoxFace0(contactPolygon, corners);
        hitFound |= CCollision_TestSegmentDisk(ray, contactPolygon, point, radius, 1);
    }
    return hitFound;
}

void CPolyCollision_TraceWorldElements(Ray180 *ray) {
    Box box;
    CQuatern rect;
    ContextB0 ctx;
    Hit8 hits[128];
    f32 t;
    CVector3 *start;
    CVector3 *end;
    Hit8 *hit;
    EntryC *table;
    ModelF0 *model;
    ElementE8 *element;
    s32 count;
    s32 hitCount;
    s32 segments;
    s32 remaining;
    s32 i;
    s32 j;

    start = &ray->start;
    end = &ray->end;
    ctx.ray = ray;
    ctx.start = start;
    ctx.end = end;
    ctx.reach = ray->scale * ray->nearest + ray->radius;
    if (ray->spacing != 0.0f) {
        segments = ((2) > ((s32) (ray->length / ray->spacing) + 1) ? (2) : ((s32) (ray->length / ray->spacing) + 1));
        ctx.segments = segments;
        ctx.step = (ray->length - 2.0f * ray->spacing) / (f32) (segments - 1);
    } else {
        ctx.segments = 1;
        ctx.step = 1.0f;
    }
    hit = hits;
    hitCount = 0;
    table = g_worldCollisionElementTable.entries;
    count = g_worldCollisionElementTable.count;
    for (i = 0; i < count; i++) {
        rect.x = table[i].rect->x - ray->radius;
        rect.y = table[i].rect->y - ray->radius;
        rect.z = table[i].rect->z + ray->radius;
        rect.w = table[i].rect->w + ray->radius;
        if (ray->rect.x < rect.z && rect.x < ray->rect.z && ray->rect.y < rect.w &&
            rect.y < ray->rect.w && CCollision_IntersectSegmentRectangle(ray, &rect, &t) != 0) {
            model = SetN64_GetPackSection(*table[i].resource, 0);
            remaining = model->count;
            element = model->elements;
            while (--remaining != -1) {
                if (hitCount >= 128) {
                    break;
                }
                if (!(element->flags & 0x10)) {
                    box.min.x = element->box.min.x - ray->radius;
                    box.min.y = element->box.min.y - ray->radius;
                    box.min.z = element->box.min.z - ray->radius;
                    box.max.x = element->box.max.x + ray->radius;
                    box.max.y = element->box.max.y + ray->radius;
                    box.max.z = element->box.max.z + ray->radius;
                    if (box.min.x < ray->box.max.x && ray->box.min.x < box.max.x && box.min.z < ray->box.max.z &&
                        ray->box.min.z < box.max.z && box.min.y < ray->box.max.y && ray->box.min.y < box.max.y &&
                        CCollision_IntersectSegmentBox(ray, &box, &t) != 0) {
                        hitCount++;
                        hit->element = element;
                        hit->t = t;
                        hit++;
                    }
                }
                element++;
            }
        }
    }
    if (hitCount != 0) {
        Graphu64_ComputeViewMatrix(&ctx.matrix, start, end, &g_collisionTraceViewUpVector);
        PpDecom_QuickSortRecords((char *) hits, hitCount, sizeof(Hit8), CPolyCollision_CompareSortedHits, CPolyCollision_SwapSortedHits);
        hit = hits;
        for (j = 0; j < hitCount; j++, hit++) {
            if (!(hit->t < ray->nearest)) {
                break;
            }
            element = hit->element;
            ctx.element = element;
            ctx.kind = Barrel_GetImpactSlot(element);
            if (ctx.kind == 9) {
                ctx.isKind9 = 1;
            } else {
                ctx.isKind9 = 0;
            }
            CPolyCollision_TraceElementMesh(&ctx);
        }
    }
}
