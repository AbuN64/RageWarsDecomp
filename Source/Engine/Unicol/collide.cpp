#include "include_asm.h"
#include "types.h"
#include "Common/motion_step.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/triple.h"
#include "Common/sharedplayer.h"
#include "Common/virtual_pager.h"
#include "Common/rendersortrecord.h"
#include "Common/sky_layers.h"
#include "Anim/cplane_resetcontact.h"
#include "Engine/Unicol/collide.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Engine/Unicol/Collide/ccollision_traceactormotion.h"
#include "Polycol/polycol_tracegeometry.h"
#include "Polycol/cpolycollision_traceceilingtriangle.h"
#include "Common/vector4f.h"
#include "Common/runtime_declarations.h"
#include "Common/approachlocation.h"
#include "Common/output.h"
#include "Common/graphics_matrix_and_vector_math.h"
#include "Fx/normalize_vector.h"
#include "Engine/Unicol/Collide/ccollision_intersectsegmentbox.h"
#include "Engine/Unicol/plane.h"
#include "Engine/Unicol/Collide/ccollision_testoffsetpolygon.h"
#include "Common/ballisticparams.h"
#include "Common/Lone/collision_current_actor.h"
#include "Engine/Unicol/Collide/ccollision_testraycylinder.h"
#include "Plane/ccollision_intersectfrontplanepoint.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Engine/Unicol/Collide/ccollision_testsegmentpolygon.h"
#include "Common/aiprofile.h"
#include "Common/box_contact.h"
#include "Common/legacy_collision_actor.h"
#include "Common/world.h"
#include "Collide/ccollision_testsegmentdisk.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Sched/sky_postscreenmessage.h"
#include "Common/ccollisionsetup_t.h"
#include "Io/debug_memory.h"
#include "Common/format.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"

/* CCOLLISION_TRACEACTORMOTION.CPP */

void CCollision_IntegrateGravityAndDrag(ActorMotion *motion) {
    CVector3 acceleration;
    f32 limit;
    f32 drag;
    f32 gravity;
    f32 dt;
    f32 halfDt;
    CCollisionInfo2_t *surface;

    if (motion->orientationActive != 0) {
        dt = g_frameElapsedTime * g_collisionMotionTimeScale;
        surface = motion->surface;
        if (dt != 0.0f) {
            drag = surface->AirFriction;
            drag *= g_collisionMotionDragScale;
            limit = g_collisionMotionMaximumDrag / dt;
            if (!(drag <= limit)) {
                drag = limit;
            }
            gravity = 0.0f;
            if (motion->candidateIndex != 0) {
                gravity = surface->GravityAcceleration;
            }
            if (drag == 0.0f) {
                acceleration.x = 0.0f;
                acceleration.y = gravity;
                acceleration.z = 0.0f;
            } else {
                acceleration.x = -motion->orientation.x * drag;
                acceleration.y = -motion->orientation.y * drag + gravity;
                acceleration.z = -motion->orientation.z * drag;
            }
            halfDt = dt * g_collisionMotionHalfStepScale;
            motion->end.x += (motion->orientation.x + acceleration.x * halfDt) * dt;
            motion->end.y += (motion->orientation.y + acceleration.y * halfDt) * dt;
            motion->end.z += (motion->orientation.z + acceleration.z * halfDt) * dt;
            motion->orientation.x += acceleration.x * dt;
            motion->orientation.y += acceleration.y * dt;
            motion->orientation.z += acceleration.z * dt;
        }
    }
}

