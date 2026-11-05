#include "Ai/source.h"
#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include "Common/level_actor.h"
#include "Ai/actor_setup_versions.h"
extern u8 ACTOR_TABLE_B[];
#include "types.h"
#include <platform_sdk.h>
#include "Ui/X_files/x_plus.h"
#include "Actor/actor.h"
#include "Engine/gregion.h"
#include "Ai/nav_symbols.h"
#include "Common/sharedplayer.h"
#include "Game/builddirectionmatrix.h"
#include "Actor/nav_applysupportingplatformmotion.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Render/triggered_updatetriggeredmotion.h"
#include "Engine/Unicol/unicol.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/triple.h"
#include "Common/runtime_declarations.h"
#include "Weapons/actor_requestactorstate.h"
#include "Actor/actor_updateactorstateanimation.h"
#include "Cbarrel/barrel_spawnflaggedeffects.h"
#include "Engine/defs.h"
#include "Common/world.h"
#include "Engine/Instance/gobjinst.h"
#include "Gobjinst/gobjinst_buildactortransform.h"
#include "Ai/cbarrel.h"

/* Seeds an actor record from its definition: clears the sound handle, pending flag and channel, copies the
   definition's first, second and send bytes into the source object, and takes the health from the
   definition (unsigned for kinds 1 and 4, with kind 1's two levels; signed short for kind 7). For kinds 1
   and 4 the scene mask scales it: 8 by g_actorSceneMaskHealthLimits with a floor and no second level, 0x20 by
   g_actorSceneMaskHealthScale with second level g_actorSceneMaskSecondaryLevel. The health is kept as 24.8 fixed point. */
void Actor_ApplyActorDefinition(Dest *actor, void *def, CVector3 position, LevelActor *source) {
    s32 send;
    s32 first;
    s32 second;
    f32 pitch;
    f32 level;
    f32 level2;
    f64 wide;
    f32 scaled;
    s32 raw;

    send = 0;
    level = g_actorDefaultLevelPair;
    level2 = (&g_actorDefaultLevelPair)[1];
    first = 0;
    second = 0;
    actor->handle = -1;
    actor->pending = 0;
    actor->channel = -1;
    pitch = level;
    if (def != 0) {
        send = ((ActorDefinitionHeader *)def)->send;
        first = ((ActorDefinitionHeader *)def)->first;
        second = ((ActorDefinitionHeader *)def)->second;
        switch (((ActorDefinitionHeader *)def)->kind) {
        case 1:
            raw = ((ActorHealthDefinition *)def)->health;
            wide = raw;
            if (raw < 0) {
                wide += g_actorMovementKindUnsignedHealthBias;
            }
            level = ((MovementDescriptor *)def)->level;
            level2 = ((MovementDescriptor *)def)->secondaryLevel;
            pitch = wide;
            break;
        case 4:
            raw = ((ActorHealthDefinition *)def)->health;
            wide = raw;
            if (raw < 0) {
                wide += g_actorHealthKindUnsignedHealthBias;
            }
            pitch = wide;
            break;
        case 7:
            pitch = ((PickupHealthActorDefinition *)def)->health;
            break;
        }
        if (((ActorDefinitionHeader *)def)->kind == 1 || ((ActorDefinitionHeader *)def)->kind == 4) {
            switch (g_gameSettings.sceneMask) {
            case 8:
                scaled = pitch * g_actorSceneMaskHealthLimits;
                level2 = 0.0f;
                if (scaled < (&g_actorSceneMaskHealthLimits)[1]) {
                    scaled = (&g_actorSceneMaskHealthLimits)[1];
                }
                pitch = scaled;
                break;
            case 32:
                level2 = g_actorSceneMaskSecondaryLevel;
                pitch *= g_actorSceneMaskHealthScale;
                break;
            }
        }
    }
    source->renderPass = send;
    source->team = first;
    source->spawnSecond = second;
    actor->health = pitch;
    actor->level = (s32) level;
    actor->secondaryLevel = (s32) level2;
    actor->health <<= 8;
    actor->maxHealth = actor->health;
}

/* Builds an actor record from its source level actor: clears the record (keeping animation), applies the
 * definition, installs this version's two behaviour tables, seeds the position, height and scale copies,
 * the sentinel indices (-1) and the unit scales, clears the attach count and its flag bit, runs the
 * optional spawn callback, and sets the attach count when the source has bit 27 of its flags. */
typedef struct ActorSpawnCallbacks {
    void (*onSpawn)(LevelActor *, Dest *);
} ActorSpawnCallbacks;

