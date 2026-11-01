#include "COMMON/OBJ.H"
#include "COMMON/MODEL_RENDER.H"
#include "include_asm.h"
#include "COMMON/REC.H"
#include "COMMON/LIGHTDATA.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/LISTHEADER.H"
#include "TYPES.H"
#include "RENDER/TRIGGERED_UPDATETRIGGEREDMOTION.H"
#include "RENDER/MOVINGAI.H"
#include "COMMON/SHAREDPLAYER.H"
#include <ultra64.h>
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "GOBJINST/GASTATE_ADVANCEROOTMOTION_DATA.H"

extern void Scene_SetLevelActorStateBit(void *a, unsigned short b, unsigned short c, int d);

extern int Cinema_IsSequenceInWindow(void);

/** For each of the object's child slots, attach the child to the record and spawn its effect. */
extern int g_lightingBufferIndex;

extern void *Gobjinst_RequestAnimatedModelVariant(void *, int);

extern void GameObject_DrawActorShadow(char *obj, s32 unused, char *info);

extern void Track_RequestTrackByIds(s32, void *);

void Triggered_StartTriggerAnimation(void *actor, void *motionState, Trigger *trigger) {
    extern void Rumble_SetActorStateBit(Shared_World *a, void *b, int c);
    MovingAI_RequestMotionAnimation(actor, motionState, trigger->trackArgument);
    ((LevelActor *)actor)->flags = ((LevelActor *)actor)->flags | 0x2100;
    Gobjinst_AdvanceActorRootMotion(actor);
    Rumble_SetActorStateBit(&g_world, actor, 0);
}

void Triggered_ClearCollisionAndActivate(Shared_Actor *actor) {
    extern void Rumble_SetActorStateBit(Shared_World *, void *, s32);
    s32 v = actor->weaponFlags;
    v &= ~0x2000;
    v &= ~0x100;
    actor->weaponFlags = v;
    Rumble_SetActorStateBit(&g_world, actor, 1);
}

void Triggered_EnableTriggeredActorState(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 1);
}

void Triggered_DeactivateForSequence(Shared_Actor *actor, s32 *sequenceFlags) {
    extern void Rumble_SetActorStateBit(Shared_World *, void *, s32);
    actor->weaponFlags |= 0x2100;
    if (Cinema_IsSequenceInWindow() != 0) {
        *sequenceFlags |= 0x200;
    }
    Gobjinst_AdvanceActorRootMotion(actor);
    Rumble_SetActorStateBit(&g_world, actor, 0);
}

void Triggered_DisableTriggeredActorState(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 0);
}

void Triggered_RequestTrackAndDeactivate(struct Shared_Actor *actor, s32 unusedContext, s32 trackRequest) {
    extern void Rumble_SetActorStateBit(Shared_World *, void *, s32);
    Track_RequestTrackByIds((s32)actor, (void *)trackRequest);
    actor->weaponFlags |= 0x2100;
    Rumble_SetActorStateBit(&g_world, actor, 0);
}

void Triggered_RequestTrackById(s32 trackRequest) {
    Track_RequestTrackByIds(0, (void *)trackRequest);
}

/** Copy the source byte at offset 7 into two fields under object offset 0x18. */
void Triggered_SetPairedDefinitionBytes(LevelActor *actor, int unusedContext, Trigger *triggerRecord) {
    void *inner = actor->definition;
    ((ActorDefinitionHeader *)inner)->first = (s8)triggerRecord->trackArgument;
    inner = actor->definition;
    ((ActorDefinitionHeader *)inner)->second = (s8)triggerRecord->trackArgument;
}