s32 CCollision_TraceActorMotion(ActorMotion *object) {
    u32 *flags = &object->surface->dwFlags;
    f32 magnitude;
    f32 minimumX;
    f32 maximumX;
    f32 minimumY;
    f32 maximumY;
    f32 minimumZ;
    f32 maximumZ;

    CPlane_ResetContact(&object->collisionState);
    Graphu64_SubtractVectors(&object->velocity,
        &object->end,
        &object->start);
    magnitude = Gu_Sqrtf(
        (object->velocity.x * object->velocity.x) +
        (object->velocity.y * object->velocity.y) +
        (object->velocity.z * object->velocity.z));
    object->distance = magnitude;
    if ((magnitude == 0.0f) && (object->actorFlags == 0)) {
        return 0;
    }

    if (object->distance != 0.0f) {
        Graphu64_ScaleVector(&object->direction,
            &object->velocity,
            g_collisionMotionRetreatDistance / object->distance);
    } else {
        object->direction = object->velocity;
    }

    minimumX = object->end.x;
    if (!(minimumX <= object->start.x)) {
        minimumX = object->start.x;
    }
    object->boundsMin.x = minimumX;
    maximumX = object->end.x;
    if (!(object->start.x <= maximumX)) {
        maximumX = object->start.x;
    }
    object->boundsMax.x = maximumX;

    minimumY = object->end.y;
    if (!(minimumY <= object->start.y)) {
        minimumY = object->start.y;
    }
    object->boundsMin.y = minimumY;
    maximumY = object->end.y;
    if (!(object->start.y <= maximumY)) {
        maximumY = object->start.y;
    }
    object->boundsMax.y = maximumY;

    minimumZ = object->end.z;
    if (!(minimumZ <= object->start.z)) {
        minimumZ = object->start.z;
    }
    object->boundsMin.z = minimumZ;
    maximumZ = object->end.z;
    if (!(object->start.z <= maximumZ)) {
        maximumZ = object->start.z;
    }
    object->boundsMax.z = maximumZ;

    object->horizontalBounds[0] = object->boundsMin.x;
    object->horizontalBounds[2] = object->boundsMax.x;
    object->horizontalBounds[3] = object->boundsMax.z;
    object->horizontalBounds[1] = object->boundsMin.z;

    if (*flags & 0x200000) {
        CInstanceCollision_TraceInteractiveActors(object);
    }
    if (object->distance != 0.0f) {
        if (*flags & 0x10000) {
            InstCol_ProcessEntityContacts(object);
        }
        if (*flags & 0x4000) {
            CPolyCollision_TraceWorldElements(object);
        }
        if (*flags & 0x80000) {
            CPolyCollision_TraceCeilingTriangle(object);
        }
    }
    return object->collisionState != 0;
}

/* CCOLLISION_INTERSECTSEGMENTBOX.CPP */

