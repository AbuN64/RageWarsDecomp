#include "include_asm.h"
#include "COMMON/GROUP.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/LEGACY_COLLISION_ACTOR.H"
#include "COMMON/MOTION_STEP.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "CAMERA/COLLISION_SWEEP_VIEWS.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"

/* 80243A80.CPP */
void CCollision_StoreContactResult(void *);

void CCollision_ProjectSegmentOntoSurface(void *, void *);

void CCollision_ResetContactNormal(void *);

void CCollision_ClearResultFlags(void *);

void CCollision_UpdateSurfaceResponseFlags(ActorMotion *, MotionContactResult *);

void CCollision_UpdateMaterialFlags(ActorMotion *, MotionContactResult *);

void CCollision_UpdateModelSurfaceFlags(void *, u16 *);

f32 CCollision_GetContactYaw(f32 *);

f32 InstHdr_GetActorReach(void *);

extern void Graphu64_EaseValueToward(f32 *value, f32 target, f32 rate);

f32 Graphu64_GetTrianglePlaneHeight(void *, f32, f32);

f32 Region_GetPolygonHeight(void *, f32, f32);

void * Scene_ResolveFloorPolygon(void *, CVector3 *);

s32 CCollision_IntegrateGravityAndDrag();

                     /* extern */

                         /* extern */
extern UnicolCurrentActor *g_collisionCurrentActor;

extern s32 g_particleCollisionProbeResult;

extern s32 g_collisionNoDetachSettingsSecond;

extern s32 g_supportingPlatformCollisionQuery;

extern float k_collisionUpNormalY_de;

/* Moves an actor through collision queries and updates its contact flags and resolved position. */
/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x2d0, 0x2d4, 0x2d8, 0x2dc, 0x2e0, 0x2e4, 0x2e8, 0x2f8, 0x2fc, 0x300, 0x304], gap at: 0x2ec. */
typedef Shared_CollisionMoveFrame UnicolMotionFrame;

typedef CVector3 UnicolPosition;

extern void CCollision_SetUniformSweepExtent(void *actorMotion, f32 extent);