void Triggered_DrawAnimatedVariants(char *actor, void *renderContext, Rec *info) {
    int i;
    int n;
    void *child;

    n = (s8)((LevelActor *)actor)->stateE7;
    for (i = 0; i < n; i++) {
        child = Gobjinst_RequestAnimatedModelVariant(actor, i);
        if (child != 0) {
            info->a = child;
            info->b = child;
            GameObject_DrawActorShadow(actor, renderContext, info);
            Geometry_DrawModelResource(child, ((LevelActor *)actor)->animationMatrices, 1, &((LevelActor *)actor)->lighting[g_lightingBufferIndex], 0, ((LevelActor *)actor)->renderPass);
        }
    }
}

extern f32 g_frameElapsedTime;

/* Advance triggered shaking and vertical motion, invalidating animation on a state change. */
/* A hold segment keeps the motion until the input is held. */
void Triggered_UpdateTriggeredMotion(MovingPlatformActorView *actor, MovingPlatformMotionStateView *motion) {
    CPlatformIntelligence *segment;
    s32 oldState;
    s32 release;
    f32 shakeMin;
    f32 shakeMax;

    oldState = motion->state;
    segment = &actor->motionTrack->segment;
    switch (oldState) {
    case 0:
        if (segment->flags & 0xC00000) {
            if (segment->flags & 0x04000000) {
                if (actor->inputFlags & 0x40) {
                    motion->triggerTime = motion->triggerTime + g_frameElapsedTime;
                } else {
                    motion->triggerTime = 0.0f;
                    break;
                }
            } else if (motion->triggerTime > 0.0f || (actor->inputFlags & 0x20)) {
                motion->triggerTime += g_frameElapsedTime;
            }
            if (motion->triggerTime >= segment->triggerDelay) {
                motion->timer = 0.0f;
                if (segment->flags & 0x01000000) {
                    motion->state = 3;
                } else if (segment->flags & 0x400000) {
                    motion->state = 1;
                } else if (segment->flags & 0x800000) {
                    motion->state = 4;
                }
            }
        }
        break;
    case 3:
        shakeMin = -0.512f;
        shakeMax = 0.512f;
        motion->shake.x = Graphu64_RandomBetween(shakeMin, shakeMax);
        motion->shake.y = Graphu64_RandomBetween(shakeMin, shakeMax);
        motion->shake.z = Graphu64_RandomBetween(shakeMin, shakeMax);
        motion->timer += g_frameElapsedTime;
        if (45.0f < motion->timer) {
            motion->timer = 0.0f;
            if (segment->flags & 0x400000) {
                motion->state = 1;
            } else if (segment->flags & 0x800000) {
                motion->state = 4;
            }
        }
        break;
    case 1:
        if (motion->timer < segment->duration) {
            motion->timer += g_frameElapsedTime;
        } else if (segment->flags & 0x02000000) {
            actor->flags &= ~0x2000;
        } else {
            motion->timer = segment->duration;
            if ((segment->flags & 0x08000000) && !(actor->inputFlags & 0x40)) {
                release = 0;
            } else {
                u32 flags = segment->flags;
                release = 1;
                if (flags & 0x10000000) {
                    release = (actor->inputFlags & 0x40) < release;
                }
            }
            if (release) {
                motion->state = 2;
            }
        }
        if (segment->duration > 0.0f) {
            motion->shake.y = -segment->displacement * Defs_CosineEase(motion->timer / segment->duration);
        } else {
            motion->shake.y = -segment->displacement;
        }
        break;
    case 2:
        if (motion->timer > 0.0f) {
            motion->timer -= g_frameElapsedTime;
        } else {
            motion->state = 0;
            motion->triggerTime = 0.0f;
        }
        if (segment->duration > 0.0f) {
            motion->shake.y = -segment->displacement * Defs_CosineEase(motion->timer / segment->duration);
        } else {
            motion->shake.y = -segment->displacement;
        }
        break;
    case 4:
        if (motion->timer < segment->duration) {
            motion->timer += g_frameElapsedTime;
        }
        if (segment->duration > 0.0f) {
            motion->shake.y = -segment->displacement * Defs_CosineEase(motion->timer / segment->duration);
        } else {
            motion->shake.y = -segment->displacement;
        }
        if (segment->flags & 0x02000000) {
            actor->flags &= ~0x2000;
        }
        break;
    }
    if (oldState != motion->state) {
        motion->animation = -1;
    }
}

