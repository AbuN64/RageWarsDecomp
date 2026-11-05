#include "Ai/Devices/Actionhit/actionhit.h"
#include "Common/game_session.h"
#include "include_asm.h"
#include "Common/breakable_hits.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/shared_voidcallback.h"
#include "Common/level_actor.h"
#include "Common/world.h"
#include "Common/rec.h"
#include "Common/listheader.h"
#include "types.h"
#include "Common/effectcontribution.h"
#include "Level/actionhit.h"
#include "Weapons/actor_requestactorstate.h"
#include "Common/animationtriggerdefinition.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Engine/rumble_setactorstatebit.h"
#include "Engine/Events/events_applydamageevent.h"

typedef struct BreakableContactRule {
    u32 flags;
    f32 limit;
    s8 damageFactor;
} BreakableContactRule;

/* Apply the descriptor hit rule, then update the contact response timer. */
void Action_UpdateBreakableHit(BreakableHitContext *ctx, ActorMotionState *hit) {
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
            team = hit->contactTeam;
            if (ctx->teamIdFirst != team || ctx->teamIdSecond != team) {
                triggerResponse = 0;
            } else if (hit->actionPending != 0 && !(ctx->flags & 0x400)) {
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
    if ((rule->flags & 1) && hit->actionPending != 0) {
        f32 timeLimit = rule->limit;
        if (timeLimit == 0.0f || hit->speed < timeLimit) {
            if (hit->speed == 0.0f) {
                hit->timer = 0.0f;
            }
            hit->speed = timeLimit;
        }
    }
    if (hit->speed != 0.0f && hit->speed <= hit->timer) {
        Actor_RequestActorState(ctx, (BreakableHitStateView *)hit, 1);
    }
}

/* Destroys a breakable object after a hit: when its descriptor has a damage factor, scaled
   by k_breakableDamageScale, and the object is forced, or the hit's team byte matches both ids at
   0x108 and 0x10A and either the hit bypasses an object without flag 0x400 or the scaled count
   reaches its limit (the count against the flagged hit limit while flagged 0x400 below three hits,
   otherwise the hits against the plain hit limit), it raises event 7 at its position through Events_DispatchCallback and
   releases it through Rumble_SetActorStateBit_Actionhit. Written from its own assembly with the destroy decision as an
   if/else chain on a byte-sized damage factor. */


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
            destroy = ((BreakableHitContext *)(breakableHitContext))->flaggedHitCount
                * scale <= ((BreakableHitContext *)(breakableHitContext))->flaggedHitLimit;
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

void Action_SetEnterHandler(void *ownerActor, Dest *dispatchState) {
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
    Fx_RecycleOwnerParticles(&g_gameSession.hud.actors, (s32)actor);
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
    Fx_RecycleOwnerParticles(&g_gameSession.hud.actors, (s32)breakableHitContext);
    if (flag->mode != 4) {
        Events_DispatchCallback(breakableHitContext, breakableHitContext, 7,
                      breakableHitContext->position, local);
        breakableHitContext->flags |= 0x08000000;
    }
}

void Action_RequestInactiveState(void *actor, void *eventSource) {
    Actor_RequestActorState(actor, eventSource, 0); }

void Action_EnableTriggerActor(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 1);
}

void Action_RequestActiveState(void *actor, void *eventSource) {
    Actor_RequestActorState(actor, eventSource, 1); }

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

/** Update the floating state under its range rules. */
void Action_RaiseMotionSpeed(void *ownerActor, char *object, float value) {
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

#if defined(VERSION_US)
const char s_PolycolOshVerteText[8] = "oshVerte";
#endif
