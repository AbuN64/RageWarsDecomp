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

/* Starts a player's secondary action: sets the request type to 1, refreshes the idle state when the current
 * action is not allowed, and when the player is flagged 0x4000, may fire and holds a charge either releases
 * a charged shot (sound 0x42E at the player, action 0xB) once charged past 24 or reports the empty weapon;
 * otherwise the default action for the player's state is started unless Weaponai_TryRequestFiringState handled the request
 * or the actor is flagged 0x400. Adapted from Weaponai_TryEnterAlternateStateEight with the same static fire check. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif

extern WeaponActionRecord g_weaponActionRecords[];
extern char g_localPlayerProfiles[];


extern char g_playerViewRenderContext[];
#include "COMMON/MENU_MATCH_GLOBALS.H"

extern s16 Weaponai_FindNextUsableWeapon(void *);
extern s32 Player_GetProfileAchievementFlag(void *, s16);
extern s32 SoundElement_PlaySoundAtPosition(s32, s32, s32, s32, void *, s32);
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
                          g_ammoCostFirstMessageDuration);
        }
    }
    return ammo;
}

void Weaponai_TryEnterAmmoCostState(Shared_Actor *actor, WeaponFireState *fireState) {
    char *player;
    s32 action;

    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    fireState->mode = 1;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
        return;
    }
    if ((((SharedPlayer *)(player))->views5E8.view6AC_45.inputFlags & 0x4000) && can_fire(player) && ((SharedPlayer *)(player))->views5E4.view5E4_0.health != 0) {
        if (((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[0] >= 25) {
            SoundElement_PlaySoundAtPosition(1070, ((SharedPlayer *)(player))->views0.positionBits.positionWords[0], ((SharedPlayer *)(player))->views0.positionBits.positionWords[1], ((SharedPlayer *)(player))->views0.positionBits.positionWords[2], (char *)&((SharedPlayer *)player)->views0.view8_2.position,
                          -1);
            Actor_RequestActorState(actor, fireState, 11);
        } else if (((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) {
            SoundElement_PlayFlatSound(3405);
            if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
                Gsky_PostTargetedScreenMessage(&((Shared_MenuData *)g_playerViewRenderContext)->object, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, (u8)g_playerViewRenderContext[6153]),
                              Player_GetPlayerIndex(g_playerViewRenderContext, player), g_ammoCostSecondMessageDuration);
            }
        }
        return;
    }
    if (Weaponai_TryRequestFiringState(actor, fireState) == 0 && !(actor->weaponFlags & 0x400)) {
        Actor_RequestActorState(actor, fireState, action);
    }
}