s32 Unicol_MoveActorWithCollision(UnicolActor *actor, UnicolPosition pos, u32 *motionSettings) {
    s32 CCollision_ApplyMotionResponse();
    UnicolMotionFrame frame;
    f32 headingCosine;
    f32 surfaceCeilingHeight;
    f32 high;
    f32 count;
    f32 actorReach;
    f32 headingSine;
    f32 groundSeparation;
    s32 collisionFound;
    s32 flags;
    s32 motionContinuation;
    s32 repeatFloorProbe;
    s32 remainingIterations;
    s32 collisionCount;
    s32 unusedMovementState;
    s32 groundFollowEnabled;
    s32 peakMoveCount;
    s32 horizontalResponseTicks;
    s32 verticalResponseTicks;
    u16 *surface;
    u32 preProbeFlags;
    u32 settingsFlags;
    u32 floorProbeBaseFlags;
    u32 attachmentFlags;
    u32 loopMask;
    f32 dropDistance;
    UnicolActor *attachedActor;
    s32 collisionOne;
    f32 hitY;
    f32 actorY;
    f32 savedY;

    CCollision_ClearResultFlags(&frame.actor);
    __builtin_memcpy(&g_collisionCurrentActor->x, &actor->room, 12);
    actor->flags = (u32) (actor->flags & ~0x18);
    frame.actor = actor;
    motionContinuation = 0;
    if (actor->type == 1) {
        motionContinuation = (u32) motionContinuation < (actor->status & 0x300000);
    }
    frame.motionContinuation = motionContinuation;
    actorReach = InstHdr_GetActorReach(actor);
    count = Gobjinst_GetActorRadius(actor);
    high = Gobjinst_GetActorHeight(actor);
    CCollision_SetSweepRange(&frame.actor, actorReach, count, high, InstHdr_GetActorBaseOffset(actor));
    *(UnicolPosition *)&frame.startX = *(UnicolPosition *)&actor->x;
    __builtin_memcpy(&frame.targetX, &pos, 12);
    __builtin_memcpy(&frame.room, &actor->room, 12);
    frame.surface = actor->collision;
    groundFollowEnabled = 0;
    if ((*motionSettings & 0x200) && (actor->velY <= 0.0f)) {
        groundFollowEnabled = 1;
    }
    frame.groundFollowEnabled = groundFollowEnabled;
    frame.motionSettingsBit1 = ((u32) *motionSettings >> 1) & 1;
    frame.actorFlagsBit2Clear = (((u32) actor->flags >> 2) ^ 1) & 1;
    frame.traceEnabled = 1;
    frame.motionFlags = actor->flags;
    frame.scaledSweepReach = frame.sweepReach * k_collisionHeightMarginScale_de;
    frame.motionSettingsBit19 = ((u32) *motionSettings >> 19) & 1;
    frame.motionSettings = motionSettings;
    CCollision_IntegrateGravityAndDrag(&frame.actor);
    if ((frame.groundFollowEnabled != 0) && (frame.motionFlags & 7) && !(frame.motionFlags & 0x2000)) {
        __builtin_memcpy(&frame.previousContactX, &actor->contactX, 12);
        frame.groundProbeX = actor->x;
        frame.groundProbeY = actor->groundY;
        frame.groundProbeZ = actor->z;
        CCollision_ProjectSegmentOntoSurface(&frame.actor, &frame.segmentProjection);
    }
    if ((frame.motionContinuation != 0) || (frame.startX != frame.targetX) || (frame.startY != frame.targetY) || (unusedMovementState = 0, (frame.startZ != frame.targetZ))) {
        peakMoveCount = ++g_collisionMovementCount;
        if (peakMoveCount < g_collisionPeakMovementCount) {
            peakMoveCount = g_collisionPeakMovementCount;
        }
        g_collisionPeakMovementCount = peakMoveCount;
        if ((motionSettings != &g_supportingPlatformCollisionQuery) && (motionSettings != &g_collisionNoDetachSettingsSecond) && (motionSettings != &g_particleCollisionProbeResult) && (motionSettings != &g_collisionSurfaceExcludedFromTrace)) {
            actor->attached = 0;
            frame.motionFlags &= ~0x7B;
        }
        frame.motionFlags &= ~0x80;
        if (actor->type == 1) {
            frame.heading = actor->angle;
        } else {
            frame.heading = 0.0f;
        }
        headingSine = Gu_Sinf(frame.heading);
        headingCosine = Math_Cosf(frame.heading);
        frame.motionFlags &= ~0x2000;
        settingsFlags = *motionSettings;
        if (settingsFlags & 4) {
            remainingIterations = 1;
        } else if (settingsFlags & 0x800) {
            remainingIterations = 3;
        } else {
            if (actor->type == 1) remainingIterations = 4;
            else remainingIterations = 1;
        }
        horizontalResponseTicks = remainingIterations;
        if (remainingIterations >= 3) {
            horizontalResponseTicks = 2;
        }
        frame.horizontalResponseTicks = horizontalResponseTicks;
        verticalResponseTicks = remainingIterations + 1;
        if (verticalResponseTicks >= 4) {
            verticalResponseTicks = 3;
        }
        frame.verticalResponseTicks = verticalResponseTicks;
        CCollision_ResetContactNormal(&frame.actor);
        collisionCount = 0;
        loopMask = 0x80000;
        collisionOne = 1;
loop_34:
        if (*motionSettings & loopMask) {
            frame.surface = Scene_ResolveFloorPolygon(frame.surface, &frame.targetX);
        }
        collisionFound = CCollision_TraceActorMotion((s8 *) &frame.actor);
        motionContinuation = 0;
        if (collisionFound != 0) {
            if (frame.hitType != collisionOne) {
                if (frame.hitType == 4) {
                    if (((frame.contactX * -headingSine) + (frame.contactZ * -headingCosine)) < k_collisionWallFacingDotLimit_de) {
                        frame.motionFlags |= 0x80;
                        CCollision_UpdateSurfaceResponseFlags(&frame.actor, &frame.hitType);
                    }
                } else {
                    goto block_42;
                }
            } else {
                frame.motionSettingsBit1 = 0;
block_42:
                frame.motionFlags &= ~0x80;
            }
            CCollision_StoreContactResult(&frame.actor);
            collisionCount += 1;
            motionContinuation = CCollision_ApplyMotionResponse(&frame.actor);
            __builtin_memcpy(&frame.startX, &frame.resultX, 12);
            __builtin_memcpy(&frame.targetX, &frame.resultTargetX, 12);
            __builtin_memcpy(&frame.room, &frame.resultRoom, 12);
        } else {
            __builtin_memcpy(&frame.startX, &frame.targetX, 12);
        }
        remainingIterations -= 1;
        if (motionContinuation == 0) {
        } else if (remainingIterations != 0) {
            goto loop_34;
        }
        __builtin_memcpy(&actor->x, &frame.startX, 12);
        __builtin_memcpy(&actor->room, &frame.room, 12);
        frame.motionFlags &= ~4;
        if (*motionSettings & 0x40000) {
            __builtin_memcpy(&frame.targetX, &frame.startX, 12);
            frame.traceEnabled = 0;
            frame.horizontalResponseTicks = 0;
            frame.verticalResponseTicks = 0;
            savedY = frame.targetY;
            dropDistance = k_collisionFloorProbeDrop_de;
            frame.targetY = savedY - dropDistance;
            __builtin_memcpy(&frame.probeFlags, &g_playerCollisionProbe, sizeof(g_playerCollisionProbe));
            frame.motionSettings = &frame.probeFlags;
            floorProbeBaseFlags = frame.probeFlags & 0xFFE7FFF7;
            frame.probeFlags = floorProbeBaseFlags;
            frame.probeFlags = floorProbeBaseFlags | (*motionSettings & 0x180008);
            frame.motionSettingsBit19 = 0;
            CCollision_ResetContactNormal(&frame.actor);
            actor->contactX = 0.0f;
            actor->contactZ = 0.0f;
            actor->contactBits = k_collisionUpNormalY_de;
            actor->groundY = (f32) (actor->y - dropDistance);
loop_49:
            if (CCollision_TraceActorMotion((s8 *) &frame.actor) != 0) {
                if (frame.probeHitType == 7) {
                    frame.groundFollowEnabled = 0;
                }
                CCollision_ApplyMotionResponse(&frame.actor);
                repeatFloorProbe = 0;
                actor->groundY = frame.resultY;
                __builtin_memcpy(&actor->contactX, &frame.contactX, 12);
                actorY = actor->y;
                hitY = frame.resultY;
                groundSeparation = actorY - hitY;
                if ((frame.groundFollowEnabled != 0) && (groundSeparation < k_collisionGroundSnapDistance_de)) {
                    frame.groundFollowEnabled = 0;
                    actor->velY = 0.0f;
                    groundSeparation = actor->velY;
                    actor->y = hitY;
                }
                if ((actor->velY <= 0.0f) && (groundSeparation < k_collisionGroundContactDistance_de)) {
                    if (frame.hitType == 5) {
                        frame.motionFlags |= 0x2004;
                        CCollision_UpdateMaterialFlags(&frame.actor, &frame.hitType);
                        repeatFloorProbe = 1;
                        *frame.motionSettings &= ~8;
                    } else {
                        if (frame.hitType < 5) goto no_attach;
                        if (frame.hitType >= 10) goto no_attach;
                        if (frame.hitType < 7) goto no_attach;
                        if (frame.hitActor->type != 1) goto no_attach;
                        attachedActor = frame.hitActor;
                        actor->attached = attachedActor;
                        flags = attachedActor->flags;
                        attachedActor->flags = (s32) (flags | 0x20);
                        if (frame.motionContinuation != 0) {
                            attachedActor->flags = (s32) (flags | 0x60);
                        }
                        attachmentFlags = (frame.motionFlags & ~3) | 2;
                        goto attach_done;
no_attach:
                        attachmentFlags = frame.motionFlags | 4;
attach_done:
                        frame.motionFlags = attachmentFlags;
                    }
                }
                if (repeatFloorProbe != 0) {
                    __builtin_memcpy(&frame.startX, &frame.resultX, 12);
                    goto block_71;
                }
            } else {
                repeatFloorProbe = 0;
block_71:
                if (repeatFloorProbe == 0) {

                } else {
                    goto loop_49;
                }
            }
        }
        preProbeFlags = frame.motionFlags;
        frame.motionFlags = preProbeFlags & ~0x100;
        if ((frame.motionSettingsBit1 != 0) || (preProbeFlags & 0x80)) {
            __builtin_memcpy(&frame.startX, &actor->x, 12);
            __builtin_memcpy(&frame.targetX, &actor->x, 12);
            frame.traceEnabled = 0;
            frame.horizontalResponseTicks = 0;
            frame.verticalResponseTicks = 0;
            frame.motionSettings = &g_playerCollisionProbe.flags;
            frame.targetX -= headingSine * k_collisionWallProbeReach_de;
            frame.targetZ -= headingCosine * k_collisionWallProbeReach_de;
            CCollision_ResetContactNormal(&frame.actor);
            if ((CCollision_TraceActorMotion((s8 *) &frame.actor) != 0) && (frame.hitType == 4)) {
                if (frame.motionSettingsBit1 != 0) {
                    CCollision_ApplyMotionResponse(&frame.actor);
                    actor->x = frame.resultX;
                    actor->z = frame.resultZ;
                    frame.motionFlags |= 0x100;
                    CCollision_UpdateSurfaceResponseFlags(&frame.actor, &frame.hitType);
                    if (actor->type == 1) {
                        Graphu64_EaseValueToward(&frame.heading, frame.heading - Graphu64_GetWrappedDifference(frame.heading, CCollision_GetContactYaw((f32 *) &frame.hitType)), 0.9f);
                        actor->angle = frame.heading;
                    }
                }
            } else {
                frame.motionFlags &= ~0x80;
            }
        }
        if (*motionSettings & 0x80000) {
            surface = Scene_ResolveFloorPolygon(frame.surface, &actor->x);
            frame.motionFlags &= ~0x5000;
            if ((surface != 0) && ((((UnicolSurfaceRecord *)surface)->flags & 0x41) == 0x41) && (Region_GetPolygonHeight(surface, actor->x, actor->z) <= actor->y)) {
                surfaceCeilingHeight = Graphu64_GetTrianglePlaneHeight(surface, actor->x, actor->z);
                if (actor->y <= surfaceCeilingHeight) {
                    frame.motionFlags |= 0x4000;
                }
                surfaceCeilingHeight += frame.scaledSweepReach;
                if (actor->y <= surfaceCeilingHeight) {
                    frame.motionFlags |= 0x1000;
                }
                CCollision_UpdateModelSurfaceFlags(&frame.actor, surface);
            }
            actor->collision = surface;
        }
        actor->flags = frame.motionFlags;
        return collisionCount;
    }
    return 0;
}

