#include "include_asm.h"
#include "COMMON/OBJRECAT30.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHARED_VOIDCALLBACK.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/REC.H"
#include "COMMON/LISTHEADER.H"
#include "TYPES.H"
#include "COMMON/EFFECTCONTRIBUTION.H"
#include "LEVEL/ACTIONHIT.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"

extern void Events_DispatchCallback(void *, void *, s32, CVector3, ResourceManagerState);
typedef struct BreakableContactRule {
    u32 flags;
    f32 limit;
    s8 damageFactor;
} BreakableContactRule;

typedef struct BreakableContactState {
    u8 pad0[0x40];
    f32 elapsed;
    u8 pad44[0x20];
    f32 limit;
    u8 pad68[0x62];
    s8 team;
    s8 active;
} BreakableContactState;

/* Apply the descriptor hit rule, then update the contact response timer. */
void Action_UpdateBreakableHit(BreakableHitContext *ctx, BreakableContactState *hit) {
    BreakableContactRule *rule = (BreakableContactRule *)(&((ActorDefinitionHeader *)ctx->descriptor)->flags);
    ResourceManagerState eventState;
    f32 damageScale;
    s32 triggerResponse;
    s8 team;
    if (rule->damageFactor != -1) {
        damageScale = rule->damageFactor * (1.0f / 127.0f);
        if (ctx->forced == 1) {
            triggerResponse = 1;
        } else {
            team = hit->team;
            if (ctx->teamIdFirst != team || ctx->teamIdSecond != team) {
                triggerResponse = 0;
            } else if (hit->active != 0 && !(ctx->flags & 0x400)) {
                triggerResponse = 1;
            } else {
                if (ctx->hitCount < 3 && (ctx->flags & 0x400)) {
                    triggerResponse = ctx->flaggedHitCount * damageScale <= ctx->flaggedHitLimit;
                } else {
                    triggerResponse = ctx->hitCount * damageScale <= ctx->hitLimit;
                }
            }
        }
        if (triggerResponse) {
            eventState.active = 0;
            Events_DispatchCallback(ctx, ctx, 6, ctx->position, eventState);
            Rumble_SetActorStateBit(&g_world, ctx, 1);
        }
    }
    if ((rule->flags & 1) && hit->active != 0) {
        f32 timeLimit = rule->limit;
        if (timeLimit == 0.0f || hit->limit < timeLimit) {
            if (hit->limit == 0.0f) {
                hit->elapsed = 0.0f;
            }
            hit->limit = timeLimit;
        }
    }
    if (hit->limit != 0.0f && hit->limit <= hit->elapsed) {
        Actor_RequestActorState(ctx, (BreakableHitStateView *)hit, 1);
    }
}

/* Destroys a breakable object after a hit: when its descriptor has a damage factor at 0x1D, scaled
   by k_breakableDamageScale, and the object is forced at 0xE6, or the hit's team byte at 0xCA matches both ids at
   0x108 and 0x10A and either the hit at 0xCB bypasses an object without flag 0x400 or the scaled count
   reaches its limit (the count at 0x12C against 0x134 while flagged 0x400 below three hits at 0x10C,
   otherwise the hits against 0x104), it raises event 7 at its position through Events_DispatchCallback and
   releases it through Rumble_SetActorStateBit_Actionhit. Written from its own assembly with the destroy decision as an
   if/else chain on a byte-sized damage factor. */









extern s32 Rumble_TestActorStateBit(void *, void *);




extern void Events_DispatchCallback(void *sourceActor, void *targetActor, s32 eventKind,
                          CVector3 eventPosition, ResourceManagerState eventParams);

extern void Scene_SetLevelActorStateBit(void *a, unsigned short b, unsigned short c, int d);

void Action_ResolveBreakableHit(void *breakableHitContext, BreakableHitStateView *hitState) {
    ResourceManagerState local;
    s8 factor;
    f32 scale;
    s32 destroy;
    s8 team;

    factor = ((struct BreakableDamageScaleView *) ((BreakableHitContext *) breakableHitContext)->descriptor)->damageScale;
    if (factor == -1) {
        return;
    }
    scale = factor * k_breakableDamageScale;
    if (((BreakableHitContext *)(breakableHitContext))->forced == 1) {
        destroy = 1;
    } else {
        team = hitState->team;
        if (((BreakableHitContext *)(breakableHitContext))->teamIdFirst != team || ((BreakableHitContext *)(breakableHitContext))->teamIdSecond != team) {
            destroy = 0;
        } else if (hitState->active != 0 && !(((BreakableHitContext *)(breakableHitContext))->flags & 0x400)) {
            destroy = 1;
        } else if (((BreakableHitContext *)(breakableHitContext))->hitCount < 3 && (((BreakableHitContext *)(breakableHitContext))->flags & 0x400)) {
            destroy = ((BreakableHitContext *)(breakableHitContext))->flaggedHitCount * scale <= ((BreakableHitContext *)(breakableHitContext))->flaggedHitLimit;
        } else {
            destroy = ((BreakableHitContext *)(breakableHitContext))->hitCount * scale <= ((BreakableHitContext *)(breakableHitContext))->hitLimit;
        }
    }
    if (destroy) {
        local.active = 0;
        Events_DispatchCallback(breakableHitContext, breakableHitContext, 7, ((BreakableHitContext *)(breakableHitContext))->position, local);
        Rumble_SetActorStateBit(&g_world, breakableHitContext, 0);
    }
}