/* Resolve contact response, updating translation and rotation along the contact normal. */
s32 CCollision_ApplyMotionResponse(void *actorStorage) {
    ActorMotion *a = actorStorage;
    CVector3 remaining;
    CVector3 slide;
    CVector3 bounce;
    CVector3 reflection;
    CVector3 projected;
    CVector3 gravity;
    CVector3 rotation;
    CCollisionInfo2_t *settings;
    CVector3 *delta;
    f32 step, highest, d, scale, damping, fraction;
    s32 i, active, type, timer;
    settings=a->surface;
    if (a->collisionState!=0) {
        Graphu64_NormalizeVec3(&a->normal.x);
        step=k_collisionRetreatStepBase_de*g_collisionRetreatStepScale;
        a->position=a->end;
        a->projectedOrientation=a->orientation;
        if (step<=a->distance && a->mode!=7) {
            f32 adjusted=a->blend-step/a->distance;
            a->blend=adjusted;
            Graphu64_InterpolateVector(&a->interpolated,adjusted,&a->start,&a->end);
        }
        if(a->grounded!=0 && a->collisionState==3) {
            highest=a->contacts[0].y;
            i=1;
            while(i<a->contactCount) { f32 point=a->contacts[i].y; if(!(highest<=point)) point=highest; highest=point; i++; }
            d=highest-a->start.y;
            if(0.0f<d && d<=g_collisionMaximumStepHeight) {
                a->interpolated=a->start; a->position=a->end; a->projectedOrientation=a->orientation;
                a->blend=0.0f;
                d+=g_collisionStepHeightClearance;
                a->interpolated.y+=d;
                a->position.y+=d;
                return 1;
            }
        }
        type=a->mode;
        if(type==6) { if(a->grounded==0)a->mode=3;else a->mode=2; }
        type=a->mode;
        if(type==3 && settings->BounceReturnEnergy<g_collisionMinimumBounceEnergy && a->distance<g_collisionMinimumBounceDistance) {
            s32 response=1;
            if(!(a->velocity.x*a->velocity.x+a->velocity.z*a->velocity.z<g_collisionMinimumSlideSpeedSquared))response=2;
            a->mode=response;
        }
        type=a->collisionState;
        if(type>=3)goto planar;
        if(type<=0)goto planar;
        {
            timer=a->verticalTicks;
            if(timer!=0){a->verticalTicks=timer-1;goto vertical;}
            goto zero_vertical;
        }
        planar:
        timer=a->horizontalTicks;
        if(timer!=0)a->horizontalTicks=timer-1;
        vertical:
        if(a->verticalTicks==0){
            zero_vertical:
            a->velocity.y=0.0f;
        }
        if(a->horizontalTicks==0){a->velocity.x=a->velocity.z=0.0f;} timer=a->horizontalTicks; active=0; if(timer!=0 || a->verticalTicks!=0)active=1;
        switch(a->mode) {
        case 7:
            if(a->orientationActive!=0)a->projectedOrientation=a->orientation;
            if(active!=0)a->position=a->end;
            if(a->transitionActive!=0) {
                if(a->collisionState==5){a->flags^=0x1000;CCollision_UpdateMaterialFlags(a,&a->collisionState);}
                if(a->collisionState==6){a->flags^=0x4000;CCollision_UpdateMaterialFlags(a,&a->collisionState);}
            }
            return 1;
        case 1: case 8:
            if(a->orientationActive!=0){a->projectedOrientation.x=0.0f;a->projectedOrientation.y=0.0f;a->projectedOrientation.z=0.0f;}
            if(active!=0)a->position=a->interpolated;
            return 0;
        case 3: {
                f32 remainingFraction;
                if(a->orientationActive!=0) {
                    Graphu64_ReflectVector(&rotation,&a->orientation,&a->normal,settings->BounceReturnEnergy);
                    a->projectedOrientation=rotation;
                    damping=a->damping;
                    Graphu64_ScaleVector(&a->projectedOrientation,&a->projectedOrientation,g_collisionBounceOrientationDampingBase-damping);
                }
                if(active==0)return 1;
                remainingFraction=a->blend;
                scale=g_collisionBounceRemainingFractionBase;
                remainingFraction=scale-remainingFraction;
                Graphu64_ScaleVector(&remaining,&a->velocity,remainingFraction);
                delta=&slide;
                Graphu64_ReflectVector(delta,&remaining,&a->normal,settings->BounceReturnEnergy);
                Graphu64_ScaleVector(delta,delta,scale-a->damping);
                Graphu64_AddVec3(&a->position,&a->interpolated,delta);
                return 1;
            }
        case 2: {
                f32 remainingFraction;
                if(a->orientationActive!=0) {
                    Graphu64_ProjectVectorOntoPlane(&rotation,&a->orientation,&a->normal);
                    a->projectedOrientation=rotation;
                    damping=a->damping;
                    Graphu64_ScaleVector(&a->projectedOrientation,&a->projectedOrientation,g_collisionSlideOrientationDampingBase-damping);
                }
                if(active==0)return 1;
                remainingFraction=a->blend;
                scale=g_collisionSlideRemainingFractionBase;
                remainingFraction=scale-remainingFraction;
                Graphu64_ScaleVector(&remaining,&a->velocity,remainingFraction);
                Graphu64_ProjectVectorOntoPlane(&bounce,&remaining,&a->normal);
                Graphu64_ScaleVector(&bounce,&bounce,scale-a->damping);
                Graphu64_AddVec3(&a->position,&a->interpolated,&bounce);
                Graphu64_ScaleVector(&gravity,&a->normal,k_collisionSurfaceOffsetScales[0]*g_collisionSurfaceGravityScale);
                Graphu64_AddVec3(&a->position,&a->position,&gravity);
                return 1;

            }
        case 4:
            if(a->orientationActive!=0) {rotation=Graphu64_ProjectVectorPreservingLength(&a->orientation,&a->normal);a->projectedOrientation=rotation;}
            if(active==0)return 1;
            fraction=a->blend;
            Graphu64_ScaleVector(&remaining,&a->velocity,g_collisionPreservedSlideFractionBase-fraction);
            bounce=Graphu64_ProjectVectorPreservingLength(&remaining,&a->normal);
            Graphu64_AddVec3(&a->position,&a->interpolated,&bounce);
            Graphu64_ScaleVector(&gravity,&a->normal,k_collisionSurfaceOffsetScales[0]*g_collisionSurfaceGravityScale);
            Graphu64_AddVec3(&a->position,&a->position,&gravity);
            return 1;

        case 5: {
                f32 remainingFraction;
                if(a->orientationActive!=0) {
                    Graphu64_ProjectVectorOntoPlane(&reflection,&a->orientation,&a->normal);
                    projected=Graphu64_ProjectVectorPreservingLength(&a->orientation,&a->normal);
                    Graphu64_InterpolateVector(&a->projectedOrientation,0.25f,&reflection,&projected);
                    damping=a->damping;
                    Graphu64_ScaleVector(&a->projectedOrientation,&a->projectedOrientation,g_collisionBlendedSlideDampingBase-damping);
                }
                if(active==0)return 1;
                remainingFraction=a->blend;
                scale=g_collisionBlendedSlideFractionBase;
                remainingFraction=scale-remainingFraction;
                Graphu64_ScaleVector(&remaining,&a->velocity,remainingFraction);
                Graphu64_ProjectVectorOntoPlane(&reflection,&remaining,&a->normal);
                projected=Graphu64_ProjectVectorPreservingLength(&remaining,&a->normal);
                Graphu64_InterpolateVector(&bounce,0.25f,&reflection,&projected);
                Graphu64_ScaleVector(&bounce,&bounce,scale-a->damping);
                Graphu64_AddVec3(&a->position,&a->interpolated,&bounce);
                Graphu64_ScaleVector(&gravity,&a->normal,k_collisionSurfaceOffsetScales[0]*g_collisionSurfaceGravityScale);
                Graphu64_AddVec3(&a->position,&a->position,&gravity);
                return 1;

            }
        case 6: default: return 0;
        }
    }
    return 0;
}

