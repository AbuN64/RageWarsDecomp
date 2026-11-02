#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "AI/WEAPONAI.H"
#include "COMMON/LONE/WEAPON_LOCKED_NOTICE_TEXT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MENU_TEXT.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/GAMEPLAY_ROUND_RULES.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/INTEGERSTATE244.H"
#include "TYPES.H"
#include "RENDER/WEAPON_INITIALIZECHARGEANDSTARTUPCUES_DATA.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Runs a charge weapon's fire for its holder at 0x1D8: picks the holder's next weapon at 0x770 through
   Weaponai_FindNextUsableWeapon when the current one cannot be used; while the fire input 0x4000 is held on a weapon
   that can fire (not stunned, with ammunition, clicking and showing the empty message otherwise) in
   ready state 1 at 0x13C, a full charge of at least 50 at 0x5F6 fires action 5 and enters state 2,
   while a partial charge clicks and shows the not-ready message; otherwise it fires the state's action
   from g_weaponActionRecords unless Weaponai_TryRequestFiringState handles the weapon or the actor has flag 0x400, and when
   Weaponai_TryRequestFiringState handles it the barrel spin at 0x128 grows, drives the model's animation speed at 0x168
   (capped at 1), returns the weapon to state 1 and sets the spin step at 0x124. */
extern WeaponActionRecord g_weaponActionRecords[];

extern char g_localPlayerProfiles[];




extern char g_playerViewRenderContext[];

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

extern s32 Playerai_GetWeaponAmmo(void *actor, s16 weaponId);

/* Advances a player's second charging action: when the trigger is released (as in Weaponai_UpdateSpinAndRepeatCue) or the
 * cooldown is past g_weaponAlternateStunLimit, it switches to action 2, runs Playerai_StopPrimaryAttachedSound and Playerai_StopSecondaryAttachedSound, plays sound
 * 0x794 at the player's target or position and pushes the charge at 0x128 by the release amount; otherwise
 * it grows the charge by the charge rate and each time the cue timer at 0x64 runs out adds the cue period
 * back and plays the charge cue (0x3F9 in a multiplayer match without controller, 0x4CB otherwise).
 * Adapted from Weaponai_UpdateSpinAndRepeatCue. */




extern s32 g_playerWeaponClassMode;


extern s32 SoundElement_PlaySoundAtPosition(s16, CVector3, void *, s32);


static inline s32 released(void *actor, char *player) {
    char *control;
    s32 latch;

    if (((Shared_ActorView *)player)->stun > g_weaponAlternateStunLimit) {
        return 1;
    }
    if ((((LevelActor *)actor)->flags & 0x300000) && ((Shared_ActorView *)player)->remote != 0) {
        control = ((Shared_ActorView *)player)->owner;
        latch = ((NavigationBrainView *)control)->triggerLatch;
        ((NavigationBrainView *)control)->triggerLatch = 0;
        return latch == 0;
    }
    if (!(((Shared_ActorView *)player)->actionFlags & 0x2000)) {
        return 1;
    }
    if (((Shared_ActorView *)player)->actionState != 0) {
        return 1;
    }
    return Player_HasAmmoForMode(player, ((Shared_ActorView *)player)->selectedAction) == 0;
}

