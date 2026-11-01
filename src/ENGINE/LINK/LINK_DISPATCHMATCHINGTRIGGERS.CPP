#include "include_asm.h"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "ACTORS/VERTEX_LIGHT_AND_ACTOR_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/LISTHEADER.H"
#include "TYPES.H"
#include "ENGINE/LINK.H"
#include "COMMON/TRIGGER_AND_FLOAT_VALUE_OPERATIONS.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"

/* 80277444_8.CPP */

#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/GAMEPLAY_SOUND_TABLE.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include "ENGINE/AUDIO/T2SOUNDELEMENT.H"
typedef void (*NavPrimaryFn)(NavigationPlatform *, void *, Trigger *);
typedef void (*NavSecondaryFn)(Trigger *);
typedef struct NavCallbackPair { NavPrimaryFn primary; NavSecondaryFn secondary; } NavCallbackPair;

extern NavCallbackPair *g_actorTriggerDispatchTables[];

extern void *g_gameLoopFrameCount;

#include "COMMON/MENU_MATCH_GLOBALS.H"
extern s32 g_activeLinkSequenceId;

extern void Gsky_PostTargetedScreenMessage(void *, void *, s32, void *, f32);
extern s32 Track_RequestTrackByKey(s32);
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


extern s32 Scene_FindActorTriggerRange(s8 *world, void *levelActor, s32 *firstIndex, s32 *lastIndex);

extern s32 Scene_FindAlternateTriggerRange(s8 *world, s32 triggerIds, s32 *firstIndex, s32 *lastIndex);

extern void Scene_ResetTransitionViewport(void);

extern void Track_RequestTrackByIds(s32, s32);

extern void Barrel_StopActorLoopingSound(void);

extern void Animpool_ReleaseSceneEffect(struct Shared_Actor *node);

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

void Link_ActivateTrigger(void *trigger) {
    TriggerActivationView *object = trigger;

    object->enabled |= 0x10;
    Scene_SetTriggerStateBit(&g_world, trigger, 1);
    if ((g_world.mode == 4) && (object->enabled & 2)) {
        Scene_QueueTriggerTimer(&g_world, trigger);
        return;
    }
    Link_DispatchTrigger(trigger);
}

void Link_DispatchTriggerExit(Record14 *trigger) {
    Record14 copy;
    u8 *bytes = (u8 *)trigger;

    bytes[14] |= 0x20;
    if (bytes[17] == 1) {
        copy = *trigger;
        copy.mode = 2;
        copy.state = 0;
        Link_DispatchTrigger(&copy);
    }
}

/* Clears bits 0x2000 and 0x100 of the flag word at offset 0x100 of an object. */

void Link_ClearActorFlagMask(struct LevelActor *object) {
    object->flags &= ~0x2000;
    object->flags &= ~0x100;
}

void Link_SetActorFlagMask(LevelActor *actor) {
    Gobjinst_AdvanceActorRootMotion(actor);
    actor->flags = (s32) (actor->flags | 0x2100);
}

