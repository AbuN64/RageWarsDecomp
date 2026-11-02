#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "AI/WEAPONAI.H"
#include "COMMON/NAME.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/PLAYER_GETPLAYERINDEX.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Starts a player's action: when the current action is not allowed the idle state is refreshed; a player
 * flagged 0x4000 with no cooldown, no lock and the ammo option enabled checks its weapon's ammo, playing sound
 * 0xD4D and reporting the empty weapon when it is out, and takes action 8 when it may fire; otherwise the
 * default action for the player's state is started unless Weaponai_TryRequestFiringState handled the request or the actor is
 * flagged 0x400. */

#if defined(VERSION_EU) || defined(VERSION_EU_X)

#else
#endif
extern WeaponActionRecord g_weaponActionRecords[];
extern MatchRewardsRecord g_localPlayerProfiles[];

extern s32 g_weaponLockedNoticeText;


extern s16 Weaponai_FindNextUsableWeapon(void *);
extern s32 Player_GetProfileAchievementFlag(void *, s16);
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
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((SharedPlayer *)(player))->views1C.view5D4_45.playerIndex], ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
#if defined(VERSION_EU)
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera, ((g_weaponLockedNoticeTextEu)[g_languageIndex]), Player_GetPlayerIndex(&g_playerViewRenderContext, player),
#elif defined(VERSION_EU_X)
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera, ((g_weaponLockedNoticeTextEuX)[g_languageIndex]), Player_GetPlayerIndex(&g_playerViewRenderContext, player),
#else
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera, (g_weaponLockedNoticeText), Player_GetPlayerIndex(&g_playerViewRenderContext, player),
#endif
                          g_alternateStateEightMessageDuration);
        }
    }
    return ammo;
}

void Weaponai_TryEnterAlternateStateEight(Shared_Actor *actor, void *attack) {
    char *player;
    s32 action;

    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
        return;
    }
    if ((((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) && can_fire(player)) {
        Actor_RequestActorState(actor, attack, 8);
        return;
    }
    if (Weaponai_TryRequestFiringState(actor, attack) == 0 && !(actor->weaponFlags & 0x400)) {
        Actor_RequestActorState(actor, attack, action);
    }
}