s32 CCollision_SweepPoint(char *actorStorage, CVector3 startPosition, CVector3 desired, s32 motionSettings) {
    extern s32 CCollision_ApplyMotionResponse(void *actorStorage);
    CollisionSweepWork work;
    VectorPair vectors;
    char *object = actorStorage;
    char *out;
    s32 count;
    s32 active;
    s32 result;
    s32 next;
    s32 maximum;
    s32 flags;

    CCollision_SetUniformSweepExtent(work.data, 0.0f);
    out = work.data;
    vectors.first = startPosition;
    vectors.second = desired;
    CCollision_ClearResultFlags(out);
    if (vectors.first.x == vectors.second.x &&
        vectors.first.y == vectors.second.y &&
        vectors.first.z == vectors.second.z) {
        return 0;
    }

    g_collisionSweepCount += 1;
    maximum = g_collisionPeakSweepCount;
    next = g_collisionSweepCount;
    if (next < maximum) {
        next = maximum;
    }
    g_collisionPeakSweepCount = next;

    ((struct ActorMotion *)(out))->actor = object;
    if (object != 0) {
        s32 value = 0;
        if (*(u8 *)object == 1) {
            flags = ((struct LevelActor *)(object))->flags;
            flags &= 0x300000;
            value = flags != 0;
        }
        ((struct ActorMotion *)(out))->actorFlags = value;
    } else {
        ((struct ActorMotion *)(out))->actorFlags = 0;
    }

    ((struct ActorMotion *)(out))->start = vectors.first;
    ((struct ActorMotion *)(out))->end = vectors.second;
    ((struct ActorMotion *)(out))->grounded = 0;
    ((struct ActorMotion *)(out))->candidate = 0;
    ((struct ActorMotion *)(out))->candidateIndex = 0;
    ((struct ActorMotion *)(out))->orientationActive = 0;
    ((struct ActorMotion *)(out))->iteration = 0;
    ((struct ActorMotion *)(out))->surface = (CCollisionInfo2_t *)motionSettings;
    ((struct ActorMotion *)(out))->queryFlags = 0;
    ((struct ActorMotion *)(out))->horizontalTicks = 0;
    ((struct ActorMotion *)(out))->verticalTicks = 0;
    CCollision_ResetContactNormal(out);

    active = 1;
    count = 0;
    do {
        if (CCollision_TraceActorMotion(out) != 0) {
            CCollision_StoreContactResult(out);
            count += 1;
            result = CCollision_ApplyMotionResponse(out);
            ((struct ActorMotion *)(out))->start = ((struct ActorMotion *)(out))->interpolated;
            ((struct ActorMotion *)(out))->end = ((struct ActorMotion *)(out))->position;
            ((struct ActorMotion *)(out))->orientation = ((struct ActorMotion *)(out))->projectedOrientation;
            active -= 1;
        } else {
            result = 0;
            ((struct ActorMotion *)(out))->start = ((struct ActorMotion *)(out))->end;
            active -= 1;
        }
    } while (result != 0 && active != 0);
    return count;
}