void Actor_InitSpawnedActor(LevelActor *source, Dest *actor, ActorSpawnCallbacks *callbacks) {
    void *saved;
    void *surface;
    f32 scale;
    s32 value;
    u32 bits;

    saved = actor->animation;
    XPlus_FillMemory(actor, 0, sizeof(Dest));
    actor->flags = 0x40;
    actor->animation = saved;
    Actor_ApplyActorDefinition(actor, source->definition, source->position0, source);
    actor->callback11C = &ACTOR_TABLE_A;
    actor->draw = &ACTOR_TABLE_B;
    actor->state = -1;
    actor->old_state = -1;
    actor->entry = NULL;
    actor->initialPosition = source->position0;
    actor->previousPosition = source->position0;
    actor->animationCount[0] = 0;
    actor->animationCount[1] = 0;
    actor->animationCount[2] = 0;
    actor->initialHeight = source->yaw;
    actor->cueTimer = 0;
    actor->reserved78[0] = 0;
    actor->reserved78[1] = 0;
    actor->reserved78[2] = 0;
    actor->reserved78[3] = 0;
    actor->reserved78[4] = 0;
    actor->height8C = source->yaw;
    actor->height90 = source->position0.y;
    actor->height9C = source->yaw;
    actor->positionA0 = source->position0;
    actor->surfaceAC = (void *)source->model;
    actor->positionB0 = source->position0;
    surface = (void *)source->model;
    actor->surfaceBC = surface;
    if ((source->definition->gate & 4) && surface != NULL) {
        actor->positionB0.y = Region_GetPolygonHeight(surface, actor->positionB0.x, actor->positionB0.z);
    }
    scale = 1.0f;
    value = -1;
    actor->state_result = value;
    value = 20;
    actor->state13 = value;
    value = 0xFF;
    actor->state95 = value;
    bits = -1;
    actor->result = bits;
    actor->old_state = bits;
    actor->state14[0] = bits;
    actor->state14[1] = bits;
    actor->state14[2] = bits;
    actor->state14[3] = bits;
    actor->channel = bits;
    actor->state96 = bits;
    actor->count = 0;
    actor->reservedD0 = 0;
    actor->reservedWordBeforeTail = 0;
    actor->reserved44 = 0;
    actor->state12 = 0;
    actor->reserved1C[0] = 0;
    actor->reserved1C[1] = 0;
    actor->reserved1C[2] = 0;
    actor->reserved1C[3] = 0;
    actor->pending = 0;
    actor->state94 = 0;
    actor->sound = NULL;
    actor->scale = scale;
    actor->entry_scale = scale;
    actor->flags &= ~1;
    actor->initialScale = scale;
    if (callbacks != NULL && callbacks->onSpawn != NULL) {
        callbacks->onSpawn(source, actor);
    }
    bits = 0x8000000;
    if (source->flags & bits) {
        actor->count = 1;
    }
}

struct CollisionInfo;



void Actor_ApplySupportingPlatformMotion(LevelActor *player, void *motionContext) {
    CVector3 saved_velocity;
    CVector3 position;
    CVector3 transformed;
    MatrixF matrix;
    u8 *object;
    f32 amount;

    object = InstHdr_GetEnabledItemValue(player);
    if ((object != 0) && (((LevelActor *)object)->definition->kind == 2)) {
        position = player->position0;
        InstHdr_GetActorTargetOffset(object, &saved_velocity);
        if (!(player->motionState & 0x1000) || (saved_velocity.y > 0.0f)) {
            Graphu64_AddVec3(&position, &position, &saved_velocity);
        }
        saved_velocity = player->position1;
        player->position1.x = 0.0f;
        player->position1.y = 0.0f;
        player->position1.z = 0.0f;
        Graphu64_SubtractVectors(&transformed, &position, &((LevelActor *)object)->position0);
        amount = InstHdr_GetActorTargetHeight(object);
        BuildYawMatrix(&matrix, amount);
        Graphu64_TransformPoints(&matrix, &transformed, &transformed, 1);
        Graphu64_AddVec3(&transformed, &transformed, &((LevelActor *)object)->position0);
        Graphu64_SubtractVectors(&transformed, &transformed, &position);
        player->yaw += amount;
        Graphu64_AddVec3(&position, &position, &transformed);
        Unicol_MoveActorWithCollision(player, position.x, position.y, position.z, &g_supportingPlatformCollisionQuery);
        player->position1 = saved_velocity;
        if ((object[0] == 1) && (((LevelActor *)object)->definition->kind == 2)) {
            Triggered_PathMotionNoOp();
        }
    }
}

