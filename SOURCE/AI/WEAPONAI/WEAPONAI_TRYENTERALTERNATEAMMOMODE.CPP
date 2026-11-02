#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "AI/WEAPONAI.H"
#include "COMMON/LONE/WEAPON_LOCKED_NOTICE_TEXT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "TYPES.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Continues a player's secondary action: refreshes the idle state when the current action is not allowed;
 * a player flagged 0x4000 that may fire with a type 1 request takes action 5 and marks the request type 2,
 * unless it is in state 4 with a charge under 48, which reports the empty weapon; otherwise a request
 * Weaponai_TryRequestFiringState handles is marked type 1 and the default action for the player's state is started unless
 * the actor is flagged 0x400. Adapted from Weaponai_TryEnterAlternateStateEight with the same static fire check. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif

extern WeaponActionRecord g_weaponActionRecords[];
extern char g_localPlayerProfiles[];


extern char g_playerViewRenderContext[];
#include "COMMON/MENU_MATCH_GLOBALS.H"

extern s16 Weaponai_FindNextUsableWeapon(void *);
extern s32 Player_GetProfileAchievementFlag(void *, s16);
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
                          g_alternateAmmoFirstMessageDuration);
        }
    }
    return ammo;
}

void Weaponai_TryEnterAlternateAmmoMode(Shared_Actor *actor, WeaponFireState *fireState) {
    char *player;
    s32 action;

    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
    }
    if ((((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) && can_fire(player) && fireState->mode == 1) {
        if (((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[0] >= 48 || ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon != 4) {
            Actor_RequestActorState(actor, fireState, 5);
            fireState->mode = 2;
            return;
        } else {
            SoundElement_PlayFlatSound(3405);
            if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
                Gsky_PostTargetedScreenMessage(&((Shared_MenuData *)g_playerViewRenderContext)->object, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, (u8)g_playerViewRenderContext[6153]),
                              Player_GetPlayerIndex(g_playerViewRenderContext, player), g_alternateAmmoSecondMessageDuration);
            }
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
}
