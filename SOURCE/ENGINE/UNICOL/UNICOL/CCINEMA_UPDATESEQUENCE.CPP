#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/GROUP.H"
#include "CAMERA/COLLISION_SWEEP_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/WORLD.H"
#include "COMMON/ENTRYRECAT8V4.H"
#include "TYPES.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "CAMERA/CCINEMA_UPDATESEQUENCE.H"
#include "MENU/TRACK_LOADTRACKSEQUENCE.H"
#include "MENU/MENU_PROCESSTRACKITEMEVENTS.H"
extern void Cache_ReleaseResource(void *cache, void *resource);

/* Starts the round once: unless already started, optionally resets the lead player (Playerai_ResetControllerMotion and its
 * three counters) and the player group, then when a new target id is pending selects it through
 * Scene_FindNearestPlacedObject_CcinemaUpdatesequence and Scene_LoadLevelResources, records the start time from Track_HasNoTrackRequestItems, marks the round started with
 * no pending target and copies the viewport rectangle into the active camera as floats. */













extern Group g_transientPlayerList;

extern struct { struct GameplayCamera *camera; } g_gameplayCameraList;

extern char g_controllerRumblePool;

extern struct MemoryUsageStats g_activeLinkSequenceId;

extern struct MemoryUsageStats g_activeSequenceTargetFound;

extern char g_nearestPlacedObjectResult;

extern struct MemoryUsageStats g_activeActorKind;

extern void Playerai_ResetControllerMotion(void *);

extern void Gsky_ActivateAllMessagePools(void *);

extern void Rumble_FreeAllPoolNodes(void *);

extern s32 Scene_FindNearestPlacedObject(void *, Vec3Words *, s32, void *);

extern void Scene_LoadLevelResources(void *, s32, s32);

extern s32 Track_HasNoTrackRequestItems(void);


extern u32 Cinema_GetPlaybackPauseState(void);

extern f32 g_frameElapsedTime;

/* Advances the current audio cue once per new frame: when CCinema_ProcessPendingTrack has no resource to release, the
 * cue's position steps by the frame time (as Cinema_AdvanceSequenceTime, stopping the round via CCinema_EnterSequenceScene past its
 * threshold and looping or holding at its length) and Menu_ProcessTrackItemEvents runs; a fading cue loses twice the
 * frame's fade step and, once below -0.5, stops fading and, if playing, runs its start and stop callbacks
 * (Cinema_InitializeSequenceOnce, Cinema_CloseSequenceOnce) and releases its sound; otherwise a playing, unpaused, non-looping cue with
 * no pending game event fires its cue callback past its cue point and, past its length, releases its sound
 * and fires its end callback; a still-playing cue then refreshes channel 10 through Cache_SetResourceActivityState. */
typedef void (*FuncPtr)(void);

extern s32 g_gameFrameCounter;

extern GameState g_gameStateBlock;

extern void Cinema_CloseSequenceOnce(void);


extern void Cache_SetResourceActivityState(unsigned int);

void CCinema_EnterSequenceScene(void) {
    Vec3Words origin;
    struct GameplayCamera *camera;
    Player *player;
    Group *group;
    s32 target;
    s32 found;
    Shared_World *table;

    target = g_cinemaSequenceState->targetD8;
    if (g_cinemaSequenceState->sequenceStarted != 0) {
        return;
    }
    if (g_cinemaSequenceState->pending != 0) {
        group = &g_transientPlayerList;
        player = group->lead;
        if (player != 0) {
            Playerai_ResetControllerMotion(player);
            player->weaponSpinStep = 0.0f;
            player->weaponSpin = 0.0f;
            player->weaponReset = 0;
        }
        Gsky_ActivateAllMessagePools(group->members);
        Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
    }
    if (target != -1) {
        table = &g_world;
        if (g_activeLinkSequenceId.value != target) {
            origin.w[0] = 0;
            origin.w[1] = 0;
            origin.w[2] = 0;
            found = Scene_FindNearestPlacedObject(table, &origin, target, &g_nearestPlacedObjectResult);
            g_activeActorKind.value = found;
            g_activeSequenceTargetFound.value = found != 0;
            Scene_LoadLevelResources(table, target, found != 0);
        }
    }
    g_cinemaSequenceState->noPendingTrackRequests = Track_HasNoTrackRequestItems();
    g_cinemaSequenceState->sequenceAdvanceRequested = 1;
    g_cinemaSequenceState->targetD8 = -1;
    g_cinemaSequenceState->sequenceStarted = 1;
    camera = g_gameplayCameraList.camera;
    if (camera != 0) {
        camera->viewWidth = g_cinemaSequenceState->loopBounds[1];
        camera->viewHeight = g_cinemaSequenceState->loopBounds[2];
        camera->viewLeft = g_cinemaSequenceState->loopBounds[3];
        camera->viewTop = g_cinemaSequenceState->loopBounds[4];
    }
}