/* Tests a ray against an axis-aligned box: a ray starting inside the box hits at parameter 0; otherwise
 * each axis whose start and end differ gives the parameter where the ray reaches the box face it
 * approaches, and the first such hit nearer than the ray's current nearest hit whose point lies within the
 * face's other two extents is written out. Returns whether the box was hit. */

s32 CCollision_IntersectSegmentBox(Ray *ray, Box *box, f32 *out) {
    CVector3 hit;
    CVector3 *start;
    CVector3 *end;
    f32 t;

    start = &ray->start;
    end = &ray->end;
    if (box->max.x >= start->x && box->max.y >= start->y && box->max.z >= start->z && box->min.x <= start->x &&
        box->min.y <= start->y && box->min.z <= start->z) {
        *out = 0.0f;
        return 1;
    }
    if (start->x != end->x) {
        if (start->x < end->x) {
            t = (box->min.x - start->x) / (end->x - start->x);
        } else {
            t = (start->x - box->max.x) / (start->x - end->x);
        }
        if (t < ray->nearest) {
            hit.y = start->y + t * ray->dir.y;
            hit.z = start->z + t * ray->dir.z;
            if (box->min.y <= hit.y && hit.y <= box->max.y && box->min.z <= hit.z && hit.z <= box->max.z) {
                *out = t;
                return 1;
            }
        }
    }
    if (start->y != end->y) {
        if (start->y < end->y) {
            t = (box->min.y - start->y) / (end->y - start->y);
        } else {
            t = (start->y - box->max.y) / (start->y - end->y);
        }
        if (t < ray->nearest) {
            hit.x = start->x + t * ray->dir.x;
            hit.z = start->z + t * ray->dir.z;
            if (box->min.x <= hit.x && hit.x <= box->max.x && box->min.z <= hit.z && hit.z <= box->max.z) {
                *out = t;
                return 1;
            }
        }
    }
    if (start->z != end->z) {
        if (start->z < end->z) {
            t = (box->min.z - start->z) / (end->z - start->z);
        } else {
            t = (start->z - box->max.z) / (start->z - end->z);
        }
        if (t < ray->nearest) {
            hit.x = start->x + t * ray->dir.x;
            hit.y = start->y + t * ray->dir.y;
            if (box->min.x <= hit.x && hit.x <= box->max.x && box->min.y <= hit.y && hit.y <= box->max.y) {
                *out = t;
                return 1;
            }
        }
    }
    return 0;
}

/* Tests a ray's horizontal segment against a rectangle (min and max x/z): a start
 * point inside gives parameter 0; otherwise the crossing of the x edge facing the start is tried first and
 * then the z edge, each accepted when nearer than the ray's current nearest hit and landing within
 * the other axis's extent (using the ray's direction/0x64); the accepted parameter is stored and 1
 * is returned, 0 when the segment misses. */

s32 CCollision_IntersectSegmentRectangle(Ray *ray, CQuatern *rect, f32 *t) {
    CVector3 *start;
    CVector3 *end;
    f32 a;
    f32 b;
    f32 param;
    CVector3 hit;

    start = &ray->start;
    end = &ray->end;
    if (rect->z >= start->x && rect->w >= start->z && rect->x <= start->x && rect->y <= start->z) {
        *t = 0.0f;
        return 1;
    }
    a = start->x;
    b = end->x;
    if (a != b) {
        if (a < b) {
            param = (rect->x - a) / (b - a);
        } else {
            param = (a - rect->z) / (a - b);
        }
        if (param < ray->nearest) {
            hit.z = start->z + param * ray->dir.z;
            if (rect->y <= hit.z && hit.z <= rect->w) {
                *t = param;
                return 1;
            }
        }
    }
    a = start->z;
    b = end->z;
    if (a == b) {
        return 0;
    }
    if (a < b) {
        param = (rect->y - a) / (b - a);
    } else {
        param = (a - rect->w) / (a - b);
    }
    if (!(param < ray->nearest)) {
        return 0;
    }
    hit.x = start->x + param * ray->dir.x;
    if (rect->x <= hit.x && hit.x <= rect->z) {
        *t = param;
        return 1;
    }
    return 0;
}