void Link_RequestOwnerTrack(s32 owner, s32 unused1, s32 trackId) {
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

void Link_CaptureActorTransform(void *actor, void *transform) {
    (((struct TriggerActorTransformView *) ((s8 *) actor))->flags) = (s32) ((((struct TriggerActorTransformView *) ((s8 *) actor))->flags) | 0x40000000);
    (((struct TriggerTargetTransformView *) ((s8 *) transform))->capturedPositionX) = (f32) (((struct TriggerActorTransformView *) ((s8 *) actor))->positionX);
    (((struct TriggerTargetTransformView *) ((s8 *) transform))->capturedPositionY) = (f32) (((struct TriggerActorTransformView *) ((s8 *) actor))->positionY);
    (((struct TriggerTargetTransformView *) ((s8 *) transform))->capturedPositionZ) = (f32) (((struct TriggerActorTransformView *) ((s8 *) actor))->positionZ);
    (((struct TriggerTargetTransformView *) ((s8 *) transform))->capturedYaw) = (f32) (((struct TriggerActorTransformView *) ((s8 *) actor))->yaw);
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

    Barrel_StopActorLoopingSound();
    *stateFlags |= 0x20;
    flags = actor->weaponFlags & 0xFFFEFFFF;
    flags = flags & ~0x2000;
    flags = flags & ~0x100;
    actor->weaponFlags = flags;
    if (flags & 0x80000) {
        Animpool_ReleaseSceneEffect(actor);
    }
}

void Link_PlayTriggerSoundCallback(int unused0, int unused1, void *trigger) {
    TriggerSoundIdView *triggerRecord = trigger;
    SoundElement_PlayFlatSound(triggerRecord->soundId);
}

void Link_SelectTriggerMusic(void *trigger) {
    SoundElement_SetMusicPlaybackEnabled((s32) (((struct ResourceShortIdView *) ((s8 *) trigger))->resourceId));
}

void Link_PlayTriggerSound(void *trigger) {
    SoundElement_PlayFlatSound((((struct TriggerSoundIdView *) ((s8 *) trigger))->soundId));
}

/* 80279208.CPP */
/* Updates a table of triggers against masks: for each trigger the world accepts (always in world mode 4, otherwise when Scene_TestTriggerStateBit refuses it), a trigger not yet entered whose mask meets the enter mask is marked entered and runs its enter action (the id's action through Scene_TestTriggerKindFlags and Scene_DispatchSecondaryTriggersOfKind, or Link_DispatchTriggerExit without an id); it then counts as active when its mask meets the require mask, meets the enter mask, passes the paired exclude masks, is not flagged 0x1000 without 0x100 and passes Link_CheckTriggerMessage, and an active trigger runs its fire action once (through Scene_SetTriggerStateBit, Scene_DecrementTriggerCounter, Scene_TestTriggerCounterZero and Scene_ActivateTriggersOfKind for an id, or Link_ActivateTrigger without one). */

extern s32 Scene_TestTriggerStateBit(Shared_World *world, Trigger *trigger);

extern s32 Scene_TestTriggerKindFlags(Shared_World *world, s32 id);

extern void Scene_DispatchSecondaryTriggersOfKind(Shared_World *world, s32 id);

extern void Scene_SetTriggerStateBit(Shared_World *world, Trigger *trigger, s32 arg);

extern void Scene_DecrementTriggerCounter(Shared_World *world, s32 id);

extern s32 Scene_TestTriggerCounterZero(Shared_World *world, s32 id);

extern void Scene_ActivateTriggersOfKind(Shared_World *world, s32 id);

void Link_SetTriggerTrackCallback(int unused0, int unused1, void *trigger) {
    ResourceShortIdView *triggerRecord = trigger;
    SoundElement_SetTrackAndPeriodicPlayback(triggerRecord->resourceId);
}

void Link_SetTriggerTrack(void *trigger) {
    SoundElement_SetTrackAndPeriodicPlayback((((struct ResourceShortIdView *) ((s8 *) trigger))->resourceId));
}

void Link_ClearActorStateBit(struct Shared_Actor *actor) {
    actor->weaponFlags &= ~0x10000;
}

/** Set flag 0x10000 in the word at offset 0x100. */
void Link_SetActorStateBit(void *object) {
    Shared_Actor *actor = object;
    actor->weaponFlags |= 0x10000;
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

/* 80279208_2.CPP */
extern s32 g_activeLinkSequenceId;

s32 Link_CheckTriggerMessage(void *trigger, struct Player *player) {
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

/* 800C9C20.CPP */
/* ROM-grounded data: src/g_LinkDispatchmatchingtriggersWords1_us_rev1.c */
const float g_LinkDispatchmatchingtriggersWords1[1] = {
    4.0f,
};

#if defined(VERSION_DE)
float k_LinkDispatchmatchingtriggersEncodedWords[3] = {
    1.0f, 1.0f, 7.0f,
};
#endif

/* 800C9C0C.CPP */


