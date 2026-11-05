#include "frontend_symbols.h"
#include "include_asm.h"
#include "Common/level_actor.h"
#include "Common/group.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/legacy_collision_actor.h"
#include "Common/motion_step.h"
#include "Common/triple.h"
#include "types.h"
#include "Camera/collision_sweep_views.h"
#include "Game/builddirectionmatrix.h"
#include "Engine/gregion.h"
#include "Graphu64/graphu64_buildlookatmatrix.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Libsn/nav_isballisticarcobstructed_data.h"
#include "Common/Lone/collision_current_actor.h"
#include "Common/player_sequence_state.h"
#include "Engine/Unicol/unicol.h"
#include "Collide/ccollision_testsegmentpolygon.h"
#include "Collide/ccollision_testsegmentdisk.h"
#include "Engine/Unicol/collide.h"
#include "Engine/Unicol/plane.h"
#include "Scene/scene_findactortriggerrange.h"
#include "Common/access_s8_10f.h"
#include "Common/shared_optionsscreen.h"
#include "Camera/ccinema_resetsequencecontext.h"
#include "Common/globals.h"
#include "Common/gameplay_camera.h"
#include "Common/aiprofile.h"
#include "Common/world.h"
#include "Common/track_spline.h"
#include "Camera/ccinema_updatesequence.h"
#include "Menu/track_loadtracksequence.h"
#include "Menu/menu_processtrackitemevents.h"
#include "Engine/rumble.h"
#include "Gsky/sky_posttargetedscreenmessage.h"
#include "Menu/Items/Scene/ovlscene_findplacedobjectsbykey.h"
#include "Common/ballisticparams.h"
#include "Common/cache_releaseresource.h"
#include "Common/Lone/controller_rumble_pool.h"
#include "Common/sessionhandlerrow.h"
#include "Common/weapon_screen_message_operations.h"
#include "Engine/Cinema/cinema.h"
#include "Common/game_session.h"
#include "Common/font_style_and_glyph_operations.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/track_requesttrackbykey.h"
#include "Common/audio_voice_slots.h"

/* CCINEMA_RESETSEQUENCECONTEXT.CPP */

/* Zeroes the resident game-state block, sets its four persistent-slot markers to -1, then runs the two state-machine resets that depend on it. */

void CCinema_ResetSequenceContext(void)
{
    Shared_MenuContext *p = g_cinemaSequenceState;

    p->owner = 0;
    p->resource = 0;
    p->unknown08 = 0;
    p->onClose = 0;
    p->callback10 = 0;
    p->reservedWord1 = 0;
    p->target = 0;
    p->time = 0;
    p->time20 = 0;
    p->time24 = 0;
    p->clipStart = 0;
    p->clipEnd = 0;
    p->start = 0;
    p->end = 0;
    p->active = 0;
    p->state3C = 0;
    p->sequenceStarted = 0;
    p->initialized44 = 0;
    p->closed = 0;
    p->pendingStartFlag = 0;
    p->sequenceAdvanceRequested = 0;
    p->pending = 0;
    p->pendingTrackId = 0;
    p->noPendingTrackRequests = 0;
    p->fadeRequested = 0;
    p->fade = 0;
    p->sequenceEndRequested = 0;
    p->mode = 0;
    p->reservedElements[0] = -1;
    p->reservedElements[1] = -1;
    p->reservedElements[2] = 0;
    p->reservedElements[3] = 0;
    p->reservedElements[4] = 0;
    p->reservedElements[5] = 0;
    p->reservedElements[6] = 0;
    p->targetD8 = -1;
    p->resourceDC = -1;
    p->requestE0 = -1;
    p->callbackE4 = 0;
    p->callbackE8 = 0;
    p->reservedWord2 = 0;
    p->position.x = 0;
    p->position.y = 0;
    p->position.z = 0;
    p->yaw = 0;
    p->response = 0;
    p->loopBounds[0] = 0;

    Cinema_ResetViewport();
    Cinema_ClearMessageCount();
}

/* CCINEMA_UPDATESEQUENCE.CPP */

/* Starts the round once: unless already started, optionally resets the lead player (Playerai_ResetControllerMotion and its
 * three counters) and the player group, then when a new target id is pending selects it through
 * Scene_FindNearestPlacedObject_CcinemaUpdatesequence and Scene_LoadLevelResources, records the start time from Track_HasNoTrackRequestItems, marks the round started with
 * no pending target and copies the viewport rectangle into the active camera as floats. */

