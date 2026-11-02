#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
#include "COMMON/REC.H"
#include "RENDER/MOVINGAI.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/WORLD.H"
#include "TYPES.H"
#include "RENDER/PLAYERMATRIX.H"
#include "include_asm.h"
#include "WORLD/INTEGERSTATE170.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/PLAYER_CONTROLLER_RESET_VIEWS.H"

extern void BuildRollMatrix(void *matrix, f32 rollAngle);



extern void CopyMatrix(float *destinationMatrix, float *sourceMatrix);

extern void ScaleMatrixLocal(void *matrix, f32 sx, f32 sy, f32 sz);

extern s32 Graphu64_LimitVectorLength(f32 *vectorComponents, f32 maximumLength);

extern void TranslateMatrix(f32 *, f32, f32, f32);

extern void SwapMatrixUpForward(void *);

s32 Rumble_TestActorStateBit(void *, void *);

void Triggered_UpdateTriggeredMotion(Player *mover, ActorMotionState *rider);

void Triggered_PositionPlatformRider(MovingPlatformActorView *, MovingPlatformMotionStateView *);

void Device_BuildPlayerMatrix(void *object, void *state) {
    Player *player = object;
    ActorMotionState *motionState = state;
    f32 orientationMatrix[16];
    f32 *matrix;

    BuildRollMatrix(orientationMatrix, motionState->pitch);
    PitchMatrix(orientationMatrix, motionState->yaw);
    YawMatrix(orientationMatrix, player->heading);
    matrix = player->matrix;
    CopyMatrix(matrix, orientationMatrix);
    ScaleMatrixLocal(matrix, player->scale.x, player->scale.y, player->scale.z);
    Graphu64_LimitVectorLength(&player->pos.x, 20000.0f);
    TranslateMatrix(matrix, player->pos.x, player->pos.y, player->pos.z);
    SwapMatrixUpForward(matrix);
}

void PlayerMatrix_UpdateTriggeredMotion(Player *mover, ActorMotionState *rider) {
    ActorMotionResource *resource = mover->definition;
    ActorMotionDefinition *body = &resource->motion;

    if (Rumble_TestActorStateBit(&g_world, mover) == 0) {
        mover->weaponFlags &= ~0x10000;
        mover->weaponFlags &= ~0x100;
        return;
    }
    mover->weaponFlags |= 0x10000;
    if (rider->hooks != 0 && rider->hooks->onStep != 0) {
        rider->hooks->onStep(mover, rider);
    }
    rider->progress += body->progressScale * g_frameElapsedTime;
    Triggered_UpdateTriggeredMotion(mover, rider);
    if (rider->mode != 4) {
        Triggered_PositionPlatformRider((void *)mover, (void *)rider);
    }
}

void PlayerMatrix_ClearUnsupportedOpenFlag(void *actor, s32 *stateFlags) {
    if (!((((struct ActorFlagsWordView *) ((s8 *) ((struct ActorDefinitionPointerView *) ((s8 *) actor))->definition))->flags) & 0x40)) {
        *stateFlags &= 0xFFFEFFFF;
    }
}

extern void Link_DispatchActorLinks(void *actor, s32 eventMask, void *eventSource);


extern void Rumble_SetActorStateBit(Shared_World *, void *, s32);

extern void Scene_SetLevelActorStateBit(void *a, unsigned short b, unsigned short c, int d);

void PlayerMatrix_UpdateOpeningDelay(void *object, void *state) {
    Player *player = object;
    ActorMotionState *motionState = state;
    s32 transitionFlags;
    ActorMotionResource *resource;
    ActorMotionDefinition *motionDefinition;
    s32 transitionAllowed;
    s32 requiredStateFlag;

    resource = player->definition;
    motionDefinition = &resource->motion;
    transitionFlags = motionDefinition->transitionFlags;
    transitionAllowed = 1;
    if (transitionFlags & 0x10) {
        requiredStateFlag = motionState->flags & 0x10000;
        transitionAllowed = (u32)0 < (u32)requiredStateFlag;
    }
    if ((transitionFlags & 0x100) && !(player->movementFlags & 0x40)) {
        transitionAllowed = 0;
    }
    if ((motionDefinition->transitionFlags & 0x400) && (player->movementFlags & 0x40)) {
        transitionAllowed = 0;
    }
    if (transitionAllowed != 0) {
        if (motionState->timer >= motionDefinition->openThreshold) {
            Actor_RequestActorState(player, motionState, 1);
        }
    } else {
        motionState->timer = 0.0f;
    }
}

