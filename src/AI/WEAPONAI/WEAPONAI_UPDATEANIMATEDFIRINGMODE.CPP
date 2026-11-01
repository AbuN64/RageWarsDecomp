#include "COMMON/AIPROFILE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "AI/WEAPONAI.H"
#include "COMMON/LONE/WEAPON_LOCKED_NOTICE_TEXT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/GAMEPLAY_ROUND_RULES.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "TYPES.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MENU_TEXT.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/PLAYER_GETPLAYERINDEX.H"
#include "COMMON/INTEGERSTATE244.H"
#include "RENDER/WEAPON_INITIALIZECHARGEANDSTARTUPCUES_DATA.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Advances a player's charging action: when the trigger is released (controller latch for a controlled
 * player, otherwise flag 0x2000 with no hold and a disallowed action) or the cooldown is past g_weaponChargeCooldownLimit, it
 * switches to action 2, runs Playerai_StopPrimaryAttachedSound and Playerai_StopSecondaryAttachedSound and plays sound 0x978 at the player's target or
 * position; otherwise it grows the charge at 0x128 by the charge rate and, each time the cue timer at 0x64
 * runs out, restarts it and plays the charge cue (0x3FB in a multiplayer match without controller, 0x4CD
 * otherwise). */


extern s32 g_playerWeaponClassMode;


















static inline s32 released(void *actor, Player *player) {
    AiController *control;
    s32 latch;

    if (player->cooldown > g_weaponChargeCooldownLimit) {
        return 1;
    }
    if ((((Shared_Actor *)actor)->weaponFlags & 0x300000) && player->computer != 0) {
        control = player->controller;
        latch = control->fireRequested;
        control->fireRequested = 0;
        return latch == 0;
    }
    if (!(player->inputFlags & 0x2000)) {
        return 1;
    }
    if (player->locked != 0) {
        return 1;
    }
    return Player_HasAmmoForMode(player, player->selectedAction) == 0;
}

void Weaponai_UpdateSpinAndRepeatCue(Shared_Actor *actor, WeaponFireState *attack) {
    Player *player;
    CVector3 *position;
    PlayerCameraTargetView *target;

    player = actor->entity;
    target = player->camera;
    if (target != 0) {
        position = &target->position;
    } else {
        position = &player->pos;
    }
    if (released(actor, player)) {
        Actor_RequestActorState(actor, attack, 2);
        Playerai_StopPrimaryAttachedSound(player);
        Playerai_StopSecondaryAttachedSound(player);
        SoundElement_PlaySoundAtPosition(2424, *position, (s32)position, -1);
        return;
    }
    Graphu64_EaseValueToward(&attack->spin, (f32)g_weaponChargeSpinTarget * g_weaponChargeSpinScale, 0.4f);
    attack->cueTimer -= g_frameElapsedTime;
    if (attack->cueTimer <= 0.0f) {
        attack->cueTimer = g_weaponChargeCueInterval;
        if (player->computer == 0 && g_playerWeaponClassMode == 1) {
            Playerai_DispatchWeaponFireEffect(actor->entity, 1019);
        } else {
            Playerai_DispatchWeaponFireEffect(actor->entity, 1229);
        }
    }
}



void Weaponai_SettleSpinToThirdTurn(Shared_Actor *actor, WeaponFireState *fireState) {
    f32 spin;
    f32 remainingSpin;
    f32 animationSpin;
    Player *entity;
    void *weaponAnimation;

    entity = (Player *)actor->entity;
    if (fireState->variant != 4) {
        spin = fireState->spin;
        if (spin > 0.0f) {
            fireState->spin = Graphu64_DecayToZero(spin, g_weaponThirdTurnSpinDecay);
        } else {
            f32 value = fireState->spinStep;
            f32 period = g_weaponThirdTurnSpinPeriod;
            fireState->spin = 0.0f;
            if (period <= value) {
                do {
                    value -= period;
                    fireState->spinStep = value;
                } while (period <= value);
            }
            period = fireState->spinStep;
            if (period < g_weaponFirstThirdTurnLimit) {
                Graphu64_EaseValueToward(&fireState->spinStep, 0.0f, 0.125f);
            } else if (period < g_weaponSecondThirdTurnLimit) {
                Graphu64_EaseValueToward(&fireState->spinStep, 2.0943952f, 0.125f);
            } else if (period < g_weaponFinalThirdTurnLimit) {
                Graphu64_EaseValueToward(&fireState->spinStep, 4.1887903f, 0.125f);
            } else {
                Graphu64_EaseValueToward(&fireState->spinStep, 6.2831855f, 0.125f);
            }
        }
    }
    fireState->spinStep += (fireState->spin * g_frameElapsedTime) * 2.0f;
    remainingSpin = fireState->spin;
    weaponAnimation = entity->weaponAnimation;
    if (!(remainingSpin < 0.0f
              ? g_weaponNegativeSpinSpeedLimit < (-remainingSpin * g_weaponNegativeSpinSpeedScale)
              : g_weaponPositiveSpinSpeedLimit < (remainingSpin * g_weaponPositiveSpinSpeedScale))) {
        animationSpin = fireState->spin;
        if (animationSpin < 0.0f) {
            ((WeaponAnimationState *)weaponAnimation)->speed = (f32) (-animationSpin * g_weaponReverseAnimationSpinScale);
            return;
        }
        ((WeaponAnimationState *)weaponAnimation)->speed = (f32) (animationSpin * g_weaponForwardAnimationSpinScale);
        return;
    }
    ((WeaponAnimationState *)weaponAnimation)->speed = (f32) g_weaponStoppedAnimationSpeed;
}

