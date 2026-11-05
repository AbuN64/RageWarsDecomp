#include "include_asm.h"
#include "Ai/Devices/actionai.h"
#include "Common/game_session.h"
#include "Common/gameplay_camera.h"
#include "Common/shared_optionsscreen.h"
#include "Common/obj.h"
#include "Common/rendercounters.h"
#include "Common/gameplay_transition.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/breakable_hits.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/level_actor.h"
#include "Common/world.h"
#include "Common/rec.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/listheader.h"
#include "Common/triple.h"
#include "types.h"
#include "Weapons/actor_requestactorstate.h"
#include "Common/gameplay_sound_table.h"
#include "Common/menu_match_globals.h"
#include "Common/navigation_node_and_route_views.h"
#include "Actionai/action_updatebreakableproximity.h"
#include "Ai/Player/playerai_findtransientplayer.h"
#include "Ai/player_team_score.h"
#include "Gobjinst/player_drawtintedplayer_data.h"
#include "Gsky/sky_posttargetedscreenmessage.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Engine/rumble_setactorstatebit.h"
#include "Fx/fx_spawnimpactmark.h"
#include "Camera/camera.h"
#include "Ai/devices_symbols.h"


#if defined(VERSION_EU_X)
#define Action_UpdateBreakableProximity Action_UpdateBreakableProximityEuropeanExtended
#elif defined(VERSION_EU)
#define Action_UpdateBreakableProximity Action_UpdateBreakableProximityEuropean
#endif


void Action_UpdateBreakableProximity(u8 *self, u8 *hit) {
    u8 *state = (u8 *)&((ActorDefinitionHeader *)((Player *)self)->definition)->flags;
    u16 kind = ((Player *)self)->objectId;
    u8 *player;
    u8 *table;
    u8 *table2;
    u8 *record;
    u8 *node;
    CVector3 playerOffset;
    Shared_MenuData *menuData;
    f32 distance;
    u32 clearedFlags;
    switch (kind) {
    case 1614:
        player = Playerai_FindTransientPlayer((u8 *)&g_playerViewRenderContext);
        if (player != 0 && ((Player *)player)->health != 0
                && ((ActorMotionState *)hit)->ownerTeam != ((ActorMotionState *)hit)->mode) {
            table = (u8 *)&((Shared_MenuData *)&g_playerViewRenderContext)->game.counters;
            if (((CGameStatus *)table)->m_FragTagFlipTimer == 0 && ((ActorMotionState *)hit)->reservedWord12C == 0) {
                if (((Player *)player)->profile->bonus == 1) {
                    ((Player *)player)->profile->bonus = 0;
                    ((Player *)player)->profile->state90 = 1;
                    ((CGameStatus *)table)->m_FragTagMode = 1;
                    ((ActorMotionState *)hit)->reservedWord12C = 1;
                    SoundElement_PlayFlatSound(3597);
                }
            }
        }
        break;
    case 1619:
    case 1620:
    case 1621:
    case 1622:
        if (((ActorMotionState *)hit)->ownerTeam == ((ActorMotionState *)hit)->mode) {
            return;
        }
        player = Playerai_FindTransientPlayer((u8 *)&g_playerViewRenderContext);
        if (player == 0 || ((Player *)player)->profile->bonus == 0) {
            return;
        }
        playerOffset.x = ((Player *)player)->pos.x - ((Player *)self)->pos.x;
        playerOffset.y = ((Player *)player)->pos.y - ((Player *)self)->pos.y;
        playerOffset.z = ((Player *)player)->pos.z - ((Player *)self)->pos.z;
        distance = Gu_Sqrtf(playerOffset.x * playerOffset.x + playerOffset.y * playerOffset.y + playerOffset.z * playerOffset.z);
        if ((f32)(s32)distance < 122.88f) {
            ((Player *)player)->profile->bonus = 0;
            ((Player *)player)->profile->state90 = 1;
            ((u16 *)((Player *)player)->profile->roundTotals)[4] += 1;
            Playerai_UpdateTeamScore(player, player, 3);
            table2 = (u8 *)&((Shared_MenuData *)&g_playerViewRenderContext)->game.counters;
            ((CGameStatus *)table2)->m_CTFMode = 0;
            ((CGameStatus *)table2)->m_CTFPlayerWithFlag = 0;
            switch (((Player *)player)->profile->team) {
            case 0:
                SoundElement_PlayFlatSound(742);
                break;
            case 1:
                SoundElement_PlayFlatSound(740);
                break;
            case 2:
                SoundElement_PlayFlatSound(744);
                break;
            case 3:
                SoundElement_PlayFlatSound(748);
                break;
            case 4:
                SoundElement_PlayFlatSound(746);
                break;
            }
#if defined(VERSION_EU) || defined(VERSION_EU_X)
            menuData = &g_playerViewRenderContext;
            for (node = g_transientPlayerList.actorList; node != 0; node = (u8 *)((SharedPlayer *)node)->views16E0.view16E0_0.next) {
                if (((Player *)node)->camera != 0) {
                    Camera_PostScreenMessage((u8 *)&menuData->object, ((Player *)node)->camera,
                        g_breakableNotificationText[menuData->game.language]);
                }
            }
#else
            for (node = g_transientPlayerList.actorList; node != 0; node = (u8 *)((SharedPlayer *)node)->views16E0.view16E0_0.next) {
                if (((Player *)node)->camera != 0) {
                    Camera_PostScreenMessage((u8 *)&g_frontendScreenStatus, ((Player *)node)->camera, g_breakableNotificationText);
                }
            }
#endif
        } else {
            return;
        }
        break;
    }
    if (((ActorMotionState *)hit)->actionPending != 0) {
        if (*(u32 *)state & 2) {
            clearedFlags = ((Player *)self)->weaponFlags & ~0x2000;
            ((Player *)self)->weaponFlags = clearedFlags & ~0x100;
        }
        if (((ActorMotionState *)hit)->remainingCount != 0) {
            Actor_RequestActorState(self, hit, 0);
        }
        if (((Player *)self)->objectId == 1612) {
            Actor_RequestActorState(self, hit, 2);
        }
    }
}

