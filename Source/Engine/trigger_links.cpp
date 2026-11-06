#include "Engine/cache.h"
#include "Engine/Instance/gobjinst.h"
#include "include_asm.h"
#include "Gamecore/externs.h"
#include "Common/runtime_declarations.h"
#include "Engine/link.h"
#include "Common/effectcontribution.h"
#include "types.h"
#include "Common/math_helpers.h"
#include "Common/world.h"
#include "Common/sharedplayer.h"
#include "Render/setn64_getpacksection.h"
#include "Actors/vertex_light_and_actor_views.h"
#include "Common/vector4f.h"
#include "Common/level_actor.h"
#include "Common/listheader.h"
#include "Common/trigger_and_float_value_operations.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Common/navigation_node_and_route_views.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/gameplay_sound_table.h"
#include "Render/soundelement_playflatsound.h"
#include "Engine/Audio/T2SoundElement.h"
#include "Engine/geometry.h"
#include "Common/triple.h"
#include "Common/menu_match_globals.h"
#include "Actionai/action_updatebreakableproximity.h"
#include "Animpool/animpool_spawndescribedsceneeffect.h"
#include "Cbarrel/barrel_spawnflaggedeffects.h"
#include "Gsky/sky_posttargetedscreenmessage.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#include "Menu/Items/Scene/scene_registeractorinscenelists.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Track/track_drawtrackoverlay.h"
#include "Common/track_requesttrackbykey.h"
#include "Render/timed_session_transitions.h"
#include "Engine/scene.h"
#include "Data/rest_source_records.h"
#include "libultra/ACTOR_STATE_TABLE_END_DATA.H"
#include "Engine/particle.h"
#include "Engine/lighting.h"

/* LINK_DISPATCHMATCHINGTRIGGERS.CPP */

typedef void (*NavPrimaryFn)(NavigationPlatform *, void *, Trigger *);
typedef void (*NavSecondaryFn)(Trigger *);
typedef struct NavCallbackPair { NavPrimaryFn primary; NavSecondaryFn secondary; } NavCallbackPair;



void Link_DispatchTrigger(Trigger *trigger) {
    NavCallbackPair *table;
    void *fallback;
    u8 index;
    s32 callback;
    table = g_actorTriggerDispatchTables[trigger->table];
    if (table != 0) {
        if (g_frontendScreenStatus.settings.local == 0) {
            fallback = g_frontendScreenStatus.cameras;
            if (fallback == 0) fallback = &g_frontendScreenStatus.fallbackCamera;
        } else {
            fallback = &g_frontendScreenStatus.fallbackCamera;
        }
        if (g_world.mode == 4) {
            index = trigger->sound;
            if (index != 0) {
                Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, fallback,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                                             g_gameplayEventMessageTable[trigger->sound].sound[g_languageIndex],
#else
                                             gameplaySoundValue(index),
#endif
                                             g_gameLoopFrameCount, triggerSoundWeight());
                callback = gameplaySoundHook(trigger->sound);
                if (callback != 0) SoundElement_PlayDialogGroup(callback);
            }
            if (trigger->action >= 2) Track_RequestTrackByKey(trigger->action);
        }
        table += trigger->entry;
        if (trigger->owner == g_activeLinkSequenceId) {
            NavPrimaryFn fn;
            NavigationPlatform *actor;
            fn = table->primary;
            actor = &g_navigationPlatformActors[trigger->actor];
            if (fn != 0) fn(actor, &actor->motion, trigger);
        } else {
            NavSecondaryFn fn;
            fn = table->secondary;
            if (fn != 0) fn(trigger);
        }
    }
}


void Link_DispatchActorLinks(struct Shared_Actor *actor, s32 event, void *context) {
    s32 triggers;
    s32 triggerCount;

    if (!(actor->weaponFlags & 0x80000)) {
        Scene_FindActorTriggerRange(&g_world, actor, &triggers, &triggerCount);
        if (triggerCount != 0) {
            Link_DispatchMatchingTriggers(triggers, triggerCount, 0, event & 0x3FC1FF, event & 0x400000, 0x400000, context);
        }
    }
}

