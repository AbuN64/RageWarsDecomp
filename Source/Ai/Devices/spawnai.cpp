#include "Common/stagepreset.h"
#include "Ai/spawnai_symbols.h"
#include "Common/shared_optionsscreen.h"
#include "Common/animationtriggerdefinition.h"
#include "Common/Lone/g_currentstagepreset.h"
#include "Common/audio_callbacks.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/ballisticparams.h"
#include "Common/shared_gameslot.h"
#include "Common/level_actor.h"
#include "Common/world.h"
#include "Common/breakable_hits.h"
#include "Common/rec.h"
#include "Common/animation_pool.h"
#include "Common/listheader.h"
#include "Common/results.h"
#include "types.h"
#include "Common/player_score_table.h"
#include "Weapons/actor_requestactorstate.h"
#include "Engine/lists.h"
#include "include_asm.h"
#include "Ai/Player/playerai_findtransientplayer.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Engine/gregion.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Engine/rumble_setactorstatebit.h"
#include "Engine/session.h"
#include "Engine/Animpool/animpool_spawnsceneeffect.h"
#include "Ai/ai_shared_symbols.h"

/* Dispatch configured object, particle, or weighted-choice spawns and update the owner count. */


struct Context;



static __inline__ SpawnChoice *spawnTable0(void) {
    return g_spawnChoices;
}

static __inline__ SpawnChoice *spawnTable1(void) {
    return g_spawnChoices + 1;
}

static __inline__ SpawnChoice *spawnTable2(void) {
    return g_spawnHealthChoices;
}

static __inline__ SpawnChoice *spawnTable3(void) {
    return g_spawnHealthChoicesVisible;
}

static __inline__ SpawnChoice *spawnTable4(void) {
    return g_spawnChoices + 9;
}

static __inline__ SpawnChoice *spawnTable5(void) {
    return g_spawnChoices + 13;
}

static __inline__ SpawnChoice *spawnTable6(void) {
    return g_spawnChoices + 14;
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
        id = g_currentStagePreset->recorded + 5000;
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
        id = g_currentStagePreset->recorded + 5000;
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
    owner->remaining -= Particle_SpawnEffectGroup((EffectSystem *)g_actorParticleEffectSystem, object, object, &owner->spawn,
            0, count, object->rotation, object->motion, position, 0, -1, 0);
}


/* Words preceding the jump table. */
#if defined(VERSION_EU)
const u32 k_spawnaiConstants[2] = {
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
            /* The game settings sit inside the menu data block; recover the block start from them so the settings address is built once. */
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

const float k_spawnaiFloatConstants[2] = {
    45.0f, 6e+01f,
};