void Weaponai_UpdateSpinAndAlternateFire(Shared_Actor *actor, WeaponFireState *fire) {
    char *player;
    s32 action;
    char *model;
    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
    }
    if ((((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) && can_fire(player) && fire->mode == 1) {
        if (((SharedPlayer *)(player))->views5E8.chargeView.charge >= 50) {
            Actor_RequestActorState(actor, fire, 5);
            fire->mode = 2;
        } else {
            SoundElement_PlayFlatSound(3405);
            if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
                Gsky_PostTargetedScreenMessage((&((Shared_MenuData *)g_playerViewRenderContext)->object), ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, (u8)g_playerViewRenderContext[6153]),
                              Player_GetPlayerIndex(g_playerViewRenderContext, player), 1.0f);
            }
            fire->mode = 1;
        }
        return;
    }
    if (Weaponai_TryRequestFiringState(actor, fire) == 0) {
        if (!(actor->weaponFlags & 0x400)) {
            Actor_RequestActorState(actor, fire, action);
        }
    } else {
        fire->spin += fire->spin * g_frameElapsedTime * 2.0f;
        model = ((SharedPlayer *)(player))->views5E8.view698_37.emitter;
        if (!(fire->spin < 0.0f ? 1.0f < -fire->spin * 1.7904929f
                                                     : 1.0f < fire->spin * 1.7904929f)) {
            if (fire->spin < 0.0f) {
                ((WeaponAnimationState *)(model))->speed = -fire->spin * 1.7904929f;
            } else {
                ((WeaponAnimationState *)(model))->speed = fire->spin * 1.7904929f;
            }
        } else {
            ((WeaponAnimationState *)(model))->speed = 1.0f;
        }
        fire->spinStep = fire->spin * g_frameElapsedTime * 2.0f;
        fire->mode = 1;
    }
}

void Weaponai_SelectReleasedFireState(struct WeaponActorStateView *actor, void *stateController) {
    s16 weaponMode;
    s32 fireMode;
    void *value;

    value = actor->value;
    if (!(((struct WeaponAlternateFireFlagsView *)(value))->value & 0x2000)) {
        weaponMode = ((struct PlayerWeaponClassView *)(value))->value;
        if (weaponMode != 0) {
            if (weaponMode == 2) {
                fireMode = ((struct WeaponAttackPhaseView *)(stateController))->value;
                if (fireMode == 1) {
                    Actor_RequestActorState(actor, stateController, 5);
                } else if (fireMode == weaponMode) {
                    Actor_RequestActorState(actor, stateController, 9);
                } else {
                    goto check_height;
                }
            } else {
                goto check_state;
            }
        } else {
check_height:
            if (!(((struct WeaponReleasedFireLevelView *)(stateController))->value > g_weaponAlternateFireDelayLimit)) {
                Actor_RequestActorState(actor, stateController, 9);
            } else {
                Actor_RequestActorState(actor, stateController, 5);
            }
        }
        goto done;
check_state:
        if (Playerai_GetWeaponAmmo(value, weaponMode) == 1) {
            Actor_RequestActorState(actor, stateController, 7);
        } else {
            Actor_RequestActorState(actor, stateController, 5);
        }
done:
        ;
    }
}

void Weaponai_UpdateChargeAndRepeatCue(LevelActor *actor, Dest *attack) {
    char *player;
    CVector3 *position;
    char *target;

    player = actor->controller;
    target = ((Shared_ActorView *)player)->message;
    if (target != 0) {
        position = &((PlayerCameraTargetView *)target)->position;
    } else {
        position = &((Shared_ActorView *)player)->position.vector;
    }
    if (released(actor, player)) {
        Actor_RequestActorState(actor, attack, 2);
        Playerai_StopPrimaryAttachedSound(player);
        Playerai_StopSecondaryAttachedSound(player);
        SoundElement_PlaySoundAtPosition(1940, *position, position, -1);
        Graphu64_EaseValueToward(&attack->charge, (f32)g_weaponActionFiveSpinTarget * g_weaponFirstAlternateChargeScale, 0.4f);
        return;
    }
    Graphu64_EaseValueToward(&attack->charge, (f32)g_weaponActionFiveSpinTarget * g_weaponSecondAlternateChargeScale, 0.4f);
    attack->cueTimer -= g_frameElapsedTime;
    if (attack->cueTimer <= 0.0f) {
        attack->cueTimer += g_weaponAlternateChargeCueInterval;
        if (((Shared_ActorView *)player)->remote == 0 && g_playerWeaponClassMode == 1) {
            Playerai_DispatchWeaponFireEffect(actor->controller, 1017);
        } else {
            Playerai_DispatchWeaponFireEffect(actor->controller, 1227);
        }
    }
}
