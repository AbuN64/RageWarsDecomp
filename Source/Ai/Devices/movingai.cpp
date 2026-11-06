#include "Common/stagepreset.h"
#include "Common/menu_match_globals.h"
#include "Common/shared_optionsscreen.h"
#include "Common/animationtriggerdefinition.h"
#include "Common/vector4f.h"
#include "Common/aiprofile.h"
#include "Common/level_actor.h"
#include "Common/world.h"
#include "Common/obj.h"
#include "Common/rec.h"
#include "types.h"
#include "Weapons/actor_requestactorstate.h"
#include "Common/Lone/g_currentstagepreset.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/shared_voidcallback.h"
#include "Common/multiplayeroptions.h"
#include "Common/listheader.h"
#include "Common/shared_gameslot.h"
#include "Common/rendercounters.h"
#include "Render/movingai.h"
#include "Particle/particle_spawneffectgroup.h"
#include "include_asm.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
#include "Engine/rumble_setactorstatebit.h"
#include "Engine/Cinema/cinema.h"
#include "Gobjinst/gobjinst_buildactortransform.h"
#include "Engine/Animpool/animpool_spawnsceneeffect.h"
#include "Engine/session.h"
#include "Ai/ai_shared_symbols.h"
#include "Menu/pak_load.h"
#include "Ai/devices_symbols.h"
#include "Ai/Enemies/turretai.h"
#include "Common/approachlocation.h"
#include "Common/ballisticparams.h"
#include "Ai/Cbarrel/barrel_getsignedangletopoint.h"
#include "Ai/ai_functions.h"
#include "Common/model_render.h"
#include "Common/lightdata.h"
#include "Render/triggered_updatetriggeredmotion.h"
#include <platform_sdk.h>
#include "Fx/normalize_vector.h"
#include "Gobjinst/gastate_advancerootmotion_data.h"
#include "Actor/actor_updateactorstateanimation.h"
#include "Engine/gregion.h"
#include "Gobjinst/gobjinst_requestanimatedmodelvariant.h"
#include "Playerai/playerai__playerai.h"
#include "Track/track_drawtrackoverlay.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Engine/Instance/gobjinst.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/triple.h"
#include "Ai/Devices/Movingai/movingai.h"

void MovingAI_ChooseTriggerDelay(void *levelActor, void *actorMotionState) {
    LevelActor *actor = levelActor;
    ActorMotionState *motion = actorMotionState;
    AnimationTriggerResource *resource;
    AnimationTriggerDefinition *base;
    Shared_Game *game;
    f32 result;
    s32 count;
    s32 delayPercent;
    f64 unsignedDelayPercent;
    f32 scaled;

    resource = (void *)actor->definition;
    base = &resource->trigger;
    result = Graphu64_RandomBetween(base->delayMinimum, base->delayMaximum);
    motion->speed = result;
    game = &g_gameSettings;
    if (game->local != 0) {
        count = ((Shared_MenuData *)((char *)game - offsetof(Shared_MenuData, game)))->sessionOptionResetMode;
        if ((u32) count >= 3) {
            count -= 2;
            scaled = result * k_triggerDelayPercentScale;
            delayPercent = 100 - count * 25;
            unsignedDelayPercent = (f64) delayPercent;
            if (delayPercent < 0) {
                unsignedDelayPercent += (4294967296.0);
            }
            motion->speed = scaled * (f32) unsignedDelayPercent;
        }
    }
}

void MovingAI_UpdateTriggerDelay(LevelActor *actor, ActorMotionState *motionState) {
    AnimationTriggerResource *definition;
    AnimationTriggerDefinition *triggerDefinition;
    s32 flags;
    s32 interactionGuard;

    definition = (void *)actor->definition;
    triggerDefinition = &definition->trigger;
    if (triggerDefinition->enabled == 0) {
        if (triggerDefinition->firstAnimation == -1) {
            motionState->timer = 0.0f;
            return;
        }
        if (triggerDefinition->secondAnimation == -1) {
            motionState->timer = 0.0f;
            return;
        }
    }
    if (motionState->animation == triggerDefinition->animation) {
        motionState->timer = 0.0f;
        return;
    }
    flags = triggerDefinition->flags;
    if (!(flags & 1)) {
        if (motionState->remainingCount <= 0) {
            return;
        }
    }
    interactionGuard = flags & 2;
    if (interactionGuard != 0) {
        if (actor->flags & 0x200) {
            motionState->timer = 0.0f;
            return;
        }
    }
    if (motionState->timer >= motionState->speed) {
        Actor_RequestActorState(actor, motionState, 1);
    }
}

void MovingAI_RequestInactiveOnEvent(void *actor, struct WeaponEventSource *eventSource) {
    if (eventSource->eventEnabled != 0) {
        Actor_RequestActorState(actor, eventSource, 0);
    }
}