/* CCOLLISION_TESTOFFSETPOLYGON.CPP */

/* Tests a swept sphere against a polygon: shifts the ray from its start to its end back along the polygon normal by
 * the radius (plus an optional offset), intersects the shifted ray with the polygon's plane through
 * CCollision_IntersectFrontPlaneFraction under the same acceptance rules as CCollision_TestSegmentPolygon, requires the shifted hit point to pass
 * Plane_TestPointNearPolygon at that radius, then places the hit on the unshifted ray and optionally keeps the polygon
 * as the ray's nearest hit.
 */

static inline s32 accepts(CapsuleSweep *ray, Polygon *poly) {
    if (poly->t <= 0.0f) {
        if (poly->kind == 7) {
            return 0;
        }
        if ((u32)(poly->type - 5) < 2) {
            return 0;
        }
        if (poly->t * ray->slack < -(g_collisionSlackThreshold * g_collisionSlackThresholdFactors_de[0])) {
            return 0;
        }
    }
    if (poly->t >= ray->nearest.t) {
        return 0;
    }
    return 1;
}

s32 CCollision_TestOffsetPolygon(CapsuleSweep *ray, CVector3 *offset, f32 radius, Polygon *poly, s32 keep) {
    CVector3 start;
    CVector3 end;
    CVector3 shift;
    CVector3 hit;

    if (offset != 0) {
        Graphu64_ScaleVector(&shift, &poly->normal, -radius);
        Graphu64_AddVec3(&shift, &shift, offset);
    } else {
        shift.x = 0.0f;
        shift.y = 0.0f;
        shift.z = 0.0f;
    }
    Graphu64_AddVec3(&start, &ray->start, &shift);
    Graphu64_AddVec3(&end, &ray->end, &shift);
    if (CCollision_IntersectFrontPlaneFraction(poly, &start, &end, &poly->t) == 0) {
        return 0;
    }
    if (accepts(ray, poly) == 0) {
        return 0;
    }
    Graphu64_InterpolateVector(&hit, poly->t, &start, &end);
    if (Plane_TestPointNearPolygon(poly, &hit, radius) == 0) {
        return 0;
    }
    Graphu64_InterpolateVector(&poly->hit, poly->t, &ray->start, &ray->end);
    if (keep != 0) {
        ray->nearest = *poly;
    }
    return 1;
}

/* CCOLLISION_TESTRAYCYLINDER.CPP */

/* Tests a ray against a vertical cylinder: projects the center onto the ray's horizontal direction from 0x44,
 * finds the entry parameter from the radius, accepts it under the same rules as CCollision_TestSegmentPolygon, places the
 * hit with Graphu64_InterpolateVector and optionally rejects hits above the top or below the bottom; when kept, the
 * polygon record takes the hit as its point with a horizontal normal away from the center and becomes the
 * ray's nearest hit.
 */