s32 CCinema_ProcessPendingTrack(void) {
    s32 none;
    f32 value;
    f32 limit;
    Shared_MenuContext *record;

    none = -1;
    if (g_cinemaSequenceState->resourceDC == none) {
        return 0;
    }
    Track_LoadTrackSequence(g_cinemaSequenceState->resourceDC);
    g_cinemaSequenceState->resourceDC = none;
    if (Cinema_IsSequenceActive() != 0) {
        if (Cinema_GetPlaybackPauseState() != 0) {
            g_cinemaSequenceState->time20 = g_cinemaSequenceState->time;
        } else {
            record = g_cinemaSequenceState;
            record->time20 = *(volatile f32 *)&record->time;
            record->time += g_frameElapsedTime * g_cinemaSequenceTimeScale;
            if (record->start <= record->time) {
                CCinema_EnterSequenceScene();
            }
            value = g_cinemaSequenceState->time;
            limit = g_cinemaSequenceState->clipEnd;
            if (limit <= value) {
                if (g_cinemaSequenceState->loopBounds[0] == 1) {
                    g_cinemaSequenceState->time = value - limit;
                } else {
                    g_cinemaSequenceState->time = limit;
                    if (g_cinemaSequenceState->sequenceEndRequested != 0) {
                        g_cinemaSequenceState->state3C = 1;
                        g_cinemaSequenceState->sequenceEndRequested = 0;
                    }
                }
            }
        }
    }
    Menu_ProcessTrackItemEvents();
    return 1;
}

void CCinema_UpdateSequence(void) {
    Shared_MenuContext *record;
    f32 value;
    f32 limit;

    if (g_cinemaLastUpdatedFrame == g_gameFrameCounter) {
        return;
    }
    g_cinemaLastUpdatedFrame = g_gameFrameCounter;
    if (CCinema_ProcessPendingTrack() == 0) {
        if (Cinema_IsSequenceActive() != 0) {
            if (Cinema_GetPlaybackPauseState() != 0) {
                g_cinemaSequenceState->time20 = g_cinemaSequenceState->time;
            } else {
                record = g_cinemaSequenceState;
                record->time20 = *(volatile f32 *)&record->time;
                record->time += g_frameElapsedTime * 0.06666667f;
                if (record->start <= record->time) {
                    CCinema_EnterSequenceScene();
                }
                value = g_cinemaSequenceState->time;
                limit = g_cinemaSequenceState->clipEnd;
                if (limit <= value) {
                    if (g_cinemaSequenceState->loopBounds[0] == 1) {
                        g_cinemaSequenceState->time = value - limit;
                    } else {
                        g_cinemaSequenceState->time = limit;
                        if (g_cinemaSequenceState->sequenceEndRequested != 0) {
                            g_cinemaSequenceState->state3C = 1;
                            g_cinemaSequenceState->sequenceEndRequested = 0;
                        }
                    }
                }
            }
        }
        Menu_ProcessTrackItemEvents();
    }
    CCinema_ProcessPendingTrack();
    if (g_cinemaSequenceState->fadeRequested != 0 && (g_cinemaSequenceState->fade -= 2.0f * (g_frameElapsedTime * 0.06666667f)) < -0.5f) {
        g_cinemaSequenceState->fadeRequested = 0;
        g_cinemaSequenceState->fade = 0.0f;
        if (Cinema_IsSequenceActive() != 0) {
            Cinema_InitializeSequenceOnce(1);
            Cinema_CloseSequenceOnce();
            if (g_cinemaSequenceState->owner != 0) {
                Cache_ReleaseResource(0, g_cinemaSequenceState->owner);
            }
            g_cinemaSequenceState->owner = 0;
            g_cinemaSequenceState->resource = 0;
            g_cinemaSequenceState->active = 0;
            g_cinemaSequenceState->state3C = 0;
            g_cinemaSequenceState->fadeRequested = 0;
        }
        return;
    }
    CCinema_ProcessPendingTrack();
    if (Cinema_IsSequenceActive() != 0 && Cinema_GetPlaybackPauseState() == 0 && g_gameStateBlock.busy == 0 && g_gameStateBlock.paused == 0 &&
        g_cinemaSequenceState->loopBounds[0] == 0) {
        if (g_cinemaSequenceState->time >= g_cinemaSequenceState->end && g_cinemaSequenceState->initialized44 == 0) {
            FuncPtr cue = g_cinemaSequenceState->callback10;

            if (cue != 0) {
                g_cinemaSequenceState->callback10 = 0;
                cue();
            }
            g_cinemaSequenceState->initialized44 = 1;
        }
        if (g_cinemaSequenceState->time >= g_cinemaSequenceState->clipEnd && g_cinemaSequenceState->closed == 0) {
            if (g_cinemaSequenceState->owner != 0) {
                Cache_ReleaseResource(0, g_cinemaSequenceState->owner);
            }
            {
                FuncPtr end = g_cinemaSequenceState->onClose;

                g_cinemaSequenceState->owner = 0;
                g_cinemaSequenceState->resource = 0;
                g_cinemaSequenceState->active = 0;
                g_cinemaSequenceState->state3C = 0;
                g_cinemaSequenceState->fadeRequested = 0;
                if (end != 0) {
                    g_cinemaSequenceState->onClose = 0;
                    end();
                }
            }
            g_cinemaSequenceState->closed = 1;
        }
    }
    CCinema_ProcessPendingTrack();
    if (g_cinemaSequenceState->active != 0) {
        Cache_SetResourceActivityState(10);
    }
}
