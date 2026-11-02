#include "include_asm.h"
#include "COMMON/DESCRIPTORRECAT29.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/MOTION_STEP.H"
#include "COMMON/OUTPUT.H"
#include "COMMON/GRAPHICS_MATRIX_AND_VECTOR_MATH.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "ENGINE/UNICOL/COLLIDE.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"

/* 8023A284_26.CPP */
extern void Graphu64_InterpolateVector(CVector3 *,f32,void *,void *);

/* Resolve contact response, updating translation and rotation along the contact normal. */
s32 CCollision_ApplyMotionResponse(ActorMotion *a) {
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

/* Tests a ray's horizontal segment against a rectangle (min x/z at 0 and 4, max x/z at 8 and 12): a start
 * point inside gives parameter 0; otherwise the crossing of the x edge facing the start is tried first and
 * then the z edge, each accepted when nearer than the ray's current nearest hit at 0x17C and landing within
 * the other axis's extent (using the ray's direction at 0x5C/0x64); the accepted parameter is stored and 1
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

const float k_CcollisionIntersectsegmentboxEncodedWordsBlock1[8] = {
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 10.24f,
};

/* 800C8710_5.CPP */
#if !(defined(VERSION_US_REV1))
const float k_CcollisionIntersectsegmentboxEncodedWords[3] = {
    10.24f, 1.0f, 10.24f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ccollisionIntersectsegmentboxEncodedWordsBlock3UsRev1.c */
const float k_CcollisionIntersectsegmentboxEncodedWordsBlock3[1] = {
    10.24f,
};

/* ROM-grounded data: src/ccollisionIntersectsegmentboxEncodedWordsBlock2UsRev1.c */
const float k_CcollisionIntersectsegmentboxEncodedWordsBlock2[2] = {
    1.0f, 10.24f,
};
#endif

/* 800C878C.CPP */
