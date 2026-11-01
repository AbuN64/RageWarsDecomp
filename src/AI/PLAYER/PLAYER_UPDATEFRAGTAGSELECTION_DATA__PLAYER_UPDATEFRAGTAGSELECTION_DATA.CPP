#include "COMMON/PLAYER_RECORD_AND_FRAGTAG_VIEWS.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "GFX/PLAYER_UPDATEFRAGTAGSELECTION_DATA.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/ENTRYRECAT8V4.H"
#include "TYPES.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

extern void Playerai_ApplyPeriodicDamage(s32 player, s32 unused, s32 period, s32 kind);

extern s32 InstHdr_FindActorModelEntry(void *);

extern f32 g_frameElapsedTime;

/** Set up a player's starting lives from the game mode and character, then reset its respawn state. */








extern FragTagMatchRulesView g_gameSettings;

extern Course *g_currentStagePreset;

extern char g_localPlayerProfiles[][0x190];

extern unsigned char Player_GetLevelProgress(char *, int);

extern u8 g_playerHudSpriteMode;

extern s32 g_hudReferenceViewportWidth;


void Onscrn_SetupSpriteMode(s32 color);

extern const struct ScalarPair g_playerEyeMarkerYawAndHeight;



extern void Player_BuildPlayerViewTransform(Player1680 *, Matrix *);

extern void Graphu64_GetMatrixTranslation(Matrix *, CVector3 *);

extern void Graphu64_IdentityMatrix(Matrix *);

extern void TranslateMatrix(Matrix *, float, float, float);

extern void Graphu64_ConvertMatrixToFixed(Matrix *, void *);

static inline void getEye(Player1680 *player, CVector3 *pos) {
    Matrix frame;

    if (player->mount != 0) {
        *pos = player->mount->eyePosition;
    } else {
        Player_BuildPlayerViewTransform(player, &frame);
        Graphu64_GetMatrixTranslation(&frame, pos);
    }
}

static inline float getYaw(void) {
    return g_playerEyeMarkerAngle * g_playerEyeMarkerYawAndHeight.first;
}

extern void Playerai_InitializePlayerHealth(void *player);

void Playerai_ApplyPeriodicHazardDamage(s32 player, s32 unused) {
    Playerai_ApplyPeriodicDamage(player, unused, 5, 27);
}

void Playerai_UpdateModelBlend(void *actorView, void *bodyActor) {
    void *result;
    f32 t0;
    f32 t1;

    result = (void *)InstHdr_FindActorModelEntry(bodyActor);
    if (result != 0) {
        t0 = ((ModelBlend *)result)->blend;
        t1 = ((Shared_ActorView *)actorView)->modelBlend;
        t0 = t0 - t1;
        t0 = t0 * g_playerModelBlendRate;
        t1 = t1 + t0;
        ((Shared_ActorView *)actorView)->modelBlend = t1;
    }
}

void Playerai_UpdateCountdown(void *player) {
    f32 remainingTime;
    f32 previousTime;
    previousTime = (((struct PlayerTimedPowerupView *) ((s8 *) player))->countdownSeconds);
    if (previousTime > 0.0f) {
        remainingTime = previousTime - g_frameElapsedTime;
        (((struct PlayerTimedPowerupView *) ((s8 *) player))->countdownSeconds) = remainingTime;
        if (remainingTime < 0.0f) {
            (((struct PlayerTimedPowerupView *) ((s8 *) player))->countdownSeconds) = 0.0f;
        }
    }
}

void Playerai_InitializeLivesAndRespawn(PlayerFragTagSelectionView *player) {
    short state;

    if (g_gameSettings.started != 0) {
        if (g_gameSettings.mode == 1 && player->isBot == 0) {
            player->lives = (unsigned char)Player_GetLevelProgress(g_localPlayerProfiles[player->character], player->info->characterKind) / 2 + 1;
        }
        if (g_gameSettings.mode == 4 && player->isBot == 0 && g_currentStagePreset != 0) {
            player->lives = g_currentStagePreset->laps;
        }
        state = 1;
    } else {
        state = 3;
    }
    player->state = state;
    player->timer = 0;
}

void Playerai_DrawHudSprite1FC(char *player, char *view) {
    f32 x, y;
    f32 sx, sy;
    f32 bx, by;
    f32 t1, t2;
    f32 w;
    f32 screenX, screenY;

    Onscrn_SetupSpriteMode(g_playerHudSpriteMode);

    x = ((Shared_HudView *)view)->width;
    sx = x / (f32) g_hudReferenceViewportWidth;
    bx = sx * g_playerHudSprite1FCOffset;

    y = ((Shared_HudView *)view)->height;
    sy = y / (f32) g_hudReferenceViewportHeight;
    by = sy * g_playerHudSprite1FCOffset;

    t1 = ((Shared_HudView *)view)->x + x;
    t2 = ((Shared_HudView *)view)->y + y;
    w = ((SharedPlayer *)player)->views5E8.view7BC_101.timer;

    screenX = t1 + bx;
    screenY = t2 + by;

    OnScreen_DrawSpriteResource(508, (s32) w, (s16) (s32) screenX, (s16) (s32) screenY, sx, sy, 1);
}