void Link_DispatchObjectLinks(s32 actorAddress, s32 event, void *actor) {
    s32 triggers;
    s32 triggerCount;

    if (actorAddress != 0) {
        Scene_FindAlternateTriggerRange(&g_world, actorAddress, &triggers, &triggerCount);
        if (triggerCount != 0) {
            Link_DispatchMatchingTriggers(triggers, triggerCount, 0, event & 0x7FF, event & 0x3800, 14336, actor);
        }
    }
}

void Link_ActivateTrigger(TriggerActivationView *trigger) {

    trigger->enabled |= 0x10;
    Scene_SetTriggerStateBit(&g_world, trigger, 1);
    if ((g_world.mode == 4) && (trigger->enabled & 2)) {
        Scene_QueueTriggerTimer(&g_world, trigger);
        return;
    }
    Link_DispatchTrigger(trigger);
}

void Link_DispatchTriggerExit(WorldTrigger *trigger) {
    WorldTrigger copy;

    trigger->flags |= 0x20;
    if (trigger->active == 1) {
        copy = *trigger;
        copy.mode = 2;
        copy.state = 0;
        Link_DispatchTrigger(&copy);
    }
}

/* Clears bits 0x2000 and 0x100 of the flag word of an object. */

void Link_ClearActorFlagMask(struct LevelActor *object) {
    object->flags &= ~0x2000;
    object->flags &= ~0x100;
}

void Link_SetActorFlagMask(LevelActor *actor) {
    Gobjinst_AdvanceActorRootMotion(actor);
    actor->flags = (s32) (actor->flags | 0x2100);
}

void Link_RequestOwnerTrack(s32 owner, s32 triggerEvent, s32 trackId) {
    if (g_world.mode == 4) {
        Scene_ResetTransitionViewport();
        Track_RequestTrackByIds(owner, trackId);
    }
}

void Link_RequestGlobalTrack(s32 trackId) {
    if (g_world.mode == 4) {
        Scene_ResetTransitionViewport();
        Track_RequestTrackByIds(0, trackId);
    }
}

void Link_CaptureActorTransform(TriggerActorTransformView *actor, TriggerTargetTransformView *transform) {
    ((actor)->flags) = (s32) (((actor)->flags) | 0x40000000);
    ((transform)->capturedPositionX) = (f32) ((actor)->positionX);
    ((transform)->capturedPositionY) = (f32) ((actor)->positionY);
    ((transform)->capturedPositionZ) = (f32) ((actor)->positionZ);
    ((transform)->capturedYaw) = (f32) ((actor)->yaw);
}

void Link_DispatchTriggerAudio(s32 actorAddress, s32 event, Trigger *trigger) {
    if (trigger->trackArgument >= 256) {
        SoundElement_PlayDialogGroup(trigger->trackArgument);
        return;
    }
    SoundElement_SetMusicPlaybackEnabled(trigger->trackArgument);
}

void Link_DeactivateActorState(struct Shared_Actor *actor, s32 *stateFlags) {
    s32 flags;

    Barrel_StopActorLoopingSound(actor, stateFlags);
    *stateFlags |= 0x20;
    flags = actor->weaponFlags & 0xFFFEFFFF;
    flags = flags & ~0x2000;
    flags = flags & ~0x100;
    actor->weaponFlags = flags;
    if (flags & 0x80000) {
        Animpool_ReleaseSceneEffect(actor);
    }
}

void Link_PlayTriggerSoundCallback(int platform, int triggerEvent, LinkTriggerRecord *trigger) {
    SoundElement_PlayFlatSound(trigger->soundId);
}

void Link_SelectTriggerMusic(struct LinkTriggerRecord *trigger) {
    SoundElement_SetMusicPlaybackEnabled((s32) (((struct Trigger *) ((s8 *) trigger))->trackArgument));
}

void Link_PlayTriggerSound(LinkTriggerRecord *trigger) {
    SoundElement_PlayFlatSound(trigger->soundId);
}