/* Advances the current audio cue once per new frame: when CCinema_ProcessPendingTrack has no resource to release, the
 * cue's position steps by the frame time (as Cinema_AdvanceSequenceTime, stopping the round via CCinema_EnterSequenceScene past its
 * threshold and looping or holding at its length) and Menu_ProcessTrackItemEvents runs; a fading cue loses twice the
 * frame's fade step and, once below -0.5, stops fading and, if playing, runs its start and stop callbacks
 * (Cinema_InitializeSequenceOnce, Cinema_CloseSequenceOnce) and releases its sound; otherwise a playing, unpaused, non-looping cue with
 * no pending game event fires its cue callback past its cue point and, past its length, releases its sound
 * and fires its end callback; a still-playing cue then refreshes channel 10 through Cache_SetResourceActivityState. */
#include "Common/funcptr.h"

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
        if (g_activeLinkSequenceId != target) {
            origin.w[0] = 0;
            origin.w[1] = 0;
            origin.w[2] = 0;
            found = Scene_FindNearestPlacedObject(table, &origin, target, &g_nearestPlacedObjectResult);
            g_activeActorKind = found;
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
            Shared_MenuVoidCallback completion = g_cinemaSequenceState->callback10;

            if (completion != 0) {
                g_cinemaSequenceState->callback10 = 0;
                completion();
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
/* The close callback is invoked without the cinema state. Both requesters pass none, so a
 * deferred close callback is never set here. */
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

/* CCINEMA_DRAWMESSAGES.CPP */

void CCinema_DrawMessages(void)
{
  f32 messageScaleY;
  f32 screenScaleX;
  int unusedMessageIndex;
  f32 messageLineAdvance;
  f32 followingMessageScale;
  f32 messageDrawScale;
  f32 resolutionScale;
  f32 messageScaleX;
  s32 messageIndex;
  s32 messageY;
  s32 firstMessageIndex;
  s32 screenHeight;
  void *sequenceContext;
  if ((g_cinemaSequenceState->messageCount) > 0)
  {
    s32 messageLineHeight;
    s32 messageCenterX;
    messageLineHeight = 26;
    messageCenterX = g_hudReferenceViewportWidth / 2;
    OnScreen_SetupTextRendering();
    screenScaleX = (f32) (g_hudReferenceViewportWidth / 284);
    messageScaleY = (f32) (g_hudReferenceViewportHeight / 222);
    screenHeight = g_hudReferenceViewportHeight;
    if (screenHeight >= 223)
    {
      messageY = 180;
      resolutionScale = g_cinemaHighResolutionMessageScale;
      messageScaleX = screenScaleX * resolutionScale;
      messageScaleY *= resolutionScale;
    }
    else
    {
      messageY = 110;
      resolutionScale = g_cinemaLowResolutionMessageScale;
      messageScaleX = screenScaleX * resolutionScale;
      messageScaleY *= resolutionScale;
    }
    firstMessageIndex = 0;
    OnScreen_SetTextScale(messageScaleX, messageScaleY);
    sequenceContext = g_cinemaSequenceState;
    g_gameSession.hud.shadowX = 1;
    g_gameSession.hud.shadowY = 1;
    messageIndex = firstMessageIndex;
    if ((((Shared_MenuContext *)(sequenceContext))->messageCount) > firstMessageIndex)
    {
      unusedMessageIndex = 0;
      messageDrawScale = g_cinemaLeadMessageScale;
      followingMessageScale = g_cinemaFollowingMessageScale;
      do
      {
        Onscrn_DrawText(((Shared_MenuContext *)sequenceContext)->messages[messageIndex], messageCenterX, messageY, 0xFF, 1, 1, messageDrawScale, messageDrawScale);
        messageLineAdvance = ((f32) messageLineHeight) * messageScaleY;
        screenScaleX = (f32) (g_hudReferenceViewportWidth / 284);
        messageScaleY = ((f32) (g_hudReferenceViewportHeight / 222)) * followingMessageScale;
        messageY = (s32) (((f32) messageY) + messageLineAdvance);
        OnScreen_SetTextScale(screenScaleX * followingMessageScale, messageScaleY);
        messageIndex += 1;
      }
      while (messageIndex < ((Shared_MenuContext *)(sequenceContext = g_cinemaSequenceState))->messageCount);
    }
  }
}

s32 CCinema_RequestTrackWithCallbacks(s32 requestId, ContextCallback requestContextCallback, VoidCallback completionCallback) {
    s32 result;

    result = Track_RequestTrackByKey(requestId);
    if (g_cinemaSequenceState->requestE0 == requestId) {
        g_cinemaSequenceState->callbackE4 = requestContextCallback;
        g_cinemaSequenceState->callbackE8 = completionCallback;
    } else {
        if (requestContextCallback != 0) {
            requestContextCallback(g_cinemaSequenceState);
        }
        if (completionCallback != 0) {
            completionCallback();
        }
    }
    return result;
}

/* CCINEMA_PROCESSPENDINGTRACK_DATA.CPP */

const float k_CcinemaProcesspendingtrack[1] = {
    0.06666667f,
};
