#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "AI/WEAPONAI.H"
#include "COMMON/LONE/WEAPON_LOCKED_NOTICE_TEXT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "WEAPONS/PLAYERRECAT1450V1.H"
#include "TYPES.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Handles a player's charged secondary action: refreshes the idle state when the action is not allowed and
 * picks the effect position (the weapon's at 0x128, else the player's); a player flagged 0x4000 that may
 * fire with a type 1 request marks it type 2 and, once charged to 50, plays sound 0xB23 at that position and
 * takes action 5, otherwise reports the empty weapon and restores type 1; any other request Weaponai_TryRequestFiringState
 * handles becomes type 1 with 0x124 cleared, else the state's default action starts unless the actor is
 * flagged 0x400. Adapted from Weaponai_TryEnterAlternateStateEight with the same static fire check. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif

extern WeaponActionRecord g_weaponActionRecords[];
extern char g_localPlayerProfiles[];


extern char g_playerViewRenderContext[];
#include "COMMON/MENU_MATCH_GLOBALS.H"

extern s16 Weaponai_FindNextUsableWeapon(void *);
extern s32 Player_GetProfileAchievementFlag(void *, s16);
extern s32 SoundElement_PlaySoundAtPosition(s32, s32, s32, s32, void *, void *);
extern s32 Player_GetPlayerIndex(void *, void *);
extern void Gsky_PostTargetedScreenMessage(void *, void *, s32, s32, f32);
extern s32 Weaponai_TryRequestFiringState(void *, void *);

static inline s32 can_fire(char *player) {
    s32 ammo;

    if (((SharedPlayer *)(player))->views5E8.view11D8_147.jumpCooldown > 0.0f) {
        return 0;
    }
    if (((SharedPlayer *)(player))->views1450.view1450_0.computerControlled != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((SharedPlayer *)(player))->views1C.view5D4_45.playerIndex * 400], ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex), Player_GetPlayerIndex(g_playerViewRenderContext, player),
                          g_chargedAlternateFirstMessageDuration);
        }
    }
    return ammo;
}

void Weaponai_TryEnterChargedAlternateMode(Shared_Actor *actor, WeaponFireState *fireState) {
    char *player;
    s32 action;
    s32 *pos;
    s32 type;

    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
    }
    if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
        pos = (s32 *)((char *)&((GameplayCamera *)((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera)->position);
    } else {
        pos = (s32 *)&((SharedPlayer *)(player))->views0.view8_2.position;
    }
    if ((((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) && can_fire(player) && (type = fireState->mode) == 1) {
        fireState->mode = 2;
        if (((SharedPlayer *)(player))->views5E8.chargeView.charge >= 50) {
            SoundElement_PlaySoundAtPosition(2851, pos[0], pos[1], pos[2], pos, player);
            Actor_RequestActorState(actor, fireState, 5);
        } else {
            SoundElement_PlayFlatSound(3405);
            if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
                Gsky_PostTargetedScreenMessage(&((Shared_MenuData *)g_playerViewRenderContext)->object, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, (u8)g_playerViewRenderContext[6153]),
                              Player_GetPlayerIndex(g_playerViewRenderContext, player), g_chargedAlternateSecondMessageDuration);
            }
            fireState->mode = type;
        }
        return;
    }
    if (Weaponai_TryRequestFiringState(actor, fireState) == 0) {
        if (!(actor->weaponFlags & 0x400)) {
            Actor_RequestActorState(actor, fireState, action);
        }
        return;
    }
    fireState->mode = 1;
    fireState->spinStep = 0.0f;
}