void PlayerMatrix_DispatchOpenLinks(void *object, u32 *stateFlags) {
    Player *player = object;
    ActorMotionResource *resource;
    ActorMotionDefinition *motionDefinition;

    resource = player->definition;
    motionDefinition = &resource->motion;
    Link_DispatchActorLinks(player, 0x10000, player);
    if (!(motionDefinition->transitionFlags & 0x40)) {
        *stateFlags &= 0xFFFEFFFF;
    }
}

void PlayerMatrix_AdvanceOpening(void *object, void *state) {
    Player *player = object;
    ActorMotionState *motionState = state;
    ActorMotionResource *resource;
    ActorMotionDefinition *motionDefinition;
    s32 transitionFlags;
    s32 progressAllowed;

    resource = player->definition;
    motionDefinition = &resource->motion;
    transitionFlags = motionDefinition->transitionFlags;
    progressAllowed = 1;
    if (transitionFlags & 0x10000) {
        progressAllowed = (u32)(player->movementFlags & 0x40) < (u32)progressAllowed;
    }
    if ((transitionFlags & 0x4000) && !(player->movementFlags & 0x40)) {
        progressAllowed = 0;
    }
    if (player->movementFlags & 8) {
        progressAllowed = 0;
    }
    if (progressAllowed != 0) {
        motionState->speed = motionState->speed + (g_frameElapsedTime / motionDefinition->transitionTime);
    }
    if (motionState->speed >= k_motionOpenCompletionSpeed) {
        Actor_RequestActorState(player, motionState, 2);
    }
}

void PlayerMatrix_ClearUnsupportedCloseFlag(void *actor, s32 *stateFlags) {
    if (!((((struct ActorFlagsWordView *) ((s8 *) ((struct ActorDefinitionPointerView *) ((s8 *) actor))->definition))->flags) & 0x80)) {
        *stateFlags &= 0xFFFDFFFF;
    }
}

void PlayerMatrix_UpdateClosingDelay(void *object, void *state) {
    Player *player = object;
    ActorMotionState *motionState = state;
    s32 transitionFlags;
    ActorMotionResource *resource;
    ActorMotionDefinition *motionDefinition;
    s32 transitionAllowed;
    s32 requiredCloseFlag;

    resource = player->definition;
    motionDefinition = &resource->motion;
    transitionFlags = motionDefinition->transitionFlags;
    transitionAllowed = 1;
    if (transitionFlags & 0x20) {
        requiredCloseFlag = motionState->flags & 0x20000;
        transitionAllowed = (u32)0 < (u32)requiredCloseFlag;
    }
    if ((transitionFlags & 0x200) && !(player->movementFlags & 0x40)) {
        transitionAllowed = 0;
    }
    if ((motionDefinition->transitionFlags & 0x800) && (player->movementFlags & 0x40)) {
        transitionAllowed = 0;
    }
    if (transitionAllowed != 0) {
        if (motionState->timer >= motionDefinition->closeThreshold) {
            Actor_RequestActorState(player, motionState, 3);
        }
    } else {
        motionState->timer = 0.0f;
    }
}

void PlayerMatrix_DispatchCloseLinks(void *object, u32 *stateFlags) {
    Player *player = object;
    ActorMotionResource *resource;
    ActorMotionDefinition *motionDefinition;

    resource = player->definition;
    motionDefinition = &resource->motion;
    Link_DispatchActorLinks(player, 0x20000, player);
    if (!(motionDefinition->transitionFlags & 0x80)) {
        *stateFlags &= 0xFFFDFFFF;
    }
}