void Action_SetEnterHandler(void *unused0, Dest *dispatchState) {
    dispatchState->table = &g_actionEnterDispatchTable;
    dispatchState->enter = &g_actionEnterRomEntry;
}

void Action_ToggleActorState(void *actor, void *requestContext) {
    s32 different = Rumble_TestActorStateBit(&g_world, actor) != 1;

    if (different == 0) {
        Actor_RequestActorState(actor, requestContext, 0);
    } else {
        Actor_RequestActorState(actor, requestContext, 1);
    }
}

void Action_InvokeOwnerCallback(void *callbackContext, Shared_CallbackOwner *callbackOwner) {
    Shared_CallbackHook *obj = callbackOwner->hook;
    if (obj != 0) {
        Shared_VoidCallback fn = obj->callback;
        if (fn != 0) {
            ((void (*)(void *, Shared_CallbackOwner *))fn)(callbackContext, callbackOwner);
        }
    }
}

void Action_ActivateActorAndClearMotion(void *actor, ActorMotionState *motionState) {
    ResourceManagerState local;
    Shared_World *flag;

    local.active = 0;
    flag = &g_world;
    Rumble_SetActorStateBit(flag, actor, 1);
    Link_DispatchActorLinks(actor, 0x4000, actor);
    motionState->speed = 0;
    Fx_RecycleOwnerParticles(&g_actorParticleScene, (s32)actor);
    if (flag->mode != 4) {
        Events_DispatchCallback(actor, actor, 6,
                      ((LevelActor *)actor)->position0, local);
        ((LevelActor *)actor)->flags |= 0x08000000;
    }
}

void Action_DeactivateBreakable(BreakableHitContext *breakableHitContext) {
    ResourceManagerState local;
    Shared_World *flag;

    local.active = 0;
    flag = &g_world;
    Rumble_SetActorStateBit(flag, breakableHitContext, 0);
    Link_DispatchActorLinks(breakableHitContext, 0x8000, breakableHitContext);
    Fx_RecycleOwnerParticles(&g_actorParticleScene, (s32)breakableHitContext);
    if (flag->mode != 4) {
        Events_DispatchCallback(breakableHitContext, breakableHitContext, 7,
                      breakableHitContext->position, local);
        breakableHitContext->flags |= 0x08000000;
    }
}

void Action_RequestInactiveState(void *a, void *b) {
    Actor_RequestActorState(a, b, 0); }

void Action_EnableTriggerActor(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 1);
}

void Action_RequestActiveState(void *a, void *b) {
    Actor_RequestActorState(a, b, 1); }

void Action_DisableTriggerActor(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 0);
}




int Action_IsActorStateActive(int actor) {
    return Rumble_TestActorStateBit(&g_world, actor) == 1;
}

/** Submit an object's three-word record, then attach it in mode one. */
void Action_NotifyActorActivated(LevelActor *actor) {
    ResourceManagerState pair;

    pair.active = 0;
    Events_DispatchCallback(actor, actor, 6, actor->position0, pair);
    Rumble_SetActorStateBit(&g_world, actor, 1);
}

/** Submit an object's three-word record, then attach it to the global owner. */
void Action_NotifyActorDeactivated(LevelActor *actor) {
    ResourceManagerState pair;

    pair.active = 0;
    Events_DispatchCallback(actor, actor, 7, actor->position0, pair);
    Rumble_SetActorStateBit(&g_world, actor, 0);
}

/** Update the floating state at offsets 0x40 and 0x64 under its range rules. */
void Action_RaiseMotionSpeed(void *unused, char *object, float value) {
    ActorMotionState *state = (void *)object;
    if (value == 0.0f || state->speed < value) {
        if (state->speed == 0.0f) {
            state->timer = 0.0f;
        }
        state->speed = value;
    }
}

/** Report whether the actor on the given cell is within the scaled trigger distance. */




int Action_TestScaledTriggerRange(ActorTriggerRangeView *actor, Cell *cell, float scale) {
    if (actor->always == 1) {
        return 1;
    }
    if (actor->x == (signed char)cell->pos && actor->y == (signed char)cell->pos) {
        if (cell->open != 0 && !(actor->flags & 0x400)) {
            return 1;
        }
        if (actor->level < 3 && (actor->flags & 0x400)) {
            if (actor->altLevel * scale <= actor->altRange) {
                return 1;
            }
            return 0;
        }
        if (actor->level * scale <= actor->range) {
            return 1;
        }
    }
    return 0;
}


