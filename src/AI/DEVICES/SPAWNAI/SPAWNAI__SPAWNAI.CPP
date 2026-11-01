#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "COMMON/LONE/g_currentStagePreset.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/OBJRECAT30.H"
#include "COMMON/REC.H"
#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/LISTHEADER.H"
#include "COMMON/RESULTS.H"
#include "TYPES.H"
#include "COMMON/INTEGERSTATE1250.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "ENGINE/LISTS.H"
#include "include_asm.h"

/* Dispatch configured object, particle, or weighted-choice spawns and update the owner count. */

extern f32 Region_GetPolygonHeight(Node75 *node, f32 x, f32 z);

extern void *Scene_GetActorDefinition(void *world, s32 index);

extern int Scene_GetModelIdAtIndex(void *world, int modelIndex);

struct Context;
extern s32 Playerai_CountLocalActivePlayers(struct Context *context);

extern int Playerai_GetFirstPlayer(void *world);

extern void Lists_ClearWeightedTable(WeightedTable *object);

extern SceneEffect *Animpool_SpawnSceneEffect(void *scene, s32 id, s32 variant, s32 count, s32 owner, CVector3 position, f32 scale, CVector3 direction, CVector3 color, s32 *ref);

extern s32 Particle_SpawnEffectGroup(EffectSystem *sys, EffectActor *source, EffectActor *owner, s32 *refCount, s32 followTarget, s32 kind, CVector3 inheritedVelocity, CQuatern rotation, CVector3 pos, CVector3 *aim, s32 requestedMode, s32 spawnFlags);

extern void *SetN64_SpawnModelEffect(char *container, s32 *referenceCounter, s32 effectId, CVector3 rotation, CVector3 position, s32 effectOwner, f32 initialLifetime);

extern char g_actorParticleEffectSystem[];

static __inline__ SpawnChoice *spawnTable0(void) {
    extern SpawnChoice g_spawnChoiceTableZero[];
    return g_spawnChoiceTableZero;
}

static __inline__ SpawnChoice *spawnTable1(void) {
    extern SpawnChoice g_spawnChoiceTableZero[];
    return g_spawnChoiceTableZero + 1;
}

static __inline__ SpawnChoice *spawnTable2(void) {
    extern SpawnChoice g_spawnChoiceTableTwo[];
    return g_spawnChoiceTableTwo;
}

static __inline__ SpawnChoice *spawnTable3(void) {
    extern SpawnChoice g_spawnChoiceTableThree[];
    return g_spawnChoiceTableThree;
}

static __inline__ SpawnChoice *spawnTable4(void) {
    extern SpawnChoice g_spawnChoiceTableFour[];
    return g_spawnChoiceTableFour;
}

static __inline__ SpawnChoice *spawnTable5(void) {
    extern SpawnChoice g_spawnChoiceTableFive[];
    return g_spawnChoiceTableFive;
}

static __inline__ SpawnChoice *spawnTable6(void) {
    extern SpawnChoice g_spawnChoiceTableSix[];
    return g_spawnChoiceTableSix;
}

static __inline__ s32 spawnBlocked(void) {
    return g_gameSettings.counters.m_CTFPlayerWithFlag;
}

static __inline__ s32 available(s32 id) {
    SpawnDispatchActor *actor;
    if (id == 2127) {
        actor = g_spawnedActorList.head;
        while (actor) {
            if (*actor->definition == 4) {
                return 0;
            }
            actor = actor->next;
        }
        return Playerai_CountLocalActivePlayers(&g_playerViewRenderContext) == 0;
    }
    return 1;
}

static __inline__ s32 availableChoice(s32 id) {
    SpawnDispatchActor *actor;
    if (id != 2127) {
        id = 1;
        goto done;
    }
    actor = g_spawnedActorList.head;
    while (actor) {
        if (*actor->definition == 4) {
            return id = 0;
        }
        actor = actor->next;
    }
    return id = Playerai_CountLocalActivePlayers(&g_playerViewRenderContext) == 0;
done:
    return id;
}

static __inline__ s32 copySpawnId(s32 id) {
    if (id < 0) {
        return id;
    }
    return id;
}

