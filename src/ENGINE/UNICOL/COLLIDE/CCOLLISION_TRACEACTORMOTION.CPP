#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/MOTION_STEP.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OWNERRECAT8V2.H"
#include "COMMON/RENDERSORTRECORD.H"
#include "COMMON/DESCRIPTORRECAT29.H"
#include "ANIM/CPLANE_RESETCONTACT.H"
#include "ENGINE/UNICOL/COLLIDE.H"

/* 8023A284_21.CPP */
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

/* 8023CFD0.CPP */
extern void CInstanceCollision_TraceInteractiveActors(void *obj);
extern void CPolyCollision_TraceWorldElements(void *ray);
extern void CPolyCollision_TraceCeilingTriangle(void *actor);

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