void Actor_UpdateActorStateAnimation(Source110 *src, Dest *dst) {
    StateEntry *entry;
    StateCallback callback;
    f32 factor;

    entry = dst->entry;
    if (entry != 0) {
        if (dst->old_state != dst->state) {
            if (entry->scale >= 0.0f) {
                dst->entry_scale = entry->scale;
            }
            dst->old_entry_flags = dst->entry_flags;
            dst->entry_flags = entry->flags;
            src->state_changed = 0;
            callback = entry->callback;
            if (callback != 0) {
                if (Defs_IsAddressInCodeRanges(callback) != 0) {
                    callback = callback(src, dst);
                } else if (Defs_IsAddressInStaticRanges((u32)callback) != 0) {
                    callback = (StateCallback)Gobjinst_ChooseAvailableAnimationKind(src, callback, dst->state_result);
                }
                if (callback != 0) {
                    if (callback != (StateCallback)-1) {
                        dst->state_result = Gobjinst_ChooseAnimationVariant(src, (s32)callback, dst->state_result);
                        dst->result = (s16)callback;
                        if (src->current_state == dst->state_result) {
                            src->limit = 0.0f;
                        }
                    }
                    dst->count = 0;
                    dst->flags &= ~1U;
                }
            }
            dst->old_state = (u8)dst->state;
        } else if ((dst->state_result == -1) || (dst->result == -1)) {
            dst->count++;
            dst->flags |= 1;
        } else if (src->current_state == dst->state_result) {
            if (!(dst->flags & 1)) {
                s32 difference = src->counter - entry->threshold;
                double converted = difference;
                if (difference < 0) {
                    converted += g_actorAnimationUnsignedConversionBias;
                }
                if ((f32)converted <= src->limit) {
                    dst->count++;
                    dst->flags |= 1;
                }
            }
            if (src->state_changed != 0) {
                src->state_changed = 0;
                if (!(dst->flags & 1)) {
                    dst->count++;
                }
                dst->flags &= ~1U;
            }
        }

        if (dst->entry_flags & 0x10) {
            factor = dst->entry_scale;
        } else {
            factor = dst->scale * dst->entry_scale;
        }
        g_frameElapsedTime *= factor;
        Gobjinst_RequestAnimationIndex(src, dst->state_result, (dst->entry_flags >> 5) & 1);
        if ((dst->state_result != -1) && (src->previous_state != dst->state_result)) {
            dst->count = 0;
            dst->flags &= ~1U;
            src->state_changed = 0;
        }
        if (src->flags & 0x08000000) {
            dst->count++;
        }
    }
}



s32 Actor_RequestActorState(void *actor, void *stateController, s32 action) {
    struct ActorStateTable *node;
    StateEntry *entry;
    StateEntry *scan;
    s32 flags;

    if (g_world.mode == 2) {
        return 1;
    }
    if (g_world.mode == 4) {
        ((Source110 *)actor)->flags |= 0x100;
    }

    ((Dest *)stateController)->requestedState = ((Dest *)stateController)->state;
    ((Source110 *)actor)->animationChanged = 1;
    ((Source110 *)actor)->stateChanged = 1;
    if ((((Dest *)stateController)->entry != 0) && (((Dest *)stateController)->state == action)) {
        return 1;
    }

    node = ((Dest *)stateController)->table;
    entry = 0;
    ((Dest *)stateController)->state = action;
    ((Dest *)stateController)->stateTimer = 0;
    while (node != 0) {
        scan = node->entries;
        if (scan->id != -1) {
            while (scan->id != -1) {
                if (scan->id == action) {
                    entry = scan;
                    node = 0;
                    break;
                }
                scan = scan + 1;
            }
        }
        if (node != 0) {
            node = node->next;
        }
    }

    if (entry == 0) {
        return 0;
    }

    ((Dest *)stateController)->entry = entry;
    ((Source110 *)actor)->renderFlags &= 0x1F80007F;
    if ((((Source110 *)actor)->flags & 0x08000000) == 0) {
        ((Dest *)stateController)->count = 0;
        ((Dest *)stateController)->flags &= ~1U;
    }
    if (((Dest *)stateController)->sound != 0) {
        Barrel_StopActorLoopingSound(actor, stateController);
    }
    if (entry->enter.address != 0) {
        ((void (*)(struct Source110 *, struct Dest *))entry->enter.address)(actor, stateController);
    }
    flags = entry->flags;
    ((Dest *)stateController)->entry_flags = flags;
    if (flags & 4) {
        ((Source110 *)actor)->velocity.x = 0;
        ((Source110 *)actor)->velocity.y = 0;
        ((Source110 *)actor)->velocity.z = 0;
    }
    return ((Dest *)stateController)->state == action;
}



#if defined(VERSION_DE) || defined(VERSION_EU_X)
#if defined(VERSION_DE)
unsigned int k_actorZeroPad[1] = {
    0x00000000,
};
#endif
#if defined(VERSION_EU_X)
void *k_actorZeroPad[1] = {
    (void *)&Playerai_ApplyLinkedProjectileStatus_label2276,
};
#endif
#endif



#if defined(VERSION_EU) || defined(VERSION_US)
#if defined(VERSION_EU)
const unsigned int k_ActorZeroFill[1] = {
    0x00000000,
};
#endif
#if defined(VERSION_US)
unsigned int k_ActorZeroFill[1] = {
    0x00000000,
};
#endif
#endif

/* Retained data for this translation unit. */

const float g_Actor_ApplyActorDefinitionConstantWords[10] = {
    100.0f, 128.0f, 30.0f, 0.0f,
    30.0f, 0.0f, 0.5f, 1.0f,
    1.25f, 255.0f,
};

const double g_Actor_UpdateActorStateAnimationConstantWords[1] = {
    4294967296.0,
};