/* The early returns are gotos to one exit label: with plain early returns EU/EU-X build beqz for the flags
 * test where the ROM has beql (delay slot annulled); this shape gives the ROM word in all five versions. */
s32 Action_ShowTriggerMessage(struct NavigationPlatform *object, ActorMotionState *guard, struct Player *player) {
    ActorMotionDefinition *record;
    Player *parent;
    void *emitter, *fallback;
    s16 index;
    s32 callback;
    record = &object->resource->motion;
    if (record->soundEnabled == 0) goto out1;
    if (guard->mode != 0) goto out1;
    if (((Player *)player)->kind != 1) goto out1;
    if ((((Player *)player)->weaponFlags & 0x300000) == 0) goto out1;
    index = record->soundIndex;
    parent = (Player *)((Player *)player)->actorParts[0].controller;
    if (index != 0) {
        emitter = parent->camera;
        fallback = &g_fallbackScreenMessageEmitter;
        if (emitter != 0) fallback = emitter;
        Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, fallback, gameplaySoundValue(index), object, gameplaySoundWeight());
        index = record->soundIndex;
        callback = gameplaySoundHook(index);
        if (callback != 0) SoundElement_PlayDialogGroup(callback);
    }
    return 0;
out1:
    return 1;
}

typedef struct Owner Owner;


struct RibbonWorld;
extern void Fx_RecycleOwnerParticles(struct RibbonWorld *, s32);



/* Supplies the nonnegative blend remaining after the incoming strength is
 * scaled, then applies the actor animation using the original lookup. */
struct ActionFadeInput {
    char pad0[0x40];
    f32 strength;
};


/** Run the object's optional update hook, then copy one of two byte pairs into the record header. */

void Actionai_CopyTrackBytes(char *ownerRecord, char *eventRecord) {
    Owner *owner = (void *)ownerRecord;
    ActorMotionState *event = (void *)eventRecord;
    char *base = &((struct NavigationTrack *)owner->track)->segment;
    ActorMotionHooks *hooks = event->hooks;

    if (hooks != 0 && hooks->onStep != 0) {
        hooks->onStep(ownerRecord, eventRecord);
    }
    if (event->mode == 0) {
        ownerRecord[1] = base[14];
        ownerRecord[3] = base[15];
    } else {
        ownerRecord[1] = base[26];
        ownerRecord[3] = base[27];
    }
}

void Actionai_InitBreakableMotion(LevelActor *actor, ActorMotionState *motionState) {
    motionState->table = &g_actionMotionDispatchTable;
    motionState->update = &g_actionUpdateRomEntry;
    motionState->animation = 0;
    motionState->remainingCount = 0;
    motionState->reservedWord12C = 0;
    if (((BreakableDefinition *)actor->definition)->flags & 1) {
        actor->flags = actor->flags | 0x10000;
        return;
    }
    actor->flags = actor->flags & 0xFFFEFFFF;
}

/** Update actor state and clear flags for the relevant actor classes. */
void Action_ActivateBreakableState(SharedPlayer *actor, void *state) {
    s32 flags;

    if (Rumble_TestActorStateBit(&g_world, actor) == 1) {
        Actor_RequestActorState(actor, state, 1);
        switch (actor->views1C.viewE4_7.kind) {
        case 1612:
            flags = actor->views1C.view100_9.flags & ~0x2000;
            actor->views1C.view100_9.flags = flags & ~0x100;
            break;
        case 1611:
        case 1614:
            actor->views1C.view100_9.flags &= 0xF7FFFFFF;
            break;
        }
    } else {
        g_actionStateTransitionPending = 1;
        Actor_RequestActorState(actor, state, 0);
        g_actionStateTransitionPending = 0;
    }
}