s32 CCollision_SweepUniformExtent(char *actorStorage, CVector3 startPosition, CVector3 endPosition, CCollisionInfo2_t *sweepSurfaceSettings,
                   f32 sweepExtent) {
    extern s32 CCollision_ApplyMotionResponse(void *actorStorage);
    CollisionSweepWork work;
    VectorPair vectors;
    char *object = actorStorage;
    char *out;
    s32 count;
    s32 active;
    s32 result;
    s32 next;
    s32 maximum;
    s32 flags;

    CCollision_SetUniformSweepExtent(work.data, sweepExtent);
    out = work.data;
    vectors.first = startPosition;
    vectors.second = endPosition;
    CCollision_ClearResultFlags(out);
    if (vectors.first.x == vectors.second.x &&
        vectors.first.y == vectors.second.y &&
        vectors.first.z == vectors.second.z) {
        return 0;
    }

    g_collisionSweepCount += 1;
    maximum = g_collisionPeakSweepCount;
    next = g_collisionSweepCount;
    if (next < maximum) {
        next = maximum;
    }
    g_collisionPeakSweepCount = next;

    ((struct ActorMotion *)(out))->actor = object;
    if (object != 0) {
        s32 value = 0;
        if (*(u8 *)object == 1) {
            flags = ((struct LevelActor *)(object))->flags;
            flags &= 0x300000;
            value = flags != 0;
        }
        ((struct ActorMotion *)(out))->actorFlags = value;
    } else {
        ((struct ActorMotion *)(out))->actorFlags = 0;
    }

    ((struct ActorMotion *)(out))->start = vectors.first;
    ((struct ActorMotion *)(out))->end = vectors.second;
    ((struct ActorMotion *)(out))->grounded = 0;
    ((struct ActorMotion *)(out))->candidate = 0;
    ((struct ActorMotion *)(out))->candidateIndex = 0;
    ((struct ActorMotion *)(out))->orientationActive = 0;
    ((struct ActorMotion *)(out))->iteration = 0;
    ((struct ActorMotion *)(out))->surface = sweepSurfaceSettings;
    ((struct ActorMotion *)(out))->queryFlags = 0;
    ((struct ActorMotion *)(out))->horizontalTicks = 0;
    ((struct ActorMotion *)(out))->verticalTicks = 0;
    CCollision_ResetContactNormal(out);

    active = 1;
    count = 0;
    do {
        if (CCollision_TraceActorMotion(out) != 0) {
            CCollision_StoreContactResult(out);
            count += 1;
            result = CCollision_ApplyMotionResponse(out);
            ((struct ActorMotion *)(out))->start = ((struct ActorMotion *)(out))->interpolated;
            ((struct ActorMotion *)(out))->end = ((struct ActorMotion *)(out))->position;
            ((struct ActorMotion *)(out))->orientation = ((struct ActorMotion *)(out))->projectedOrientation;
            active -= 1;
        } else {
            result = 0;
            ((struct ActorMotion *)(out))->start = ((struct ActorMotion *)(out))->end;
            active -= 1;
        }
    } while (result != 0 && active != 0);
    return count;
}

