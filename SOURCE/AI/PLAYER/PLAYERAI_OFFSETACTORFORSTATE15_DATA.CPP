#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "SOUND/EXTERNS.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/OBJB.H"
#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
extern void Player_ReleaseObjectHandles(ResourceHandleOwner *object);

extern s32 g_playerSpecialAnimationTable;

/* Resets an actor's motion state, advances its wait timer, and fires action 0x13 or 0x14 once the timer passes its limit or the game mode allows it. */




extern f32 g_playerRoundEndWaitConstants[];



extern void Player_UpdateViewAngles(s32, s32, void *);




extern void ContPad_ClearControllerInput(void *object);

s32 CCinema_RequestTrackWithCallbacks(s32, s32, s32 *);




void Playerai_BeginRoundEndWait(Shared_ActorView *widget) {
    s32 clearedActorFlags;

    widget->unk_0x0860 = 0;
    Player_ReleaseObjectHandles((s32) widget);
    clearedActorFlags = widget->flags & 0xFF7FFFFF;
    widget->flags = clearedActorFlags;
    widget->unk_0x001C = 0;
    widget->unk_0x0020 = 0;
    widget->unk_0x0024 = 0;
    widget->stun = 0.0f;
    widget->flags = clearedActorFlags | 0x01000000;
    widget->marker.word = 0;
    widget->flags = clearedActorFlags | 0x01000000;
    if (widget->animationStateTable == &g_playerSpecialAnimationTable) {
        widget->effectId = 24100;
    } else {
        widget->effectId = 1;
    }
}

void Playerai_UpdateRoundEndWait(Shared_ActorView *player) {
    f32 wait;
    f32 waitLimit;
    CGameStatus *mode;

    player->flags &= 0xFF7FFFFF;
    player->unk_0x001C = 0;
    player->unk_0x0020 = 0;
    player->unk_0x0024 = 0;
    player->stun = 0.0f;
    player->marker.word = 0;
    player->flags |= 0x01000000;
    if (player->animationStateTable == &g_playerSpecialAnimationTable) {
        player->effectId = 24100;
    } else {
        player->effectId = 1;
    }
    waitLimit = g_playerRoundEndWaitConstants[1];
    wait = *(f32 *) &player->unk_0x0860 + g_frameElapsedTime;
    *(f32 *) &player->unk_0x0860 = wait;
    if (wait > waitLimit) {
        goto fire;
    }
    if ((mode = &g_gameSettings.counters)->round != 0 && mode->elapsed != 0) {
        fire:
        if ((mode = &g_gameSettings.counters)->round != 0 && 0 == mode->elapsed) {
            Player_SetPlayerState(player, player, 20);
        } else {
            Player_SetPlayerState(player, player, 19);
        }

    }
}

void Playerai_NoopRoundEndWaitFirst_de(void) {
}

void Playerai_NoopRoundEndWaitSecond_de(void) {
}

void Playerai_UpdateRoundEndViewAngles(s32 player, s32 body) {
    Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
}

/** Perform no operation. */
void Playerai_NoopRoundEndViewAngles_de(void) {
}

void Playerai_UpdateShortSequenceWait(void *player) {
    Shared_ActorView *actor = player;
    if (actor->unk_0x0850 == 0) {
        if ((actor->unk_0x0664 & 0x8000) == 0) {
            Graphu64_EaseValueToward(&actor->unk_0x072C, 1.308997f, 0.25f);
        }
        if (actor->actionTimer > g_playerShortSequenceWaitLimit) {
            Player_UpdateRunEndPlayer(player);
        }
    }
}

void Playerai_NoopShortSequenceWaitFirst_de(void) {
}

void Playerai_NoopShortSequenceWaitSecond_de(void) {
}

/** Set bit 0x20 in the word at object offset 0x122C. */
void Playerai_SetRunEndFlag(struct SharedPlayer *player) {
    player->views122C.view122C_0.flags |= 0x20;
}

void Playerai_UpdateRunEndTransition(void *runEndPlayer)
{
  f32 elapsedTime;
  elapsedTime = ((PlayerSequenceRunEndActorView *)(runEndPlayer))->poseTimer;
  if (g_playerRunEndTransitionDelay < elapsedTime)
  {
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->overkill = 1;
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->tintMode = -1;
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->tintTime = 0;
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->reactionFlags = (((PlayerSequenceRunEndActorView *)(runEndPlayer))->reactionFlags) & (~0x20);
    Player_UpdateRunEndPlayer(runEndPlayer);
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->scaleX = g_playerRunEndModelScale;
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->scaleY = g_playerRunEndModelScale;
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->scaleZ = g_playerRunEndModelScale;
    return;
  }
  ContPad_ClearControllerInput(((Shared_ActorView *)runEndPlayer)->profile);
  ((struct PlayerSequenceRunEndStateView *) ((char *) ((PlayerSequenceRunEndActorView *) runEndPlayer)->controller))->burstRequest = 0;
  ((struct PlayerSequenceRunEndStateView *) ((char *) ((PlayerSequenceRunEndActorView *) runEndPlayer)->controller))->actionFlagFrames = 0;
}

void Playerai_RequestTrackFifty(s32 requestValue) {
    g_playerTrackFiftyRequest = requestValue;
    CCinema_RequestTrackWithCallbacks(80, 0, &g_playerTrackFiftyCallbacks);
}

void Playerai_UpdateSequenceWait(void *player) {
    Shared_ActorView *actor = player;
    f32 value;

    if (actor->unk_0x0850 != 0) {
        return;
    }
    if ((actor->unk_0x0664 & 0x8000) == 0) {
        Graphu64_EaseValueToward(&actor->unk_0x072C, 1.308997f, 0.25f);
    }
    value = actor->actionTimer;
    if (g_playerSequenceWaitLimit < value) {
        Player_UpdateRunEndPlayer(player);
    }
}

void Playerai_StartSequenceTen(void *a, void *b) { Playerai_TryStartPlayerSequence(a, b, 10); }
