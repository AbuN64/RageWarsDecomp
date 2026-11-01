#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/OBJ.H"
#include "COMMON/REC.H"
#include "TYPES.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "COMMON/LONE/g_currentStagePreset.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHARED_VOIDCALLBACK.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/LISTHEADER.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "RENDER/MOVINGAI.H"
#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"
#include "include_asm.h"

/* 80204E78_7.CPP */
/* 80204E78_7.CPP */

extern s32 Rumble_TestActorStateBit(void *, void *);

void MovingAI_ChooseTriggerDelay(void *levelActor, void *actorMotionState) {
    LevelActor *actor = levelActor;
    ActorMotionState *motion = actorMotionState;
    AnimationTriggerResource *resource;
    AnimationTriggerDefinition *base;
    char *ctx;
    f32 result;
    s32 count;
    s32 delayPercent;
    f64 unsignedDelayPercent;
    f32 scaled;

    resource = (void *)actor->definition;
    base = &resource->trigger;
    result = Graphu64_RandomBetween(base->delayMinimum, base->delayMaximum);
    motion->speed = result;
    ctx = (char *) &g_gameSettings;
    if (((GameModeEnableView *)(ctx))->local != 0) {
        count = *(s32 *) (ctx - (((char *)&((Shared_MenuData *)0)->game - (char *)0) - ((char *)&((Shared_MenuData *)0)->sessionOptionResetMode - (char *)0)));
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

void MovingAI_RequestInactiveOnEvent(void *a, struct WeaponEventSource *b) {
    if (b->eventEnabled != 0) {
        Actor_RequestActorState(a, b, 0);
    }
}

int MovingAI_IsActorStateActive(int actor) {
    return Rumble_TestActorStateBit(&g_world, actor) == 1;
}

void MovingAI_SetActorStateActive(void *actor) {
    Rumble_SetActorStateBit(&g_world, actor, 1);
}

/* 80206258.CPP */
extern void Scene_SetLevelActorStateBit(void *a, unsigned short b, unsigned short c, int d);

/* Spawns effect kind at an actor's position through SetN64_SpawnModelEffect in g_modelEffectPool's list: kind 0xBD7
   is skipped while both of g_matchRoundCounters's flags at 0x78 and 0x80 are set, and kind 0x1388 is offset by
   the variant byte at g_currentStagePreset when option g_gameControllerMode is 1 (skipped for variant 0); a spawned node
   has its word at 0x1A0 cleared, takes one charge from the owner and starts effect 0x11D at its own
   position through Barrel_SpawnActorEffect_Movingai. */

extern SpawnDispatchActor *SetN64_SpawnModelEffect(char *, void *, s32, CVector3, Triple, s32, f32);

extern s32 Animpool_SpawnSceneEffect(void *scene, s32 effectId, s32 variant, s32 count,
                         s32 owner, Triple position, f32 scale, CVector3 direction,
                         Triple color, void *ref);

extern char g_actorParticleEffectSystem;

extern char g_playerViewRenderContext;

struct Context;
extern void *Playerai_CountLocalActivePlayers(struct Context *context);

extern s32 Gobjinst_RequestAnimationKind(void *a, s32 c, s32 flag);

extern s32 Cinema_GetSequenceRequest(void);

extern MovingActorGameFlagView g_motionVisibilitySettings;

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
        kind = *g_currentStagePreset + 5000;
        if (kind == 5000) {
            return;
        }
    }
    node = SetN64_SpawnModelEffect(&g_modelEffectPool, &owner->animation, kind,
                         actor->position1, params.v, params.w, 0.0f);
    if (node != 0) {
        node->state = 0;
        owner->remainingCount -= 1;
        Barrel_SpawnActorEffect(node, 285, node->position, 0);
    }
}

void MovingAI_SpawnConfiguredSceneEffect(LevelActor *actor, ActorMotionState *spawnState, Triple spawnPosition, Triple spawnColor,
                   s32 spawnOwner, s32 spawnId, s32 spawnCount) {
    if (Animpool_SpawnSceneEffect(&g_sceneEffectPool, spawnId, 0, spawnCount,
                      spawnOwner, spawnPosition,
                      actor->yaw,
                      actor->position1, spawnColor,
                      &spawnState->animation) != 0) {
        spawnState->remainingCount -= 1;
    }
}

void MovingAI_SpawnSceneEffectAtPosition(void *actor, ActorMotionState *spawnState, Triple effectPosition,
                   s32 unused5, s32 effectKind) {
    s32 result;

    result = Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor,
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

void MovingAI_RequestMotionAnimation(void *a, ActorMotionState *b, s32 c) {
    b->action = -1;
    b->actionPending = 0;
    b->animation = c;
    Gobjinst_RequestAnimationKind(a, c, 1);
    Gobjinst_AdvanceActorRootMotion(a);
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
    if (g_motionVisibilitySettings.gameFlag == 0) {
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

int MovingAI_GetDeviceHealth(void *unused0, Dest *deviceState) {
    return deviceState->definitionHealth;
}

void MovingAI_DeviceHealthNoOp(void) {
}

/* 800C6BC4.CPP */

/* 80204E78_7_DATA3.CPP */
/* 800C6BD0.CPP */
/* ROM-grounded data: src/k_MovingaiOneWords_us_rev1.c */
const float k_MovingaiOneWords[1] = {
    1.0f,
};

#if defined(VERSION_EU_X)
float k_MovingaiEncodedWordsBlock1[3] = {
    6.2831855f, 0.2f, 0.2f,
};
#endif

#if defined(VERSION_DE)
void *k_MovingaiEncodedWords[3] = {
    (void *)((char *)&g_triggeredVariantDrawRomEntry + 656), (void *)((char *)&g_triggeredVariantDrawRomEntry + 848), (void *)((char *)&g_triggeredVariantDrawRomEntry + 496),
};
#endif

/* 800C1A14.CPP */
#if defined(VERSION_US)
const unsigned int k_movingaiConstantWords[3] = {
    0x076D5F41, 0x6C706861, 0x54000020,
};
#endif

/* 800C1D84.CPP */
#if defined(VERSION_EU)
const unsigned int k_movingaiConstantWordsBlock1[3] = {
    0x02421024, 0x1040002D, 0x24030058,
};
#endif