/* Places a rider along its path for the frame: clamps the throttle to 0..1 (eased through Defs_CosineEase unless the segment is linear), offsets its base by the segment's rise and circle point, moves the rider there through Graphu64_InterpolateVector, adds a bob to its height (one wave or a sum of four detuned waves by the segment's bob mode), applies its shake offsets, turns the actor by the segment's yaw mode (interpolated, constant spin unless held, or constant spin) and, for free segments, snaps the actor to the ground through Region_GetPolygonHeight and Region_SetNodeGroupHeight. */

extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);

extern f32 Region_GetPolygonHeight(s32, f32, f32);

extern void Region_SetNodeGroupHeight(s32, f32);

/* Steers an actor along path nodes, blending direction, speed and orientation as it advances waypoints. */
/* The values Triggered_AdvancePathMotion loads by address:
 * 0x800C6C18 = 3.0 (float, k_triggeredMinArrivalRadius in this cartridge's tables)
 * 0x800C6C1C = 10.24 (float, unnamed in this cartridge's tables)
 * 0x800C6C20 = 1.0 (float, k_triggeredBlendClampLimit in this cartridge's tables)
 * 0x800C6C24 = 1.0 (float, unnamed in this cartridge's tables)
 * 0x800C6C28 = 1.0 (float, k_triggeredBlendCompleteThreshold in this cartridge's tables)
 * 0x800C6C2C = 3.1415927 (float, k_triggeredBrakeEasePi in this cartridge's tables)
 * 0x800C6C30 = 0.5 (float, k_triggeredBrakeFraction in this cartridge's tables)
 * 0x800C6C34 = 0.3 (float, k_triggeredStopSpeedThreshold in this cartridge's tables)
 * 0x800C6C38 = 15.0 (float, k_triggeredPauseDurationScale in this cartridge's tables)
 * 0x800D2988 = 1.0 (float, g_frameElapsedTime in this cartridge's tables; not a literal: a variable, its value in the image, since g_frameElapsedTime: `swc1` at %lo(g_frameElapsedTime) in Actor_UpdateActorStateAnimation.s)
 * 0x800C6C3C = 1.0 (float, k_triggeredAccelEaseOne in this cartridge's tables)
 * 0x800C6C40 = 3.1415927 (float, k_triggeredAccelEasePi in this cartridge's tables)
 * 0x800C6C44 = 0.5 (float, k_triggeredAccelBlendHalf in this cartridge's tables)
 * 0x800C6C48 = 2.670354 (float, k_triggeredStartEaseAngle in this cartridge's tables)
 * 0x800C6C4C = 0.5 (float, unnamed in this cartridge's tables)
 * 0x800C6C50 = 1.0 (float, k_triggeredStartEaseOffset in this cartridge's tables)
 * 0x800C6C54 = 0.017453294 (float, unnamed in this cartridge's tables)
 * 0x800C6C58 = 0.017453294 (float, k_triggeredHeadingSmoothDegToRad in this cartridge's tables)
 * 0x800C6C5C = 0.1 (float, unnamed in this cartridge's tables)
 * 0x800C6C60 = 0.017453294 (float, k_triggeredSecondaryBlendDegToRad in this cartridge's tables)
 * 0x800C6C64 = 0.017453294 (float, unnamed in this cartridge's tables)
 * 0x800C6C68 = 0.1 (float, k_triggeredSecondarySmoothFactor in this cartridge's tables)
 * 0x800C6C6C = 0.017453294 (float, k_triggeredTertiaryBlendDegToRad in this cartridge's tables)
 * 0x800C6C70 = 0.017453294 (float, k_triggeredTertiarySmoothDegToRad in this cartridge's tables)
 * 0x800C6C74 = 0.1 (float, unnamed in this cartridge's tables)
 */