/* The kind-10 actor initializer installs the state table containing this callback. */
s32 Actionai_UpdateTriggerFlag(LevelActor *actor) {
    void *resource = actor->definition;
    BreakableDefinition *definition = resource;
    s32 triggerValue;

    triggerValue = definition->triggerValue;
    if (triggerValue != 0) {
        actor->flags = actor->flags | 0x2000;
    } else {
        actor->flags = actor->flags & ~0x2000;
    }
    return triggerValue;
}

void Action_ClearBreakableState(void *actor, void *actorMotionState) {
    ActorMotionState *state = actorMotionState;
    Rumble_SetActorStateBit(&g_world, actor, 0);
    Link_DispatchActorLinks(actor, 0x200000, actor);
    state->reservedWord12C = 0;
}

s32 Actionai_UpdateHealthFlag(LevelActor *actor) {
    s32 health;

    health = ((BreakableDefinition *)actor->definition)->health;
    if (health != 0) {
        actor->flags = actor->flags | 0x2000;
    } else {
        s32 flags = actor->flags & ~0x2000;
        flags &= ~0x100;
        actor->flags = flags;
    }
    return health;
}

void Action_SetBreakableState(void *actor) {
    BreakableDefinition *breakableDefinition;
    s32 hitFlags;
    s32 masked;
    Shared_World *pFlag;

    breakableDefinition = (BreakableDefinition *)((LevelActor *)actor)->definition;
    pFlag = &g_world;
    Rumble_SetActorStateBit(pFlag, actor, 1);
    if (g_actionStateTransitionPending == 0) {
        Link_DispatchActorLinks(actor, 0x80000, actor);
    }
    Fx_RecycleOwnerParticles(&g_gameSession.hud.actors, actor);
    if (pFlag->mode != 4) {
        hitFlags = ((LevelActor *)actor)->flags | 0x08000000;
        ((LevelActor *)actor)->flags = hitFlags;
        if (breakableDefinition->flags & 2) {
            masked = hitFlags & ~0x2000;
            masked = masked & ~0x100;
            ((LevelActor *)actor)->flags = masked;
        }
        if (((BreakableDefinition *)((LevelActor *)actor)->definition)->health == 0) {
            ((LevelActor *)actor)->flags = ((LevelActor *)actor)->flags & ~0x100;
        }
    }
}

void Actionai_SetDrawHandler(void *ownerActor, void *motionState) {
    Dest *state = motionState;
    state->draw = &g_actionDrawRomEntry;
}

/** Clear two flag groups when the object's tracked value exceeds a tunable. */
void Actionai_ClearMotionFlags(LevelActor *object) {
    if (object->motionThreshold > k_actionMotionThreshold) {
        int flags = object->flags;
        flags &= ~0x2000;
        flags &= ~0x100;
        object->flags = flags;
    }
}

void Action_RequestStateOn(void *actor, void *eventSource) {
    Actor_RequestActorState(actor, eventSource, 1); }

void Actionai_EnableTrigger(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 1);
}

void Action_RequestStateOff(void *actor, void *eventSource) {
    Actor_RequestActorState(actor, eventSource, 0); }

void Actionai_DisableTrigger(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 0);
}

void Actionai_DrawFadedActor(LevelActor *actor, struct ActionFadeInput *input, Lookup *lookup) {
    f32 remaining = k_actionFadeMaximum - input->strength * k_actionFadeStrengthScale;
    g_menuModelFillEnabled = 1;
    if (remaining < 0.0f) {
        remaining = 0.0f;
    }
    g_menuModelFillColor[3] = remaining;
    Gobjinst_DrawActorModelWithViewEffects(actor, input, lookup);
}


#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
const float k_actionUpdateBreakableProximityLiteral[1] = {
    4.0f,
};
#endif

#undef Action_UpdateBreakableProximity

const float k_actionClearMotionFlagsLiteral[1] = {
    3e+01f,
};

const float k_actionResolvebreakablehitDataFloatConstants[1] = {
    0.007874016f,
};

#if defined(VERSION_EU_X)
unsigned int k_actionResolvebreakablehitFragment[2] = {
    0x40490FDC, 0xBFC90FDC,
};
#endif

#if defined(VERSION_EU)
unsigned int k_actionResolvebreakablehitFragment[2] = {
    0x3C021000, 0x8E030010,
};
#endif

#if defined(VERSION_DE)
unsigned int k_ActionResolvebreakablehitData[2] = {
    0x0C0AC6AC, 0x02803021,
};
#endif

#if !(defined(VERSION_DE) || defined(VERSION_US))
#ifdef VERSION_EU
const float k_actionUpdateBreakableProximityLiteral[1] = {
    4.0f,
};
#endif
#ifdef VERSION_EU_X
const float k_actionUpdateBreakableProximityLiteral[1] = {
    4.0f,
};
#endif
#ifdef VERSION_US_REV1
#endif
#endif

#if defined(VERSION_US_REV1)
unsigned int g_actionFloatConstants[2] = {
    0x40490FDC, 0xBFC90FDC,
};
#endif