/* Updates a table of triggers against masks: for each trigger the world accepts (always in world mode 4, otherwise when Scene_TestTriggerStateBit refuses it), a trigger not yet entered whose mask meets the enter mask is marked entered and runs its enter action (the id's action through Scene_TestTriggerKindFlags and Scene_DispatchSecondaryTriggersOfKind, or Link_DispatchTriggerExit without an id); it then counts as active when its mask meets the require mask, meets the enter mask, passes the paired exclude masks, is not flagged 0x1000 without 0x100 and passes Link_CheckTriggerMessage, and an active trigger runs its fire action once (through Scene_SetTriggerStateBit, Scene_DecrementTriggerCounter, Scene_TestTriggerCounterZero and Scene_ActivateTriggersOfKind for an id, or Link_ActivateTrigger without one). */

void Link_SetTriggerTrackCallback(int platform, int triggerEvent, struct LinkTriggerRecord *trigger) {
    Trigger *triggerRecord = trigger;
    SoundElement_SetTrackAndPeriodicPlayback(triggerRecord->trackArgument);
}

void Link_SetTriggerTrack(struct LinkTriggerRecord *trigger) {
    SoundElement_SetTrackAndPeriodicPlayback((((struct Trigger *) ((s8 *) trigger))->trackArgument));
}

void Link_ClearActorStateBit(struct Shared_Actor *actor) {
    actor->weaponFlags &= ~0x10000;
}

/** Set flag 0x10000 in the word. */
void Link_SetActorStateBit(Shared_Actor *object) {
    object->weaponFlags |= 0x10000;
}

void Link_DispatchMatchingTriggers(Trigger *triggers, s32 count, s32 require, s32 enter, s32 exclude, s32 group, struct Player *arg) {
    s32 i;
    s32 active;
    s32 usable;
    Shared_World *world;
    Trigger *trigger;

    for (trigger = triggers, i = 0; i < count; trigger++, i++) {
        world = &g_world;
        usable = 1;
        if (world->mode != 4) {
            usable = Scene_TestTriggerStateBit(world, trigger) == 0;
        }
        if (!usable) {
            continue;
        }
        active = 1;
        if (!(trigger->flags.bytes.state & 0x20) && enter != 0 && (trigger->mask & enter)) {
            trigger->flags.bytes.state |= 0x40;
            if (trigger->flags.bytes.id != 0) {
                if (Scene_TestTriggerKindFlags(world, trigger->flags.bytes.id) != 0) {
                    Scene_DispatchSecondaryTriggersOfKind(world, trigger->flags.bytes.id);
                }
            } else {
                Link_DispatchTriggerExit(trigger);
            }
            active = 1;
        }
        if (require != 0) {
            active = 0;
            if (trigger->mask & require) {
                active = 1;
            }
        }
        if (enter != 0 && !(trigger->mask & enter)) {
            active = 0;
        }
        if ((trigger->mask & group) && !(trigger->mask & group & exclude)) {
            active = 0;
        }
        if ((trigger->flags.word & 0x1100) == 0x1000) {
            active = 0;
        }
        if (Link_CheckTriggerMessage(trigger, arg) == 0) {
            active = 0;
        }
        if (!active) {
            continue;
        }
        if (trigger->flags.bytes.id != 0) {
            if (!(trigger->flags.bytes.state & 0x80)) {
                Scene_SetTriggerStateBit(world, trigger, 1);
                trigger->flags.bytes.state |= 0x80;
                Scene_DecrementTriggerCounter(world, trigger->flags.bytes.id);
                if (Scene_TestTriggerCounterZero(world, trigger->flags.bytes.id) != 0) {
                    Scene_ActivateTriggersOfKind(world, trigger->flags.bytes.id);
                }
            }
        } else {
            Link_ActivateTrigger(trigger);
        }
    }
}

s32 Link_CheckTriggerMessage(LinkTriggerMessageView *trigger, struct Player *player) {
    LinkTriggerMessageView *object = trigger;
    NavigationPlatform *platform;

    if (object->sequenceId == g_activeLinkSequenceId) {
        if (player != 0) {
            platform = &g_navigationPlatformActors[object->platformIndex];
            if ((object->messageKind == 10) && (object->messageState == 1)) {
                return Action_ShowTriggerMessage(platform, &platform->motion, player);
            }
        }
        return 1;
    }
    return 1;
}