int MovingAI_IsActorStateActive(int actor) {
    return Rumble_TestActorStateBit(&g_world, actor) == 1;
}

void MovingAI_SetActorStateActive(void *actor) {
    Rumble_SetActorStateBit(&g_world, actor, 1);
}


/* Spawns effect kind at an actor's position through SetN64_SpawnModelEffect in g_modelEffectPool's list: kind 0xBD7
   is skipped while both of g_gameSettings.counters's flags are set, and kind 0x1388 is offset by
   the variant byte at g_currentStagePreset when option g_gameControllerMode is 1 (skipped for variant 0); a spawned node
   has its word cleared, takes one charge from the owner and starts effect 0x11D at its own
   position through Barrel_SpawnActorEffect_Movingai. */




struct Context;



void MovingAI_EnableTriggerActor(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 1);
}

void MovingAI_ClearActorStateActive(void *actor) {
    Rumble_SetActorStateBit(&g_world, actor, 0);
}

void MovingAI_DisableTriggerActor(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 0);
}

void MovingAI_SpawnConfiguredModelEffect(LevelActor *actor, ActorMotionState *owner, Params params, s32 kind) {
    SpawnDispatchActor *node;
    CGameStatus *settings;

    if (kind == 3031) {
        settings = &g_gameSettings.counters;
        if (settings->m_bCTFOn != 0 && settings->m_CTFPlayerWithFlag != 0) {
            return;
        }
    }
    if (kind == 5000 && g_gameSettings.controllerMode == 1) {
        kind = g_currentStagePreset->recorded + 5000;
        if (kind == 5000) {
            return;
        }
    }
    node = SetN64_SpawnModelEffect(&g_modelEffectPool, &owner->animation, kind,
                         actor->position1, *(CVector3 *)&params.v, params.w, 0.0f);
    if (node != 0) {
        node->state = 0;
        owner->remainingCount -= 1;
        Barrel_SpawnActorEffect(node, 285, node->position, 0);
    }
}

void MovingAI_SpawnConfiguredSceneEffect(LevelActor *actor, ActorMotionState *spawnState, Triple spawnPosition, Triple spawnColor,
                   s32 spawnOwner, s32 spawnId, s32 spawnCount) {
    if (Animpool_SpawnSceneEffect(&g_sceneEffectPool, spawnId, 0, spawnCount,
                      spawnOwner, *(CVector3 *)&spawnPosition,
                      actor->yaw,
                      actor->position1, *(CVector3 *)&spawnColor,
                      &spawnState->animation) != 0) {
        spawnState->remainingCount -= 1;
    }
}

void MovingAI_SpawnSceneEffectAtPosition(void *actor, ActorMotionState *spawnState, Triple effectPosition,
                   s32 spawnFlags, s32 effectKind) {
    s32 result;

    result = Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor,
                           (s32 *)&spawnState->animation, 0, effectKind,
                           ((LevelActor *)actor)->position1,
                           ((LevelActor *)actor)->rotation,
                           *(CVector3 *)&effectPosition, 0, -1, 0);
    spawnState->remainingCount -= result;
}

s32 MovingAI_CanSpawnActorKind(s32 actorKind) {
    SpawnDispatchActor *node;

    if (actorKind == 2127) {
        node = g_spawnedActorList.head;
        while (node != 0) {
            if (*node->definition == 4) {
                return 0;
            }
            node = node->next;
        }
        return Playerai_CountLocalActivePlayers(&g_playerViewRenderContext) == 0;
    }
    return 1;
}

void MovingAI_RequestMotionAnimation(void *actor, ActorMotionState *motionState, s32 animation) {
    motionState->action = -1;
    motionState->actionPending = 0;
    motionState->animation = animation;
    Gobjinst_RequestAnimationKind(actor, animation, 1);
    Gobjinst_AdvanceActorRootMotion(actor);
}

void MovingAI_InitializeMotionDispatch(LevelActor *actor, ActorMotionState *motionState) {
    s32 flags;
    s32 flags2;

    motionState->table = &g_movingMotionDispatchTable;
    motionState->update = &g_movingCallbackRomEntry;
    flags = actor->flags;
    flags |= 0x01000000;
    flags |= 0x02000000;
    flags2 = flags | 0x20000;
    actor->flags = flags2;
    if (g_gameSettings.local == 0) {
        actor->flags = flags2 | 0x10000000;
    }
    if ((actor->type == 1107) && (Cinema_GetSequenceRequest() == 111)) {
        motionState->secondaryUpdate = &g_triggeredVariantDrawRomEntry;
    }
}