void Barrel_ApplyClampedTurn(void *, s32, f32, f32);

void Playerai_AdvanceRouteCursor(void *);

void * Playerai_GetRouteCursorPoint(struct Cursor *);

void *Playerai_GetRouteCursorNextPoint(struct Cursor *);

void Graphu64_SubtractVectors(struct CVector3_t *difference, struct CVector3_t *leftVector, struct CVector3_t *rightVector);

f32 Gu_Sqrtf(f32);

f32 Barrel_GetSignedAngleToPoint(void *, CVector3);

 /* extern */

/* Chooses the option label from the signed kind byte and, for the default
 * kind, the paired variant byte. The caller's context is unused. */
struct TriggeredMotionSoundOption {
    char pad0[0x34];
    s8 variant;
    char pad35[2];
    s8 kind;
};

extern char g_triggeredMotionDispatchTable[];

extern char g_triggeredUpdateRomEntry;

extern char g_triggeredTransformRomEntry;

extern f32 k_triggeredInitialMotionScale;

void Triggered_PositionPlatformRider(MovingPlatformActorView *actor, MovingPlatformMotionStateView *rider) {
    CVector3 point;
    CPlatformIntelligence *segment;
    f32 t;
    f32 phase;
    f32 amp;
    CVector3 *base;
    MovingPlatformActorView *owner;
    t = rider->throttle;
    segment = (CPlatformIntelligence *)(&((struct NavigationTrack *)actor->track)->segment);
    if (t < 0.0f) {
        t = 0.0f;
    } else if (t > 1.0f) {
        t = 1.0f;
    }
    if (segment->linear == 0) {
        t = Defs_CosineEase(t);
    }
    owner = actor;
    point = rider->base;
    base = &rider->base;
    point.y += segment->rise;
    if (segment->moving != 0) {
        point.x += segment->radius * Gu_Sinf(segment->angle);
        point.z += segment->radius * Math_Cosf(segment->angle);
    }
    Graphu64_InterpolateVector(&rider->pos, t, base, &point);
    switch (segment->bobMode) {
    case 0:
        rider->pos.y += segment->bob * Gu_Sinf(rider->phase);
        break;
    case 1:
        phase = rider->phase;
        amp = 0.25f;
        rider->pos.y += segment->bob * (Gu_Sinf(phase) * amp);
        rider->pos.y += segment->bob * (Gu_Sinf(phase * 1.1f) * amp);
        rider->pos.y += segment->bob * (Gu_Sinf(phase * 1.2f) * amp);
        rider->pos.y += segment->bob * (Gu_Sinf(phase * 1.3f) * amp);
        break;
    }
    rider->pos.x += rider->shake.x;
    rider->pos.y += rider->shake.y;
    rider->pos.z += rider->shake.z;
    switch (segment->yawMode) {
    case 0:
        owner->yaw = rider->baseYaw + t * ((rider->baseYaw + segment->yaw) - rider->baseYaw);
        break;
    case 1:
        if (rider->flags & 0x400) {
            break;
        }
    case 2:
        owner->yaw += segment->yaw * 0.06666667f;
        break;
    }
    if (segment->moving == 0) {
        Region_SetNodeGroupHeight(owner->model, Region_GetPolygonHeight(owner->model, owner->x, owner->z) + rider->pos.y - owner->y);
    }
}

struct Cursor;

