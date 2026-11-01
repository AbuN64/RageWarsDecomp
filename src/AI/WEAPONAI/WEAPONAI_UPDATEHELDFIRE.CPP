#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/NAME.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/AIPROFILE.H"
#include "WEAPONS/PLAYERRECAT1450V1.H"
#include "RENDER/PLAYERAI_TOGGLEFORCEMARKER.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Runs a player's aiming action: refreshes the idle state when the action is not allowed; while the aim
 * flag 0x4000 is held and the weapon may fire (as in Weaponai_TryEnterAlternateStateEight) the attack enters aiming and, for scoped
 * weapons, zooms in through Playerai_ToggleForceMarker_WeaponaiUpdateheldfire; when aiming stops it zooms back out unless the zoom was already
 * cancelled; then the default action for the player's state starts unless Weaponai_TryRequestFiringState handled the
 * request or the actor is flagged 0x400. Adapted from Weaponai_TryEnterAlternateStateEight with the aiming state.
 */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern u8 *g_weaponLockedNoticeTextEu[];
extern u8 *g_weaponLockedNoticeTextEuX[];

#else
#endif
extern WeaponActionRecord g_weaponActionRecords[];
extern MatchRewardsRecord g_localPlayerProfiles[];

extern u8 *g_weaponLockedNoticeText[];


extern s32 Weaponai_FindNextUsableWeapon(void *);
extern s32 Player_GetProfileAchievementFlag(void *, s32);
extern s32 Player_GetPlayerIndex(void *, void *);
extern CCameraText *Gsky_PostTargetedScreenMessage(void *, void *, u8 *, s32, f32);
extern s32 Weaponai_TryRequestFiringState(void *, void *);

#if defined(VERSION_EU_X)
extern void Playerai_ToggleForceMarkerEuropean(void *, s32);

#else
#endif
static inline s32 can_fire(char *player, f32 *scale) {
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
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera, g_weaponLockedNoticeText[0], Player_GetPlayerIndex(&g_playerViewRenderContext, player),
#endif
                          *scale);
        }
    }
    return ammo;
}

void Weaponai_UpdateForceMarkerTrigger(Shared_Actor *actor, WeaponFireState *attack) {
    char *player;
    s32 action;

    player = (char *)actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
    }
    if ((((SharedPlayer *)(player))->views5E8.view6AC_45.inputFlags & 0x4000) && can_fire(player, &k_forceMarkerLockedNoticeScale)) {
        attack->triggered = 1;
        if (((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x2000) {

#if defined(VERSION_EU_X)
            Playerai_ToggleForceMarkerEuropean(player, 0);
#else
            Playerai_ToggleForceMarker(player, 0);
#endif

            attack->alternate = 1;
        }
    } else if (attack->triggered != 0) {
        if (attack->alternate == 0) {

#if defined(VERSION_EU_X)
            Playerai_ToggleForceMarkerEuropean(player, 1);
#else
            Playerai_ToggleForceMarker(player, 1);
#endif

        } else {
            attack->alternate = 0;
        }
        attack->triggered = 0;
    }
    if (Weaponai_TryRequestFiringState(actor, attack) == 0 && !(actor->weaponFlags & 0x400)) {
        Actor_RequestActorState(actor, attack, action);
    }
}
/* k_forceMarkerLockedNoticeScale and k_heldFireLockedNoticeScale are the two message-duration floats of this unit's literal pool. */
typedef struct HeldPlayerState {
    u8 pad0[8];
    CVector3 position;
    u8 pad14[0x594 - 0x14];
    s32 mode594;
    u8 pad598[0x5F4 - 0x598];
    s16 window5F4;
    s16 window5F6;
    s16 charge5F8;
    u8 pad5FA[0x62E - 0x5FA];
    s16 mode;
    u8 pad630[0x6AC - 0x630];
    s32 buttons;
    u8 pad6B0[0x788 - 0x6B0];
    s32 handled788;
    s32 handled78C;
} HeldPlayerState;

void Weaponai_UpdateHeldFire(Shared_Actor *actor, WeaponFireState *attack) {
    HeldPlayerState *state;
    s32 finished;
    state = actor->entity;
    if (attack->triggerMode != 0) {
        if (state->mode == 4 || state->mode == 14 || state->mode == 15) {
            goto no;
        }
        if (state->mode == 10) {
            if (!(state->buttons & 0x4000)) goto no;
            if (state->charge5F8 == 0) goto no;
            goto yes;
        } else if (state->mode == 3) {
            if ((state->buttons & 0x6000) != 0x6000) goto no;
            if (state->window5F4 == 0) goto no;
            if (state->window5F6 != 0) goto yes;
        no:
            finished = 0;
            goto done;
        yes:
            finished = 1;
        done:;
        } else {
            finished = Weaponai_TryRequestFiringState(actor, attack);
        }
        if (finished != 0) {
            attack->triggerMode = 0;
            attack->queuedAction = -1;
        } else {
            if (state->mode == 5) {
                Playerai_StopSecondaryAttachedSound(state);
                SoundElement_PlaySoundAtPosition(1120, state->position, &state->position, -1);
            }
            if (state->mode == 3 && can_fire((char *)state, &k_heldFireLockedNoticeScale) != 0 && state->mode594 == 2) {
                Actor_RequestActorState(actor, attack, 11);
                Playerai_BeginHeldAlternateFire(state);
            } else {
                Actor_RequestActorState(actor, attack, 2);
            }
        }
        state->handled788 = 1;
        state->handled78C = 0;
    }
}
