#include "COMMON/DESCRIPTORRECAT29.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MOTION_STEP.H"
#include "COMMON/OUTPUT.H"
#include "TYPES.H"
#include "COMMON/BALLISTICPARAMS.H"

/* Tests a ray against a vertical cylinder: projects the center onto the ray's horizontal direction from 0x44,
 * finds the entry parameter from the radius, accepts it under the same rules as CCollision_TestSegmentPolygon, places the
 * hit with Graphu64_InterpolateVector and optionally rejects hits above the top or below the bottom; when kept, the
 * polygon record takes the hit as its point with a horizontal normal away from the center and becomes the
 * ray's nearest hit. Adapted from CCollision_TestSegmentPolygon with its static acceptance helper.
 */







extern f32 g_collisionSlackThresholdFactors_de[];


extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);


static inline s32 accepts(RayCCollisionTestRayCylinder *ray, PolygonCCollisionTestRayCylinder *poly) {
    if (poly->t <= 0.0f) {
        if (poly->kind == 7) {
            return 0;
        }
        if ((u32)(poly->type - 5) < 2) {
            return 0;
        }
        if (poly->t * ray->slack < -(g_collisionSlackThreshold * g_collisionSlackThresholdFactors_de[2])) {
            return 0;
        }
    }
    if (poly->t >= ray->nearest.t) {
        return 0;
    }
    return 1;
}

extern CCollisionResults *g_collisionCurrentActor;

s32 CCollision_TestRayCylinder(RayCCollisionTestRayCylinder *ray, CVector3 *center, f32 radius, f32 top, f32 bottom, s32 clip, PolygonCCollisionTestRayCylinder *poly, s32 keep) {
    CVector3 delta;
    CVector3 dir;
    CVector3 perp;
    f32 len;
    f32 inv;
    f32 along;
    f32 disc;

    delta.x = center->x - ray->start.x;
    delta.z = center->z - ray->start.z;
    if (delta.x * ray->dir.x + delta.z * ray->dir.z < 0.0f) {
        return 0;
    }
    len = Gu_Sqrtf(ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z);
    if (len == 0.0f) {
        return 0;
    }
    inv = g_collisionSlackThresholdFactors_de[1] / len;
    dir.x = ray->dir.x * inv;
    dir.z = ray->dir.z * inv;
    along = delta.x * dir.x + delta.z * dir.z;
    perp.x = delta.x - dir.x * along;
    perp.z = delta.z - dir.z * along;
    disc = radius * radius - (perp.x * perp.x + perp.z * perp.z);
    if (!(disc > 0.0f)) {
        return 0;
    }
    poly->t = (along - Gu_Sqrtf(disc)) * inv;
    if (accepts(ray, poly) != 0) {
        Graphu64_InterpolateVector(&poly->hit, poly->t, &ray->start, &ray->end);
        if (clip != 0 && (poly->hit.y > top || poly->hit.y < bottom)) {
            return 0;
        }
        if (keep != 0) {
            poly->flag = 1;
            poly->point = poly->hit;
            poly->normal.x = poly->point.x - center->x;
            poly->normal.y = 0.0f;
            poly->normal.z = poly->point.z - center->z;
            ray->nearest = *poly;
        }
        return 1;
    }
    return 0;
}

void CCollision_StoreContactResult(Input *contactInput) {
    {
        s32 type = contactInput->type;
        s32 sw_type_value = type - 1;
        if ((unsigned int)sw_type_value > 8) {
            goto sw_type_default;
        }
        switch (sw_type_value) {
        case 0: goto sw_type_1;
        case 1: goto sw_type_1;
        case 2: goto sw_type_1;
        case 3: goto sw_type_1;
        case 4: goto sw_type_2;
        case 5: goto sw_type_6;
        case 6: goto sw_type_3;
        case 7: goto sw_type_4;
        case 8: goto sw_type_5;
        }
    }
    do {
    sw_type_1:
        g_collisionCurrentActor->instance0 = contactInput->instance104;
        if (contactInput->instance104 != 0) {
            g_collisionCurrentActor->instanceValue4 = contactInput->instance104->value;
        } else {
            g_collisionCurrentActor->instanceValue4 = 0;
        }
        g_collisionCurrentActor->vec8 = contactInput->vec180;
        g_collisionCurrentActor->value = -1;
        break;
    sw_type_2:
        if (contactInput->instance104 != 0) {
            g_collisionCurrentActor->instanceValueC4 = contactInput->instance104->value;
        } else {
            g_collisionCurrentActor->instanceValueC4 = 0;
        }
        g_collisionCurrentActor->vecC8 = contactInput->vec180;
        g_collisionCurrentActor->contactAuxValue = contactInput->contactAuxValue;
        break;
    sw_type_3:
        g_collisionCurrentActor->instance0 = contactInput->instance104;
        g_collisionCurrentActor->instanceValue4 = contactInput->instance104->value;
        g_collisionCurrentActor->vec8 = contactInput->vec180;
        g_collisionCurrentActor->value = -1;
        break;
    sw_type_4:
        g_collisionCurrentActor->instance0 = contactInput->instance104;
        g_collisionCurrentActor->instanceValue4 = contactInput->instance104->value;
        g_collisionCurrentActor->vec8 = contactInput->vec180;
        g_collisionCurrentActor->value = contactInput->blockValue;
        g_collisionCurrentActor->block18 = contactInput->block10C;
        break;
    sw_type_5:
        g_collisionCurrentActor->instance88 = contactInput->instance104;
        g_collisionCurrentActor->instanceValue8C = contactInput->instance104->value;
        g_collisionCurrentActor->vec90 = contactInput->vec180;
        break;
    sw_type_6:
    sw_type_7:
    sw_type_8:
    sw_type_9:
        break;

    sw_type_default:;
    } while (0);
    g_collisionCurrentActor->vecF0 = contactInput->vecF8;
    g_collisionCurrentActor->vecE4 = contactInput->vec180;
    g_collisionCurrentActor->typeFC = contactInput->type;
    g_collisionCurrentActor->contactValue = contactInput->contactValue;
}

/* Stores a range and its parameters in a record: the low bound at 8, a count at 0xC, the high
   bound at 0x10 and a fourth value at 0x14, and at 0x18 the larger bound plus the pooled constant
   g_collisionCylinderRangeMargin. */




void CCollision_SetSweepRange(struct Range *range, f32 low, s32 count, f32 high, f32 extra) {
    f32 larger;

    range->count = count;
    range->low = low;
    range->high = high;
    range->extra = extra;
    larger = high;
    if (!(low <= high)) {
        larger = low;
    }
    range->limit = larger + g_collisionCylinderRangeMargin;
}

void CCollision_SetUniformSweepExtent(void *actorMotion, float extent) {
    ActorMotion *motion = actorMotion;
    motion->bottom = 0.0f;
    motion->sweepExtentFirst = extent;
    motion->radius = extent;
    motion->height = extent;
    motion->sweepExtentLast = extent;
}