s32 Unicol_SweepActorMotion(char *actorStorage, CVector3 startPosition, CVector3 endPosition, CCollisionInfo2_t *motionSettings,
                  CVector3 motionExtents, f32 baseOffset) {
    extern s32 CCollision_ApplyMotionResponse(void *actorStorage);
    CollisionSweepWork work;
    VectorPair vectors;
    char *object = actorStorage;
    char *out;
    s32 count;
    s32 active;
    s32 result;
    s32 next;
    s32 maximum;
    s32 flags;

    CCollision_SetSweepRange(work.data, motionExtents.x, motionExtents.y, motionExtents.z, baseOffset);
    out = work.data;
    vectors.first = startPosition;
    vectors.second = endPosition;
    CCollision_ClearResultFlags(out);
    if (vectors.first.x == vectors.second.x &&
        vectors.first.y == vectors.second.y &&
        vectors.first.z == vectors.second.z) {
        return 0;
    }

    g_collisionSweepCount += 1;
    maximum = g_collisionPeakSweepCount;
    next = g_collisionSweepCount;
    if (next < maximum) {
        next = maximum;
    }
    g_collisionPeakSweepCount = next;

    ((struct ActorMotion *)(out))->actor = object;
    if (object != 0) {
        s32 value = 0;
        if (*(u8 *)object == 1) {
            flags = ((struct LevelActor *)(object))->flags;
            flags &= 0x300000;
            value = flags != 0;
        }
        ((struct ActorMotion *)(out))->actorFlags = value;
    } else {
        ((struct ActorMotion *)(out))->actorFlags = 0;
    }

    ((struct ActorMotion *)(out))->start = vectors.first;
    ((struct ActorMotion *)(out))->end = vectors.second;
    ((struct ActorMotion *)(out))->grounded = 0;
    ((struct ActorMotion *)(out))->candidate = 0;
    ((struct ActorMotion *)(out))->candidateIndex = 0;
    ((struct ActorMotion *)(out))->orientationActive = 0;
    ((struct ActorMotion *)(out))->iteration = 0;
    ((struct ActorMotion *)(out))->surface = motionSettings;
    ((struct ActorMotion *)(out))->queryFlags = 0;
    ((struct ActorMotion *)(out))->horizontalTicks = 0;
    ((struct ActorMotion *)(out))->verticalTicks = 0;
    CCollision_ResetContactNormal(out);

    active = 1;
    count = 0;
    do {
        if (CCollision_TraceActorMotion(out) != 0) {
            CCollision_StoreContactResult(out);
            count += 1;
            result = CCollision_ApplyMotionResponse(out);
            ((struct ActorMotion *)(out))->start = ((struct ActorMotion *)(out))->interpolated;
            ((struct ActorMotion *)(out))->end = ((struct ActorMotion *)(out))->position;
            ((struct ActorMotion *)(out))->orientation = ((struct ActorMotion *)(out))->projectedOrientation;
            active -= 1;
        } else {
            result = 0;
            ((struct ActorMotion *)(out))->start = ((struct ActorMotion *)(out))->end;
            active -= 1;
        }
    } while (result != 0 && active != 0);
    return count;
}