static __inline__ void spawn(SpawnDispatchObject *object, s32 id,
        CVector3 position, SpawnDispatchOwner *owner, void *world) {
    SpawnDispatchActor *actor;
    id = copySpawnId(id);
    if (id == 3031 && g_gameSettings.counters.m_bCTFOn && spawnBlocked()) {
        return;
    }
    if (id == 5000 && g_gameSettings.controllerMode == 1) {
        id = *g_currentStagePreset + 5000;
        if (id == 5000) {
            return;
        }
    }
    actor = SetN64_SpawnModelEffect(&g_modelEffectPool, &owner->spawn, id,
        object->rotation, position, (s32)world, 0);
    if (actor) {
        actor->state = 0;
        owner->remaining--;
        Barrel_SpawnActorEffect(actor, 285, actor->position, 0);
    }
}

static __inline__ void spawnSelected(SpawnDispatchObject *object, SpawnDispatchOwner *owner, s32 id,
        void *world, CVector3 position) {
    SpawnDispatchActor *actor;
    if (id == 3031 && g_gameSettings.counters.m_bCTFOn && spawnBlocked()) {
        return;
    }
    if (id == 5000 && g_gameSettings.controllerMode == 1) {
        id = *g_currentStagePreset + 5000;
        if (id == 5000) {
            return;
        }
    }
    actor = SetN64_SpawnModelEffect(&g_modelEffectPool, &owner->spawn, id,
        object->rotation, position, (s32)world, 0);
    if (actor) {
        actor->state = 0;
        owner->remaining--;
        Barrel_SpawnActorEffect(actor, 285, actor->position, 0);
    }
}

static __inline__ void spawnParticles(SpawnDispatchObject *object, SpawnDispatchOwner *owner,
        CVector3 position, CVector3 velocity, s32 type, s32 *entry, void *world) {
    if (Animpool_SpawnSceneEffect(&g_sceneEffectPool, type, 0, (s32)entry, (s32)world, position,
            object->scale, object->rotation, velocity, &owner->spawn)) {
        owner->remaining--;
    }
}

static __inline__ void spawnGroup(SpawnDispatchObject *object, SpawnDispatchOwner *owner,
        CVector3 position, s32 count) {
    owner->remaining -= Particle_SpawnEffectGroup((EffectSystem *)g_actorParticleEffectSystem, (EffectActor *)object, (EffectActor *)object, &owner->spawn,
            0, count, object->rotation, object->motion, position, 0, -1, 0);
}

extern s32 Rumble_TestActorStateBit(void *, void *);

/* Retained ROM words preceding this unit's generated jump table. */
#if defined(VERSION_EU)
const u32 k_spawnaiConstantWords[2] = {
    0x00031880, 0x96230004,
};
#endif

