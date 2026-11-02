#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "AI/WEAPONAI.H"
#include "COMMON/LONE/WEAPON_LOCKED_NOTICE_TEXT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "TYPES.H"
#include "COMMON/MENU_TEXT.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Runs a weapon's two-shot alternate fire for its holder at 0x1D8: when the holder cannot use the
   alternate mode of its weapon (Player_HasAmmoForMode) a pending switch at 0x13C is cancelled and, if still
   unusable, the holder picks its next weapon at 0x770 through Weaponai_FindNextUsableWeapon; otherwise, while the
   alternate input 0x4000 is held and the weapon can fire (not stunned, and with ammunition in a single
   player game, clicking and showing the empty message when out), mode 1 with a second shot available
   arms mode 2, clicking and showing the unavailable message and falling back to mode 1 when mode 2
   cannot be used, and any other state resets to mode 1; finally, unless Weaponai_TryRequestFiringState handled the
   weapon or the actor has flag 0x400, it fires through Actor_RequestActorState_Damageai with the holder's state's fire
   mode from g_weaponActionRecords. */
extern WeaponActionRecord g_weaponActionRecords[];
extern char g_localPlayerProfiles[];
extern char g_playerViewRenderContext[];
#include "COMMON/MENU_MATCH_GLOBALS.H"

extern s16 Weaponai_FindNextUsableWeapon(void *);
extern s32 Player_GetProfileAchievementFlag(void *, s16);
extern s32 Player_GetPlayerIndex(void *, void *);
extern void Gsky_PostTargetedScreenMessage(void *, void *, s32, s32, f32);
extern s32 Weaponai_TryRequestFiringState(void *, void *);
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
#elif defined(VERSION_EU)
#elif defined(VERSION_EU_X)
#endif
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
                          1.0f);
        }
    }
    return ammo;
}
void Weaponai_ToggleFiringModeWithAmmoCheck(Shared_Actor *actor, WeaponFireState *fireState) {
    char *player;
    s32 action;
    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        if (fireState->mode != 2) {
            ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
            return;
        }
        fireState->mode = 1;
        if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
            ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
            return;
        }
    }
    if ((((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) && can_fire(player)) {
        if (fireState->mode == 1 && can_fire(player)) {
            fireState->mode = 2;
            if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
                SoundElement_PlayFlatSound(3405);
                if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
                    Gsky_PostTargetedScreenMessage((&((Shared_MenuData *)g_playerViewRenderContext)->object), ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, (u8)g_playerViewRenderContext[6153]),
                                  Player_GetPlayerIndex(g_playerViewRenderContext, player), 1.0f);
                }
                fireState->mode = 1;
            }
        } else {
            fireState->mode = 1;
        }
    }
    if (Weaponai_TryRequestFiringState(actor, fireState) == 0 && !(actor->weaponFlags & 0x400)) {
        Actor_RequestActorState(actor, fireState, action);
    }
}