s32 CCollision_SweepWithWorkBuffer(char *actorStorage, char *motionWork, CVector3 first, CVector3 second,
                   s32 motionSurface) {
    extern s32 CCollision_ApplyMotionResponse(void *actorStorage);
    char *object = actorStorage;
    char *out = motionWork;
    s32 count;
    s32 active;
    s32 result;
    s32 next;
    s32 maximum;
    s32 flags;

    CCollision_ClearResultFlags(out);
    if (first.x == second.x && first.y == second.y && first.z == second.z) {
        return 0;
    }

    g_collisionSweepCount += 1;
    maximum = g_collisionPeakSweepCount;
    next = g_collisionSweepCount;
    if (next < maximum) {
        next = maximum;
    }
    g_collisionPeakSweepCount = next;

    ((struct ActorMotion *)(out))->actor = object;
    if (object != 0) {
        s32 value = 0;
        if (*(u8 *)object == 1) {
            flags = ((struct LevelActor *)(object))->flags;
            flags &= 0x300000;
            value = flags != 0;
        }
        ((struct ActorMotion *)(out))->actorFlags = value;
    } else {
        ((struct ActorMotion *)(out))->actorFlags = 0;
    }

    ((struct ActorMotion *)(out))->start = first;
    ((struct ActorMotion *)(out))->end = second;
    ((struct ActorMotion *)(out))->grounded = 0;
    ((struct ActorMotion *)(out))->candidate = 0;
    ((struct ActorMotion *)(out))->candidateIndex = 0;
    ((struct ActorMotion *)(out))->orientationActive = 0;
    ((struct ActorMotion *)(out))->iteration = 0;
    ((struct ActorMotion *)(out))->surface = motionSurface;
    ((struct ActorMotion *)(out))->queryFlags = 0;
    ((struct ActorMotion *)(out))->horizontalTicks = 0;
    ((struct ActorMotion *)(out))->verticalTicks = 0;
    CCollision_ResetContactNormal(out);

    active = 1;
    count = 0;
    do {
        if (CCollision_TraceActorMotion(out) != 0) {
            CCollision_StoreContactResult(out);
            count += 1;
            result = CCollision_ApplyMotionResponse(out);
            ((struct ActorMotion *)(out))->start = ((struct ActorMotion *)(out))->interpolated;
            ((struct ActorMotion *)(out))->end = ((struct ActorMotion *)(out))->position;
            ((struct ActorMotion *)(out))->orientation = ((struct ActorMotion *)(out))->projectedOrientation;
            active -= 1;
        } else {
            result = 0;
            ((struct ActorMotion *)(out))->start = ((struct ActorMotion *)(out))->end;
            active -= 1;
        }
    } while (result != 0 && active != 0);
    return count;
}


/* 800C8710_13.CPP */
const float k_UnicolEncodedWordsBlock1[7] = {
    -0.45f, -0.7071f, 204.79999f, 1.0f, 51.199997f, 1.024f,
    51.199997f,
};