static inline s32 accepts_ccollision_testraycylinder(RayCCollisionTestRayCylinder *ray, PolygonCCollisionTestRayCylinder *poly) {
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
    if (accepts_ccollision_testraycylinder(ray, poly) != 0) {
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

/* Fills a sweep range: its count, low and high bounds and extra value, plus a limit that is the larger
   bound plus the pooled margin g_collisionCylinderRangeMargin. */

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

/* CCOLLISION_TESTSEGMENTPOLYGON.CPP */

/* Tests a ray against a polygon: intersects the ray from its start to its end with the polygon's plane through
 * CCollision_IntersectFrontPlaneFraction and accepts a parameter nearer than the ray's current nearest hit, also allowing a slightly negative
 * one (above -g_collisionSlackThreshold * g_collisionSegmentPolygonSlackFactor scaled by the ray's slack factor) except for kind 7 and types 5 and
 * 6; the hit point is then placed with Graphu64_InterpolateVector and must lie inside the polygon (CCollision_IsPointInsidePolygon). On a
 * hit the polygon record is optionally kept as the ray's nearest hit at 0xB0. */









extern s32 CCollision_IntersectFrontPlaneFraction(void *poly, void *start, void *segmentEnd, f32 *outputFraction);

extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);

struct Polygon;

static inline s32 accepts_ccollision_testsegmentpolygon(CapsuleSweep *ray, PolygonCCollisionTestSegmentPolygon *poly) {
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

/** Copy the polygon's normal into the contact's contact vector. */
void CCollision_CopyPolygonNormal(void *contactStorage, void *polygonStorage) {
    CollisionPolygonNormalView *polygon = polygonStorage;
    CollisionContactVectorView *contact = contactStorage;
    contact->contactVector = polygon->normal;
}

s32 CCollision_TestSegmentPolygon(CapsuleSweep *ray, PolygonCCollisionTestSegmentPolygon *poly, s32 keep) {
    if (CCollision_IntersectFrontPlaneFraction(poly, &ray->start, &ray->end, &poly->t) == 0) {
        return 0;
    }
    if (accepts_ccollision_testsegmentpolygon(ray, poly) == 0) {
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

/* CCOLLISION_TESTSEGMENTDISK.CPP */

/* Tests a ray against a polygon with a radius: intersects the ray from its start to its end with the polygon's plane
 * through CCollision_IntersectFrontPlaneFraction and accepts a parameter nearer than the ray's nearest hit, also allowing a slightly
 * negative one (above -g_collisionSlackThreshold * g_collisionSegmentPolygonSlackFactor[1] scaled by the ray's slack factor) except for kind 7 and
 * types 5 and 6; the hit point is then placed with Graphu64_InterpolateVector and tested against the polygon with the
 * given point and radius through CCollision_IsPointInsideDisk. On a hit the polygon record is optionally kept as the ray's
 * nearest hit. */

static inline s32 accepts_ccollision_testsegmentdisk(CapsuleSweep *ray, PolygonCCollisionTestSegmentPolygon *poly) {
    if (poly->t <= 0.0f) {
        if (poly->kind == 7) {
            return 0;
        }
        if ((u32)(poly->type - 5) < 2) {
            return 0;
        }
        if (poly->t * ray->slack < -(g_collisionSlackThreshold * g_collisionSegmentDiskSlackFactor)) {
            return 0;
        }
    }
    if (poly->t >= ray->nearest.t) {
        return 0;
    }
    return 1;
}




s32 CCollision_TestSegmentDisk(CapsuleSweep *ray, PolygonCCollisionTestSegmentPolygon *poly, CVector3 *point, f32 radius, s32 keep) {
    if (CCollision_IntersectFrontPlaneFraction(poly, &ray->start, &ray->end, &poly->t) == 0) {
        return 0;
    }
    if (accepts_ccollision_testsegmentdisk(ray, poly) == 0) {
        return 0;
    }
    Graphu64_InterpolateVector(&poly->hit, poly->t, &ray->start, &ray->end);
    if (CCollision_IsPointInsideDisk(poly, point, radius, &poly->hit) == 0) {
        return 0;
    }
    if (keep != 0) {
        ray->nearest = *poly;
    }
    return 1;
}

void CCollision_ClearResultFlags(void)
{
  g_collisionCurrentActor->contactValue = (g_collisionCurrentActor->typeFC = (g_collisionCurrentActor->instanceValueC4 = (g_collisionCurrentActor->contactFlagsB0 = (g_collisionCurrentActor->contactFlags9C = (s32)(g_collisionCurrentActor->instance88 = (g_collisionCurrentActor->instance0 = 0))))));
}

void CCollision_UpdateSurfaceResponseFlags(ActorMotion *motion, MotionContactResult *contact) {
    s32 contactFlags;
    s32 clearedFlags;

    clearedFlags = motion->flags & ~0xE00;
    motion->flags = clearedFlags;
    contactFlags = contact->flags;
    if (contactFlags & 0x20000000) {
        motion->flags = clearedFlags | 0x200;
        return;
    }
    if (contactFlags & 0x40000000) {
        motion->flags = clearedFlags | 0x400;
        return;
    }
    if (contactFlags < 0) {
        motion->flags = clearedFlags | 0x800;
    }
}

void CCollision_UpdateMaterialFlags(ActorMotion *motion, MotionContactResult *contact) {
    s32 material;
    s32 currentMotionFlags;
    s32 flags;
    s32 baseMotionFlags;

    flags = motion->flags;
    if (flags & 0x1000) {
        motion->flags = flags & ~0x2000;
    }
    currentMotionFlags = motion->flags;
    baseMotionFlags = currentMotionFlags & 0xFFFC7FFF;
    motion->flags = baseMotionFlags;
    if (currentMotionFlags & 0x7000) {
        material = contact->material;
        switch (material) {
        case 8:
            motion->flags = baseMotionFlags | 0x10000;
            return;
        case 7:
            motion->flags = baseMotionFlags | 0x8000;
            break;
        }
    }
}

void CCollision_UpdateModelSurfaceFlags(void *motionStorage, u16 *surfaceKey)
{
    char *o = (char *) motionStorage;
    s32 initialMotionFlags;
    s32 currentMotionFlags;
    s32 updatedMotionFlags;
    void *surfaceRecord;
    initialMotionFlags = ((Shared_CollisionMoveFrame *)o)->motionFlags;
    if (initialMotionFlags & 0x1000)
    {
        ((Shared_CollisionMoveFrame *)o)->motionFlags = initialMotionFlags & (~0x2000);
    }
    currentMotionFlags = ((Shared_CollisionMoveFrame *)o)->motionFlags;
    ((Shared_CollisionMoveFrame *)o)->motionFlags = currentMotionFlags & 0xFFFC7FFF;
    if (currentMotionFlags & 0x7000)
    {
        surfaceRecord = Scene_GetModelRecordByIndexPointer(&g_world, surfaceKey);
        if (surfaceRecord != 0)
        {
            if ((((ModelBlend *)surfaceRecord)->collisionFlags) & 0x400000)
            {
                ;
                ((Shared_CollisionMoveFrame *)o)->motionFlags = (((Shared_CollisionMoveFrame *)o)->motionFlags) | 0x8000;
            }
            else
            if ((((ModelBlend *)surfaceRecord)->materialFlags) & 0x80)
            {
                updatedMotionFlags = (((Shared_CollisionMoveFrame *)o)->motionFlags) | 0x10000;
                ((Shared_CollisionMoveFrame *)o)->motionFlags = updatedMotionFlags;
            }
        }
    }
}

s32 CCollision_IsNearerContact(BoxContactRay *ray, BoxContactPolygon *polygon) {
    f32 hitT;
    s32 isNearer;

    hitT = polygon->t;
    if (hitT <= 0.0f) {
        if (polygon->kind == 7) {
            return 0;
        }
        if ((u32) (polygon->type - 5) < 2) {
            return 0;
        }
        if ((hitT * ray->slack) < -(g_collisionSlackThreshold * g_collisionContactSlackFactor)) {
            return 0;
        }
    }
    isNearer = 0;
    {
        f32 polygonFraction = polygon->t;
        if (!(ray->nearest.t <= polygonFraction)) {
            isNearer = 1;
        }
    }
    return isNearer;
}

/* COLLIDE.CPP */

/* Points the active collision state at g_currentActorInstance and fills the collision infos from the setup table
 * g_collisionSetupTableResource (the KUSEG alias of g_collisionSetupTable). */

void CCollision_Initialize(void) {
    g_collisionCurrentActor = &g_currentActorInstance;
    CCollision_ApplySetupTable(g_collisionSetupTableResource);
}

/** Reset the selected fields of the current global record. */
void CCollision_ResetResult(void) {
    Reusable *record = g_collisionCurrentActor;
    record->reservedWord = 0;
    record->collisionCounter = -1;
    record->reservedWord2 = 0;
    record->reservedWord3 = 0;
    record->reservedWord4 = 0;
    record->reservedWord5 = 0;
    record->reservedWord6 = 0;
}

/* Fills every collision info named by a collision setup table from its row, resetting the
 * active collision state g_collisionCurrentActor before each one; the table ends at a row without info. */
void CCollision_ApplySetupTable(CCollisionSetup_t *setupTable)
{
    CCollisionSetup_t *setup = setupTable;
    s32 counter = -1;

    if (setup->m_pCollInfo != 0) {
        do {
            CCollisionInfo2_t *info = setup->m_pCollInfo;

            ((Reusable *)g_collisionCurrentActor)->reservedWord = 0;
            ((Reusable *)g_collisionCurrentActor)->collisionCounter = counter;
            ((Reusable *)g_collisionCurrentActor)->reservedWord2 = 0;
            ((Reusable *)g_collisionCurrentActor)->reservedWord3 = 0;
            ((Reusable *)g_collisionCurrentActor)->reservedWord4 = 0;
            ((Reusable *)g_collisionCurrentActor)->reservedWord5 = 0;
            ((Reusable *)g_collisionCurrentActor)->reservedWord6 = 0;

            info->dwFlags = setup->m_dwFlags;
            info->InstanceBehavior = setup->m_InstanceBehavior;
            info->WallBehavior = setup->m_WallBehavior;
            info->GroundBehavior = setup->m_GroundBehavior;
            info->GravityAcceleration = setup->m_GravityAcceleration;
            info->BounceReturnEnergy = setup->m_BounceReturnEnergy;
            info->GroundFriction = setup->m_GroundFriction;
            info->AirFriction = setup->m_AirFriction;
            info->WaterFriction = setup->m_WaterFriction;
            setup += 1;
        } while (setup->m_pCollInfo != 0);
    }
}

/* CCOLLISION_INTEGRATEGRAVITYANDDRAG_DATA.CPP */



/* CCOLLISION_SETSWEEPRANGE_DATA.CPP */



/* CCOLLISION_TESTSEGMENTDISK_DATA.CPP */



/* CCOLLISION_INTERSECTSEGMENTBOX_DATA.CPP */
#if defined(VERSION_DE)
const f32 g_collisionSegmentBoxLeadingTolerance = 0.0199999996f;
#endif
#if defined(VERSION_EU)
const f32 g_collisionSegmentBoxLeadingTolerance = 0.0199999996f;
#endif
#if defined(VERSION_EU_X)
const f32 g_collisionSegmentBoxLeadingTolerance = 0.0199999996f;
#endif
#if defined(VERSION_US)
const f32 g_collisionSegmentBoxLeadingTolerance = 0.0199999996f;
#endif
#if defined(VERSION_US_REV1)
const f32 g_collisionSegmentBoxLeadingTolerance = 0.0199999996f;
#endif
#if defined(VERSION_DE)
const f32 g_collisionSegmentBoxTrailingTolerance = 0.0199999996f;
#endif
#if defined(VERSION_EU)
const f32 g_collisionSegmentBoxTrailingTolerance = 0.0199999996f;
#endif
#if defined(VERSION_EU_X)
const f32 g_collisionSegmentBoxTrailingTolerance = 0.0199999996f;
#endif
#if defined(VERSION_US)
const f32 g_collisionSegmentBoxTrailingTolerance = 0.0199999996f;
#endif
#if defined(VERSION_US_REV1)
const f32 g_collisionSegmentBoxTrailingTolerance = 0.0199999996f;
#endif

/* CCOLLISION_TESTSEGMENTPOLYGON_DATA.CPP */



/* GAMEOBJECT_MOVETOXZKEEPHEIGHT_DATA.CPP */

#if defined(VERSION_DE)
struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 retainedFloatAndInstructionWords[12];
} g_gameObjectMoveToXzKeepHeightRetainedWords __attribute__((aligned(4))) = {
    0,
    0,
    0,
    0,
    -1,
    { 0x40, 0x40, 0x0, 0x0, 0x10, 0x62, 0x0, 0x3, 0x3c, 0x3, 0xa4, 0x60 }
};
typedef char g_gameObjectMoveToXzKeepHeightRetainedWordsSizeCheck[(sizeof(g_gameObjectMoveToXzKeepHeightRetainedWords) == 32) ? 1 : -1];
#endif

#if defined(VERSION_US_REV1)
extern struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 retainedFloatWords[12];
} g_gameObjectMoveToXzKeepHeightRetainedWords __attribute__((aligned(4)));
typedef char g_gameObjectMoveToXzKeepHeightRetainedWordsSizeCheck[(sizeof(g_gameObjectMoveToXzKeepHeightRetainedWords) == 32) ? 1 : -1];
#endif

/* G_COLLIDERETAINEDRECORDWORDS.CPP */

#if defined(VERSION_US_REV1)
extern struct {
    u8 retainedRecordWords[4];
} g_collideRetainedRecordWords __attribute__((aligned(4)));
#endif

/* OVERLAY_SEVEN_FLOAT_ONE_POINT_FIVE_SIX_THREE.CPP */

#if defined(VERSION_US_REV1)
extern struct {
    u8 retainedFloatWord[4];
} g_weaponSlotNearQuarterTurnRadians __attribute__((aligned(4)));
#endif

/* Retained data for this translation unit. */

const float k_CcollisionIntersectsegmentbox[11] = {
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 10.24f, 10.24f, 1.0f, 10.24f,
};

const float k_CcollisionIntegrategravityanddrag[11] = {
    0.06666667f, 15.0f, 1.0f, 0.5f, 1.0f, 10.24f,
    30.72f, 0.2048f, 1.0f, 4.096f, 1.0485761f,
};

const float k_CcollisionSetsweeprange[1] = {
    1.024f,
};

const float k_CcollisionTestsegmentdisk[3] = {
    10.24f, 10.24f, 10.24f,
};

const float k_CcollisionTestsegmentpolygon[1] = {
    0.1f,
};
