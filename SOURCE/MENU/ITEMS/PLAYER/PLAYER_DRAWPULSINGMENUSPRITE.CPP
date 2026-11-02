#include "COMMON/ACTORRECAT260.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "../../../../sdk/include/PFS/PLAYER_DRAWPULSINGMENUSPRITE.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

extern void Player_PlacePlayerForRound(void *player);
/* Forwards menuState's word at 0x1C to Player_PlacePlayerForRound and always reports success. */



/* Pulses the caption intensity on a 512-step triangle wave and redraws the caption sprite centred on the entry, dropped one full line or a short line when the wide-layout flag is clear. */



/* When team sync is enabled, copies a player's team flag from its actor (byte 0x8F of the record at
   0x5D8) into g_matchRoundCounters if it is 1; then resumes the script g_gameSession through Match_ResetMatchControllerState in mode
   1 or else clears the actor's word at 0x5D0; returns 1. Matched through a local pointer to
   g_matchRoundCounters and the team byte held in a local. */










#include "COMMON/GAME_SESSION.H"

extern void Match_ResetMatchControllerState(char *);

/* Advances the actor inactivity timer and reports pending menu state. */
s32 Playerai_IsPlayerInactive(void *);

 /* extern */


/* Points a field's text at g_fragTagOnLabelText when the option g_resultExitPending is set and at g_fragTagOffLabelText otherwise, and returns
   zero: the label an option menu shows for that option. */





/* Sets the byte at offset 0x8E of the object reached through offset 0x1C of the second argument
   and then offset 0x5D8, and returns one. */






s32 Player_SetNestedItemFlag(void *unused, struct NestedPlayerMenuFlagContext *root) {
    root->middle->leaf->flag = 1;
    return 1;
}

s32 Player_RespawnItemPlayer(void *unused0, PlayerRespawnMenuContext *menuState) {
    Player_PlacePlayerForRound(menuState->actor);
    return 1;
}

void Player_DrawPulsingMenuSprite(PulsingMenuSpriteView *spriteState, CaptionEntry *caption, s32 unusedEventKind, MenuStyle *menuStyle) {
    s32 phase;
    s32 amount;
    s32 half;
    s32 drop;
    f32 scale;
    f32 sx;
    phase = spriteState->pulsePhase = (spriteState->pulsePhase + 20) % 512;
    if (phase >= 256) {
        amount = (s32) ((f32) (512 - phase) * menuStyle->alpha * menuStyle->fade);
    } else {
        amount = (s32) ((f32) phase * menuStyle->alpha * menuStyle->fade);
    }
    Onscrn_SetupSpriteMode(amount);
    drop = 80;
    half = caption->width >> 1;
    if (g_frontendCurrentVideoModeIndex == 0) {
        drop = 45;
    }
    sx = caption->scaleX;
    scale = *(&k_playerMenuSpriteScaleConstants + 1);
    OnScreen_DrawSpriteResource(spriteState->spriteResource, 0, caption->x - (half * 8), caption->y + drop,
                  sx * scale, caption->scaleY * scale, 1);
}

int Player_ResumePlayerFromMenu(int unused, PlayerMenuResumeContext *player) {
    CGameStatus *sync = &g_gameSettings.counters;
    int team;

    if (sync->m_bFragTagOn != 0) {
        team = player->actor->info->fragTagEnabled;
        if (team == 1) {
            sync->m_FragTagMode = team;
        }
    }
    if (g_sessionOptionResetMode == 1) {
        Match_ResetMatchControllerState(&g_gameSession);
    } else {
        player->actor->waiting = 0;
    }
    return 1;
}

s32 Player_UpdatePlayerRespawnDelay(PlayerRespawnMenuContext *menuState) {
    CGameStatus *state;
    s32 respawnFrames;
    s32 roundFinished;
    PlayerRespawnMenuActor *player;
    player = menuState->actor;
    if ((player->computerControlled == 0) && (Playerai_IsPlayerInactive(player) != 0)) {
        respawnFrames = player->respawnDelayFrames + 1;
        player->respawnDelayFrames = respawnFrames;
        if (respawnFrames >= 76) {
            Player_PlacePlayerForRound(menuState->actor);
            return 1;
        }
    }
    roundFinished = 0;
    state = &g_gameSettings.counters;
    if (state->round || state->elapsed || state->state) roundFinished = 1;
    return roundFinished;
}

s32 Player_SelectFragTagLabel(struct PakActionLabelView *field) {
    if (g_gameSettings.counters.m_bFragTagOn != 0) {
        field->text = g_fragTagOnLabelText;
    } else {
        field->text = g_fragTagOffLabelText;
    }
    return 0;
}