void MovingAI_InitializeDeviceHealth(LevelActor *actor, Dest *deviceState) {
    deviceState->definitionHealth = ((ActorHealthDefinition *)actor->definition)->health;
    Actor_RequestActorState(actor, deviceState, 0);
    deviceState->charge = k_deviceInitialCharge;
    deviceState->initialCharge = k_deviceInitialCharge;
    if (Rumble_TestActorStateBit(&g_world, actor) == 1) {
        actor->flags &= ~0x2000;
        actor->flags &= ~0x100;
    }
}

void MovingAI_InvokeOwnerCallback(void *callbackContext, Shared_CallbackOwner *callbackOwner) {
    Shared_CallbackHook *obj = callbackOwner->hook;
    if (obj != 0) {
        Shared_VoidCallback fn = obj->callback;
        if (fn != 0) {
            ((void (*)(void *, Shared_CallbackOwner *))fn)(callbackContext, callbackOwner);
        }
    }
}

int MovingAI_GetDeviceHealth(void *ownerActor, Dest *deviceState) {
    return deviceState->definitionHealth;
}

void MovingAI_DeviceHealthNoOp(void) {
}




#if defined(VERSION_EU_X)
float k_movingaiFragment[3] = {
    6.2831855f, 0.2f, 0.2f,
};
#endif

#if defined(VERSION_DE)
void *k_MovingaiData[3] = {
    (void *)((char *)&g_triggeredVariantDrawRomEntry + 656), (void *)((char *)&g_triggeredVariantDrawRomEntry + 848), (void *)((char *)&g_triggeredVariantDrawRomEntry + 496),
};
#endif

#if defined(VERSION_US)
const unsigned int k_movingaiConstants[3] = {
    0x076D5F41, 0x6C706861, 0x54000020,
};
#endif

#if defined(VERSION_EU)
const unsigned int k_movingaiConstants[3] = {
    0x02421024, 0x1040002D, 0x24030058,
};
#endif

/** For each of the object's child slots, attach the child to the record and spawn its effect. */


void Triggered_StartTriggerAnimation(void *actor, void *motionState, Trigger *trigger) {
    MovingAI_RequestMotionAnimation(actor, motionState, trigger->trackArgument);
    ((LevelActor *)actor)->flags = ((LevelActor *)actor)->flags | 0x2100;
    Gobjinst_AdvanceActorRootMotion(actor);
    Rumble_SetActorStateBit(&g_world, actor, 0);
}

void Triggered_ClearCollisionAndActivate(Shared_Actor *actor) {
    s32 clearedFlags = actor->weaponFlags;
    clearedFlags &= ~0x2000;
    clearedFlags &= ~0x100;
    actor->weaponFlags = clearedFlags;
    Rumble_SetActorStateBit(&g_world, actor, 1);
}

void Triggered_EnableTriggeredActorState(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 1);
}

void Triggered_DeactivateForSequence(Shared_Actor *actor, s32 *sequenceFlags) {
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
    Track_RequestTrackByIds((s32)actor, (void *)trackRequest);
    actor->weaponFlags |= 0x2100;
    Rumble_SetActorStateBit(&g_world, actor, 0);
}

void Triggered_RequestTrackById(s32 trackRequest) {
    Track_RequestTrackByIds(0, (void *)trackRequest);
}

/** Copy the source byte into two fields. */
void Triggered_SetPairedDefinitionBytes(LevelActor *actor, int unusedContext, Trigger *triggerRecord) {
    void *inner = actor->definition;
    ((ActorDefinitionHeader *)inner)->first = (s8)triggerRecord->trackArgument;
    inner = actor->definition;
    ((ActorDefinitionHeader *)inner)->second = (s8)triggerRecord->trackArgument;
}

void Triggered_DrawAnimatedVariants(char *actor, void *renderContext, Rec *info) {
    int i;
    int linkedStateCount;
    void *child;

    linkedStateCount = (s8)((LevelActor *)actor)->stateE7;
    for (i = 0; i < linkedStateCount; i++) {
        child = Gobjinst_RequestAnimatedModelVariant(actor, i);
        if (child != 0) {
            info->a = child;
            info->b = child;
            GameObject_DrawActorShadow(actor, renderContext, info);
            Geometry_DrawModelResource(child, ((LevelActor *)actor)->animationMatrices, 1,
                &((LevelActor *)actor)->lighting[g_lightingBufferIndex], 0, ((LevelActor *)actor)->renderPass);
        }
    }
}


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

/* Places a rider along its path for the frame: clamps the throttle to 0..1 (eased through Defs_CosineEase unless
 * the segment is linear), offsets its base by the segment's rise and circle point, moves the rider there through
 * Graphu64_InterpolateVector, adds a bob to its height (one wave or a sum of four detuned waves by the segment's
 * bob mode), applies its shake offsets, turns the actor by the segment's yaw mode (interpolated, constant spin
 * unless held, or constant spin) and, for free segments, snaps the actor to the ground through
 * Region_GetPolygonHeight and Region_SetNodeGroupHeight. */