void SpawnAI_DispatchSpawnChoice(SpawnDispatchObject *object, SpawnDispatchOwner *owner) {
    CVector3 position;
    CVector3 velocity;
    WeightedTable picker;
    WeightedTable otherPicker;
    void *world;
    SpawnDefinition *definition;
    s32 *entry;
    SpawnChoice *choice;
    SpawnDispatchActor *actor;
    s32 first, second;
    s32 third;
    s32 id;
    s32 context;
    f32 height;

    definition = &object->definition->spawn;
    position = object->position;
    world = object->world;
    if (world) {
        height = Region_GetPolygonHeight(world, object->position.x, object->position.z);
        if (position.y < height) {
            position.y = height;
        }
    }
    switch (definition->kind) {
    case 0:
        entry = Scene_GetActorDefinition(&g_world, definition->selector);
        switch (*entry) {
        case 8:
            id = Scene_GetModelIdAtIndex(&g_world, definition->id);
            if (!available(id)) {
                return;
            }
            spawn(object, id, position, owner, world);
            return;
        case 1: case 2: case 3: case 4: case 5:
        case 6: case 7: case 9: case 10:
            velocity.x = definition->velocity.x;
            velocity.y = definition->velocity.y;
            velocity.z = definition->velocity.z;
            spawnParticles(object, owner, position, velocity, definition->id, entry, world);
            break;
        }
        return;
    case 1:
        spawnGroup(object, owner, position, definition->count);
        return;
    case 2:
        first = -1;
        second = -1;
        third = -1;
        if (((SpawnDispatchConfig *)&g_gameSettings)->enabled) {
            if (definition->flags & 0x20) {
                first = (s16)Lists_ChooseWeightedEntry((s16 *)spawnTable1());
            }
            if (definition->flags & 0x40) {
                second = (s16)Lists_ChooseWeightedEntry((s16 *)spawnTable4());
            }
            if (definition->flags & 0x80) {
                Lists_ClearWeightedTable(&otherPicker);
                choice = spawnTable6();
                while (choice->id != -1) {
                    if (availableChoice(choice->id)) {
                        Lists_AppendWeightedEntry(&otherPicker, choice->id, choice->weight);
                    }
                    choice++;
                }
                third = (s16)Lists_ChooseWeightedTableEntry(&otherPicker);
            }
        } else {
            /* Configuration lies 0x1288 bytes into the shared runtime block. */
            context = Playerai_GetFirstPlayer((u8 *)&g_gameSettings - ((char *)&((Shared_MenuData *)0)->game - (char *)0));
            if (!context) {
                return;
            }
            if (definition->flags & 0x20) {
                Lists_ClearWeightedTable(&picker);
                choice = spawnTable0();
                while (choice->id != -1) {
                    if (Player_IsAmmoPickupBelowCapacity((void *)context, choice->id)) {
                        Lists_AppendWeightedEntry(&picker, choice->id, choice->weight);
                    }
                    choice++;
                }
                first = (s16)Lists_ChooseWeightedTableEntry(&picker);
            }
            if (definition->flags & 0x40) {
                Lists_ClearWeightedTable(&picker);
                choice = spawnTable2();
                if (g_world.visibilityEnabled) {
                    choice = spawnTable3();
                }
                while (choice->id != -1) {
                    if (Playerai_IsHealthBelowThreshold((void *)context, choice->id)) {
                        Lists_AppendWeightedEntry(&picker, choice->id, choice->weight);
                    }
                    choice++;
                }
                second = (s16)Lists_ChooseWeightedTableEntry(&picker);
            }
            if (definition->flags & 0x80) {
                third = (s16)Lists_ChooseWeightedEntry((s16 *)spawnTable5());
            }
        }
        Lists_ClearWeightedTable(&picker);
        if (first != -1) {
            Lists_AppendWeightedEntry(&picker, first, 100);
        }
        if (second != -1) {
            Lists_AppendWeightedEntry(&picker, second, 100);
        }
        if (third != -1) {
            Lists_AppendWeightedEntry(&picker, third, 100);
        }
        if (!picker.count) {
            return;
        }
        id = (s16)Lists_ChooseWeightedTableEntry(&picker);
        spawnSelected(object, owner, id, world, position);
        return;
    }
}

void SpawnAI_InitializeActorDispatch(void *levelActor, void *actorMotionState) {
    LevelActor *actor = levelActor;
    ActorMotionState *state = actorMotionState;
    BreakableDefinition *inner = (BreakableDefinition *)actor->definition;

    state->table = &g_spawnActorDispatchTable;
    state->update = &g_spawnCallbackRomEntry;
    if ((actor->type == 1604) ||
        (inner->flags & 8)) {
        actor->flags &= ~0x2000;
    }
}

/* Starts an eligible actor action with a random delay and descriptor duration, applies its flags and callback, then clears the pending flag when required. */
void SpawnAI_InitializeActionDelay(ActorTriggerDescriptorView *actor, Action *action) {
    ActionInfo *info = &actor->desc->info;
    if ((info->flags & 0x10) && (g_gameSettings.local == 0 || g_gameSettings.mode1E != 1)) {
        actor->flags &= ~0x100;
        return;
    }
    action->delay = Graphu64_RandomBetween(k_spawnActionMinimumDelay, k_spawnActionMaximumDelay);
    action->timer = 0;
    action->duration = info->duration;
    if (actor->model == 1604 || (info->flags & 8)) actor->flags &= ~0x2000;
    Actor_RequestActorState(actor, action, 0);
    if (!(info->flags & 0x10) || g_gameSettings.mode1E == 1) return;
    actor->flags &= ~0x100;
}

void SpawnAI_InvokeActiveActorCallback(void *actor, ActorLinkCallbackEvent *callbackRecord) {
    CallbackHolder *holder;
    s32 different;

    different = Rumble_TestActorStateBit(&g_world, actor) != 1;
    if (different == 0) {
        holder = callbackRecord->holder;
        if ((holder != 0) && (holder->callback != 0)) {
            holder->callback(actor, callbackRecord);
        }
    }
}

/* ROM-grounded data: src/k_spawnaiFloatConstantWordsUsRev1.c */
const float k_spawnaiFloatConstantWords[2] = {
    45.0f, 6e+01f,
};