/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x40, 0x44, 0x48, 0x4c, 0x50, 0x54, 0x58, 0x68, 0x6c], gap at: 0x5c. */
/* Steers an actor along path nodes, blending direction, speed and orientation as it advances waypoints. */
void Triggered_AdvancePathMotion(PathMotionActorView *actor, PathMotionInterpolationState *pathState) {
    Triple initial;
    CVector3 vec0;
    CVector3 vec1;
    f32 advancedBlend;
    f32 remainingPause;
    f32 previousBlend;
    f32 unusedPathInterpolationOne;
    f32 previousDirectionY;
    f32 previousDirectionZ;
    f32 pauseOrDirectionZ;
    f32 currentHeading;
    f32 currentSecondaryAngle;
    f32 currentTertiaryAngle;
    f32 blendRate;
    f32 targetDistance;
    f32 unusedPathInterpolationTwo;
    f32 segmentDirectionY;
    f32 segmentDirectionZ;
    f32 arg0_2;
    f32 initialHeading;
    f32 initialSecondaryAngle;
    f32 initialTertiaryAngle;
    f32 arrivalRadius;
    f32 movementSpeed;
    u16 half;
    PathMotionWaypoint *segmentNode;
    void *pathCursor;
    PathMotionWaypoint *targetNode;
    pathCursor = (void *) &pathState->pathCursor;
    targetNode = Playerai_GetRouteCursorPoint(pathCursor);
    initial = targetNode->pos;
    Graphu64_SubtractVectors(&vec0, &initial, &actor->positionX);
    segmentNode = Playerai_GetRouteCursorNextPoint(pathCursor);
    targetDistance = Gu_Sqrtf(vec0.x * vec0.x + vec0.y * vec0.y + vec0.z * vec0.z);
    arrivalRadius = targetNode->arrivalRadius;
    blendRate = segmentNode->directionBlendRate;
    if (arrivalRadius < 3.0f) {
        arrivalRadius = 3.0f;
    }
    if (targetDistance <= arrivalRadius * 10.24f) {
        pathState->directionBlend = 0.0f;
        segmentNode->flags.half = (u16) (segmentNode->flags.half & 0x7FFF);
        Playerai_AdvanceRouteCursor(pathCursor);
        pathState->previousDirectionX = (f32) pathState->directionX;
        pathState->previousDirectionY = (f32) pathState->directionY;
        pathState->previousDirectionZ = (f32) pathState->directionZ;
        pathState->initialSecondaryAngle = (f32) pathState->secondaryAngle;
        arg0_2 = actor->heading;
        pathState->initialTertiaryAngle = (f32) pathState->tertiaryAngle;
        pathState->initialHeading = (f32) arg0_2;
        return;
    }
    if (segmentNode->flags.half & 2) {
        previousBlend = pathState->directionBlend;
        if (previousBlend <= 0.0f) {
            pathState->directionBlend = blendRate;
        } else {
            advancedBlend = previousBlend + blendRate;
            pathState->directionBlend = advancedBlend;
            if (advancedBlend > 1.0f) {
                pathState->directionBlend = 1.0f;
            }
        }
        if (segmentNode == targetNode) {
            Graphu64_SubtractVectors(&vec1, segmentNode, &actor->positionX);
        } else {
            Graphu64_SubtractVectors(&vec1, targetNode, segmentNode);
        }
        Graphu64_NormalizeVec3(&vec1);
        ;
        vec1.x = pathState->previousDirectionX + pathState->directionBlend * (vec1.x - pathState->previousDirectionX);
        segmentDirectionY = pathState->previousDirectionY;
        vec1.y = segmentDirectionY + pathState->directionBlend * (vec1.y - segmentDirectionY);
        segmentDirectionZ = pathState->previousDirectionZ;
        vec1.z = segmentDirectionZ + pathState->directionBlend * (vec1.z - segmentDirectionZ);
        Graphu64_NormalizeVec3(&vec1);
        if (pathState->directionBlend >= 1.0f) {
            goto block_17;
        }
    } else {
        Graphu64_NormalizeVec3(&vec0);
        ;
        vec1.x = pathState->previousDirectionX + blendRate * (vec0.x - pathState->previousDirectionX);
        previousDirectionY = pathState->previousDirectionY;
        vec1.y = previousDirectionY + blendRate * (vec0.y - previousDirectionY);
        previousDirectionZ = pathState->previousDirectionZ;
        vec1.z = previousDirectionZ + blendRate * (vec0.z - previousDirectionZ);
        Graphu64_NormalizeVec3(&vec1);
        block_17:
        pathState->previousDirectionX = vec1.x;
        pathState->previousDirectionY = vec1.y;
        pathState->previousDirectionZ = vec1.z;
    }
    pathState->directionX = vec1.x;
    pathState->directionY = vec1.y;
    pathState->directionZ = vec1.z;
    half = segmentNode->flags.half;
    if (half & 1) {
        if (pathState->movementSpeed > 0.0f && !(half & 0x8000)) {
            movementSpeed = pathState->movementSpeed + (Math_Cosf((1.0f - segmentNode->speedCurvePhase) * 3.1415927f) + 1.0f) * (-pathState->movementSpeed * 0.5f);
            if (movementSpeed <= 0.3f) {
                pathState->pauseRemaining = (f32) (segmentNode->pauseDuration * 15.0f);
                movementSpeed = 0.0f;
                segmentNode->flags.half = (u16) (segmentNode->flags.half | 0x8000);
            }
        } else {
            pauseOrDirectionZ = pathState->pauseRemaining;
            movementSpeed = 0.0f;
            if (pauseOrDirectionZ > 0.0f) {
                remainingPause = pauseOrDirectionZ - g_frameElapsedTime;
                pathState->pauseRemaining = remainingPause;
                if (remainingPause <= 0.0f) {
                    pathState->pauseRemaining = 0.0f;
                }
            } else if (pauseOrDirectionZ == 0.0f) {
                movementSpeed = pathState->movementSpeed + (Math_Cosf((1.0f - segmentNode->speedCurvePhase) * 3.1415927f) + 1.0f) * ((segmentNode->targetSpeed - pathState->movementSpeed) * 0.5f);
            }
        }
    } else {
        movementSpeed = pathState->movementSpeed + (Math_Cosf(2.670354f) + 1.0f) * ((segmentNode->targetSpeed - pathState->movementSpeed) * 0.5f);
    }
    if (actor->inputFlags & 8) {
        movementSpeed = 0.0f;
    }
    pathState->movementSpeed = movementSpeed;
    pathState->nextPositionX = (f32) (actor->positionX.v1 + vec1.x * movementSpeed * g_frameElapsedTime);
    pathState->nextPositionY = (f32) (actor->positionY + vec1.y * movementSpeed * g_frameElapsedTime);
    pauseOrDirectionZ = vec1.z;
    pathState->nextPositionZ = (f32) (actor->positionZ + pauseOrDirectionZ * movementSpeed * g_frameElapsedTime);
    if (segmentNode->flags.half & 8) {
        if ((segmentNode->flags.word & 0x420000) == 0x420000) {
            initialHeading = pathState->initialHeading;
            actor->heading = (f32) (initialHeading + pathState->directionBlend * (segmentNode->headingDegrees * 0.017453294f - initialHeading));
        } else {
            currentHeading = actor->heading;
            actor->heading = (f32) (currentHeading + (segmentNode->headingDegrees * 0.017453294f - currentHeading) * 0.1f);
        }
    } else {
        Barrel_ApplyClampedTurn(actor, (s32) pathState, 10.0f, Barrel_GetSignedAngleToPoint(actor, *(CVector3 *) &pathState->nextPositionX));
    }
    if (segmentNode->flags.half & 4) {
        if ((segmentNode->flags.word & 0x220000) == 0x220000) {
            initialSecondaryAngle = pathState->initialSecondaryAngle;
            pathState->secondaryAngle = (f32) (initialSecondaryAngle + pathState->directionBlend * (segmentNode->secondaryAngleDegrees * 0.017453294f - initialSecondaryAngle));
        } else {
            currentSecondaryAngle = pathState->secondaryAngle;
            pathState->secondaryAngle = (f32) (currentSecondaryAngle + (segmentNode->secondaryAngleDegrees * 0.017453294f - currentSecondaryAngle) * 0.1f);
        }
    }
    if (segmentNode->flags.half & 0x10) {
        if ((segmentNode->flags.word & 0x820000) == 0x820000) {
            initialTertiaryAngle = pathState->initialTertiaryAngle;
            pathState->tertiaryAngle = (f32) (initialTertiaryAngle + pathState->directionBlend * (segmentNode->tertiaryAngleDegrees * 0.017453294f - initialTertiaryAngle));
            return;
        }
        currentTertiaryAngle = (*pathState).tertiaryAngle;
        pathState->tertiaryAngle = (f32) (currentTertiaryAngle + (segmentNode->tertiaryAngleDegrees * 0.017453294f - currentTertiaryAngle) * 0.1f);
    }
}