/* Steers an actor along path nodes, blending direction, speed and orientation as it advances waypoints. */
/* The values Triggered_AdvancePathMotion loads by address:
 * 3.0 (float, k_triggeredMinArrivalRadius)
 * 10.24 (float constant)
 * 1.0 (float, k_triggeredBlendClampLimit)
 * 1.0 (float constant)
 * 1.0 (float, k_triggeredBlendCompleteThreshold)
 * 3.1415927 (float, k_triggeredBrakeEasePi)
 * 0.5 (float, k_triggeredBrakeFraction)
 * 0.3 (float, k_triggeredStopSpeedThreshold)
 * 15.0 (float, k_triggeredPauseDurationScale)
 * 1.0 (float, g_frameElapsedTime, a variable rather than a literal)
 * 1.0 (float, k_triggeredAccelEaseUnit)
 * 3.1415927 (float, k_triggeredAccelEasePi)
 * 0.5 (float, k_triggeredAccelBlendHalf)
 * 2.670354 (float, k_triggeredStartEaseAngle)
 * 0.5 (float constant)
 * 1.0 (float, k_triggeredStartEaseOffset)
 * 0.017453294 (float constant)
 * 0.017453294 (float, k_triggeredHeadingSmoothDegToRad)
 * 0.1 (float constant)
 * 0.017453294 (float, k_triggeredSecondaryBlendDegToRad)
 * 0.017453294 (float constant)
 * 0.1 (float, k_triggeredSecondarySmoothFactor)
 * 0.017453294 (float, k_triggeredTertiaryBlendDegToRad)
 * 0.017453294 (float, k_triggeredTertiarySmoothDegToRad)
 * 0.1 (float constant)
 */


/* Chooses the option label from the signed kind byte and, for the default
 * kind, the paired variant byte. The caller's context is never read. */
struct TriggeredMotionSoundOption {
    char pad0[0x34];
    s8 variant;
    char pad35[2];
    s8 kind;
};




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
            movementSpeed = pathState->movementSpeed + (Math_Cosf((1.0f - segmentNode->speedCurvePhase) * 3.1415927f) + 1.0f)
                * (-pathState->movementSpeed * 0.5f);
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
                movementSpeed = pathState->movementSpeed + (Math_Cosf((1.0f - segmentNode->speedCurvePhase) * 3.1415927f) + 1.0f)
                    * ((segmentNode->targetSpeed - pathState->movementSpeed) * 0.5f);
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
            pathState->secondaryAngle =
                (f32) (initialSecondaryAngle + pathState->directionBlend * (segmentNode->secondaryAngleDegrees * 0.017453294f - initialSecondaryAngle));
        } else {
            currentSecondaryAngle = pathState->secondaryAngle;
            pathState->secondaryAngle = (f32) (currentSecondaryAngle + (segmentNode->secondaryAngleDegrees * 0.017453294f - currentSecondaryAngle) * 0.1f);
        }
    }
    if (segmentNode->flags.half & 0x10) {
        if ((segmentNode->flags.word & 0x820000) == 0x820000) {
            initialTertiaryAngle = pathState->initialTertiaryAngle;
            pathState->tertiaryAngle =
                (f32) (initialTertiaryAngle + pathState->directionBlend * (segmentNode->tertiaryAngleDegrees * 0.017453294f - initialTertiaryAngle));
            return;
        }
        currentTertiaryAngle = (*pathState).tertiaryAngle;
        pathState->tertiaryAngle = (f32) (currentTertiaryAngle + (segmentNode->tertiaryAngleDegrees * 0.017453294f - currentTertiaryAngle) * 0.1f);
    }
}

/** Perform no operation. */
void Triggered_PathMotionNoOp(u8 *platform, void *player) {
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

void Triggered_TestActorStateCallback(int actorHandle) {
    Rumble_TestActorStateBit(&g_world, (void *)actorHandle);
}

void Triggered_InitializeMotionState(void *object, void *state)
{
    Player *actor = object;
    ActorMotionState *motionState = state;
    f32 motionScale;
    f32 value;
    f32 scaled;
    ActorMotionResource *motionResource;
    ActorMotionDefinition *motionDefinition;

    motionResource = actor->definition;
    motionScale = k_triggeredInitialMotionScale;
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
    scaled = scaled * motionScale;
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

/* Retained data for this translation unit. */

const float k_movingAiUnit[1] = {
    1.0f,
};

#if defined(VERSION_DE)
float k_triggerDelayPercentScale = 0.00999999978f;
#endif

#if defined(VERSION_DE)
float k_triggeredInitialMotionScale = 6.28318596f;
#endif