/* Runs a player's rapid-fire action: when the current action is not allowed a type 2 request drops to type 1
 * and retries once before the idle state is refreshed; a player flagged 0x4000 that may fire with rounds at
 * 0x144 turns a type 1 request into type 2 (reporting the empty weapon and staying type 1 when firing is
 * not allowed) or any other request into type 1, and holds one round; the barrel spin at 0x11F4 then winds
 * down by 0.5 to 1 while type 1 or up by 0.05 to 2 while type 2 and turns the barrel frame at 0x11F8 (of
 * 8); finally the default action for the player's state starts unless Weaponai_TryRequestFiringState handled the request
 * or the actor is flagged 0x400. Adapted from Weaponai_TryEnterAlternateStateEight with the same static fire check. */
extern WeaponActionRecord g_weaponActionRecords[];
extern char g_localPlayerProfiles[];

extern s16 Weaponai_FindNextUsableWeapon(void *);
extern s32 Player_GetProfileAchievementFlag(void *, s16);
extern void Gsky_PostTargetedScreenMessage(void *, void *, s32, s32, f32);
extern s32 Weaponai_TryRequestFiringState(void *, void *);
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
#elif defined(VERSION_EU)
#elif defined(VERSION_EU_X)
#endif
static inline s32 can_fire(Player *player) {
    s32 ammo;
    if (player->cooldown > 0.0f) {
        return 0;
    }
    if (player->computer != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[player->slot * 400], player->selectedAction);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (player->camera != 0) {
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, player->camera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex), Player_GetPlayerIndex(&g_playerViewRenderContext, player),
                          1.0f);
        }
    }
    return ammo;
}
void Weaponai_UpdateAnimatedFiringMode(Shared_Actor *actor, WeaponFireState *fireState) {
    Player *player;
    s32 action;
    s32 single;
    player = actor->entity;
    action = g_weaponActionRecords[player->pose].action;
    if (Player_HasAmmoForMode(player, player->selectedAction) == 0) {
        if (fireState->mode != 2) {
            goto idle;
        }
        fireState->mode = 1;
        if (Player_HasAmmoForMode(player, player->selectedAction) == 0) {
        idle:
            player->weapon = Weaponai_FindNextUsableWeapon(player);
            return;
        }
    }
    if ((player->actionFlags & 0x4000) && can_fire(player) && fireState->rounds > 0) {
        single = 1;
        if (fireState->mode == single) {
            fireState->mode = 2;
            if (Player_HasAmmoForMode(player, player->selectedAction) == 0) {
                SoundElement_PlayFlatSound(3405);
                if (player->camera != 0) {
                    Gsky_PostTargetedScreenMessage(&g_playerViewRenderContext.object, player->camera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_playerViewRenderContext.object.language),
                                  Player_GetPlayerIndex(&g_playerViewRenderContext, player), 1.0f);
                }
                fireState->mode = single;
                goto spin;
            }
        } else {
            fireState->mode = single;
        }
        fireState->rounds = single;
    }
spin:
    if (fireState->mode == 1) {
        if (player->fireSpin > 1.0f) {
            player->fireSpin -= 0.5f;
        }
        if (player->fireSpin < 1.0f) {
            player->fireSpin = 1.0f;
        }
    } else if (fireState->mode == 2) {
        if (player->fireSpin < 2.0f) {
            player->fireSpin += 0.05f;
        }
        if (player->fireSpin > 2.0f) {
            player->fireSpin = 2.0f;
        }
    }
    player->fireFrame = (player->fireFrame + (s32)player->fireSpin) % 8;
    if (Weaponai_TryRequestFiringState(actor, fireState) == 0 && !(actor->weaponFlags & 0x400)) {
        Actor_RequestActorState(actor, fireState, action);
    }
}