/** Perform no operation. */
void Triggered_PathMotionNoOp(void) {
}

s32 Triggered_SelectMotionSound(void *context, struct TriggeredMotionSoundOption *option) {
    s32 result;
    switch (option->kind) {
    case 3:
        return 21120;
    case 1:
    case 2:
        return 21140;
    case 0:
        result = 21100;
        switch (option->variant) {
        case 0:
        case 2:
            return 21100;
        case 1:
        case 3:
            return 21110;
        }
        break;
    default:
        return 21100;
    case 4:
        return 21130;
    }
    return result;
}

extern s32 Rumble_TestActorStateBit(void *, void *);
void Triggered_TestActorStateCallback(int actorHandle) {
    Rumble_TestActorStateBit(&g_world, (void *)actorHandle);
}

void Triggered_InitializeMotionState(void *object, void *state)
{
    Player *actor = object;
    ActorMotionState *motionState = state;
    f32 k;
    f32 value;
    f32 scaled;
    ActorMotionResource *motionResource;
    ActorMotionDefinition *motionDefinition;

    motionResource = actor->definition;
    k = k_triggeredInitialMotionScale;
    motionState->table = &g_triggeredMotionDispatchTable;
    motionState->update = &g_triggeredUpdateRomEntry;
    motionState->transform = &g_triggeredTransformRomEntry;
    motionState->yaw = 0;
    motionState->pitch = 0;
    motionDefinition = &motionResource->motion;
    value = motionDefinition->speed;
    motionState->animation = 0;
    motionState->remainingCount = 0;
    motionState->reservedWord12C = 0;
    motionState->reservedWord130 = 0;
    motionState->speed = value;
    scaled = motionDefinition->speed;
    motionState->reservedWord140 = 0;
    motionState->reservedWord144 = 0;
    scaled = scaled * k;
    motionState->reservedWord148 = 0;
    motionState->reservedWord14C = 0;
    motionState->reservedWord168 = 0;
    motionState->openTimer = 0;
    motionState->progress = scaled;
    if (motionResource->motion.flags & 4) {
        actor->weaponFlags = actor->weaponFlags & ~0x2000;
    }
}

void Triggered_ResetMotionState(void *object, void *state) {
    Player *player = object;
    ActorMotionState *motionState = state;
    motionState->state = 0;
    Actor_RequestActorState(player, motionState, 0);
    if (motionState->routeMode == 1) {
        motionState->destination = motionState->start;
        Actor_RequestActorState(player, motionState, 4);
    }
    if (Rumble_TestActorStateBit(&g_world, player) == 0) {
        player->weaponFlags &= ~0x100;
    }
}

/* ROM-grounded data: src/k_triggeredFullTurnFloatUsRev1.c */
const float k_triggeredUpdatetriggeredmotionFloatConstantWords[1] = {
    6.283186f,
};