void Playerai_DrawHudSprite1FB(void *unusedPlayer, struct ScreenRectangle *viewport)
{
  f32 x;
  f32 y;
  f32 ax;
  f32 ay;
  f32 sx;
  f32 sy;
  f32 bx;
  f32 by;
  f32 screenX;
  f32 screenY;
  Onscrn_SetupSpriteMode(g_playerHudSpriteMode);
  x = viewport->x;
  ax = x * g_playerHudSprite1FBCenterScale;
  y = viewport->y;
  ay = y * g_playerHudSprite1FBCenterScale;
  sx = x / ((f32) g_hudReferenceViewportWidth);
  bx = sx * g_playerHudSprite1FBOffset;
  sy = y / ((f32) g_hudReferenceViewportHeight);
  by = sy * g_playerHudSprite1FBOffset;
  screenX = ((viewport->width) + ax) - bx;
  screenY = ((viewport->height) + ay) - by;
  OnScreen_DrawSpriteResource(507, 0, (s16) ((s32) (((viewport->width) + ax) - bx)), (s16) ((s32) screenY), sx, sy, 1);
}

void Playerai_DrawHudSprite201(char *player, char *view) {
    f32 x, y;
    f32 sx, sy;
    f32 bx, by, cz;
    f32 t1, t2;
    f32 w;
    f32 screenX, screenY;

    Onscrn_SetupSpriteMode(g_playerHudSpriteMode);

    x = ((Shared_HudView *)view)->width;
    sx = x / (f32) g_hudReferenceViewportWidth;
    bx = sx * g_playerHudSprite201Offset;

    y = ((Shared_HudView *)view)->height;
    sy = y / (f32) g_hudReferenceViewportHeight;
    by = sy * g_playerHudSprite201Offset;

    cz = sy * g_playerHudSprite201HeightScale;

    t1 = ((Shared_HudView *)view)->x + x;
    t2 = ((Shared_HudView *)view)->y + y;
    w = ((SharedPlayer *)player)->views5E8.view7BC_101.timer;

    screenX = t1 + bx;
    screenY = t2 + by;

    OnScreen_DrawSpriteResource(513, (s32) w, (s16) (s32) screenX, (s16) (s32) screenY, sx, cz, 1);
}

void *Playerai_ResetProfileState(void *actorObject) {
    struct Player *player = actorObject;
    AiProfile *p = player->profile;
    p->state90 = 0;
    return p;
}

s32 Playerai_IsRoundEndState(void *actorObject) {
    Shared_ActorView *player = actorObject;
    s16 action;
    action = player->action;
    if ((action == 21) || (action == 19) || (action == 20)) {
        return 1;
    }
    return 0;
}

void Playerai_BuildEyeMarkerTransform(Player1680 *player) {
    Matrix mtx;
    CVector3 pos;

    getEye(player, &pos);
    Graphu64_IdentityMatrix(&mtx);
    BuildYawMatrix(&mtx, getYaw());
    TranslateMatrix(&mtx, pos.x, pos.y + g_playerEyeMarkerYawAndHeight.second, pos.z);
    Graphu64_ConvertMatrixToFixed(&mtx, &player->views[g_lightingBufferIndex]);
}

void *Playerai_GetEligiblePlayerByIndex(void *playerWorld, u32 eligiblePlayerIndex) {
    struct PlayerWorldActorTables *world = playerWorld;
    Shared_ActorView *actor;
    s32 eligibleOrdinal;

    actor = 0;
    eligibleOrdinal = 0;
    if (eligiblePlayerIndex < 8U) {
        actor = (void *)world->players;
        if (actor != 0) {
            do {
                if ((u8)actor->controls->resetFlag == 0) {
                    if (eligibleOrdinal == (s32) eligiblePlayerIndex) {
                        return actor;
                    }
                    eligibleOrdinal += 1;
                }
                actor = actor->next;
            } while (actor != 0);
        }
    }
    return actor;
}

void Playerai_ClearPlayerResetFlags(char *object) {
    struct PlayerWorldActorTables *world = (void *)object;
    Shared_ActorView *record = (void *)world->players;
    while (record != 0) {
        Shared_ControlView *nested = record->controls;
        if ((u8)nested->resetFlag == 1) {
            nested->resetFlag = 0;
        }
        record = record->next;
    }
}

void Playerai_ResetAllPlayerHealth(void *object) {
    struct PlayerWorldActorTables *world = (void *)object;
    Shared_ActorView *record = (void *)world->players;
    if (record != 0) {
        do {
            record->controls->transientFlag = 0;
            Playerai_InitializePlayerHealth(record);
            record = record->next;
        } while (record != 0);
    }
}

s32 Playerai_CountEligiblePlayers(char *object) {
    struct PlayerWorldActorTables *world = (void *)object;
    Shared_ActorView *record = (void *)world->players;
    s32 count = 0;
    while (record != 0) {
        Shared_ControlView *nested = record->controls;
        if ((u8)nested->resetFlag == 0) {
            count += 1;
        }
        record = record->next;
    }
    return count;
}

s32 Playerai_CountActivePlayers(char *object) {
    struct PlayerWorldActorTables *world = (void *)object;
    Shared_ActorView *record = (void *)world->players;
    s32 count = 0;
    while (record != 0) {
        if (record->actorState != 0) {
            count += 1;
        }
        record = record->next;
    }
    return count;
}