void PlayerMatrix_AdvanceClosing(void *object, void *state) {
    Player *player = object;
    ActorMotionState *motionState = state;
    ActorMotionResource *resource;
    ActorMotionDefinition *motionDefinition;
    s32 transitionFlags;
    s32 progressAllowed;

    resource = player->definition;
    motionDefinition = &resource->motion;
    transitionFlags = motionDefinition->transitionFlags;
    progressAllowed = 1;
    if (transitionFlags & 0x20000) {
        progressAllowed = (u32)(player->movementFlags & 0x40) < (u32)progressAllowed;
    }
    if ((transitionFlags & 0x8000) && !(player->movementFlags & 0x40)) {
        progressAllowed = 0;
    }
    if (player->movementFlags & 8) {
        progressAllowed = 0;
    }
    if (progressAllowed != 0) {
        motionState->speed = motionState->speed - (g_frameElapsedTime / motionDefinition->transitionTime);
    }
    if (motionState->speed <= 0.0f) {
        Actor_RequestActorState(player, motionState, 0);
    }
}

void PlayerMatrix_RequestOpen(struct Shared_Actor *actor, int *motionFlags) {
    actor->weaponFlags |= 0x2100;
    *motionFlags |= 0x10000;
    Actor_RequestActorState(actor, motionFlags, 1);
}

void PlayerMatrix_RequestClose(struct Shared_Actor *actor, int *motionFlags) {
    actor->weaponFlags |= 0x2100;
    *motionFlags |= 0x20000;
    Actor_RequestActorState(actor, motionFlags, 3);
}

void PlayerMatrix_ActivateMotion(struct Shared_Actor *actor) {
    Rumble_SetActorStateBit(&g_world, actor, 1);
    actor->weaponFlags |= 0x100;
}

void PlayerMatrix_EnableEventActor(void *event) {
    ActorMotionEvent *actorMotionEvent = event;
    Scene_SetLevelActorStateBit(&g_world, actorMotionEvent->id, actorMotionEvent->key, 1);
}

void PlayerMatrix_DeactivateMotion(struct Shared_Actor *actor) {
    Rumble_SetActorStateBit(&g_world, actor, 0);
    actor->weaponFlags &= ~0x100;
}

void PlayerMatrix_DisableEventActor(void *event) {
    ActorMotionEvent *actorMotionEvent = event;
    Scene_SetLevelActorStateBit(&g_world, actorMotionEvent->id, actorMotionEvent->key, 0);
}

/** Set flags 0x2100 in the word at offset 0x100. */
void PlayerMatrix_EnableCollisionFlags(void *object) {
    Player *player = object;
    player->weaponFlags |= 0x2100;
}

void PlayerMatrix_MarkOpenAndResetTimer(LevelActor *actor, ActorMotionState *motionState) {
    motionState->flags = (s32) (motionState->flags | 0x10000);
    actor->flags = (s32) (actor->flags | 0x2100);
    motionState->openTimer = 0;
}

/** Set the fixed flags on the supplied object and word. */
void PlayerMatrix_MarkCloseRequested(char *object, unsigned int *flags) {
    Player *actor = (void *)object;
    *flags |= 0x20000;
    actor->weaponFlags |= 0x2100;
}

              /* size 0x0 */

s32 PlayerMatrix_ClearCollisionBit(void *player) {
    Player *actor = player;
    s32 updatedFlags;

    updatedFlags = actor->weaponFlags & ~0x2000;
    actor->weaponFlags = updatedFlags;
    return updatedFlags;
}

#if defined(VERSION_EU_X)
/* Zero word ending PlayerMatrix_ClearCollisionBit's object; no instruction reads it. */
unsigned int g_playerMatrixClearCollisionBitZeroTail[1] = {
    0x00000000,
};
#endif

