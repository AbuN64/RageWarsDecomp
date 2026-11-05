#include "Data/rom_callback_word.h"
#include "Common/level_actor.h"
#include "Common/shared_optionsscreen.h"
#include "Common/gameplay_camera.h"
#include "include_asm.h"
#include "Weapons/weapon_switch_actions.h"
#include "Common/vector4f.h"
#include "Common/ai_behaviour_types.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Weapons/actor_requestactorstate.h"
#include "Render/soundelement_playflatsound.h"
#include "Common/playerprofiles.h"
#include "Common/gameplay_transition.h"
#include "Common/triple.h"
#include "Common/resourceloadstate.h"
#include "Common/model_render.h"
#include "Common/shared_gameslot.h"
#include "Common/player_sequence_state.h"
#include "Common/self.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/animationtriggerdefinition.h"
#include "Render/playerai_toggleforcemarker.h"
#include "Weapons/charge_and_linked_actor_handles.h"
#include "Weapons/player_movement_interfaces.h"
#include "Weapons/weapon_charge_latch.h"
#include "Common/weapon_screen_message_operations.h"
#include "Weapons/startup_cues_and_side_yaw.h"
#include "Common/objb.h"
#include "Weapons/weapon_mode_origin.h"
#include "Common/obj.h"
#include "Common/weapon_special_fire.h"
#include "Common/actorresourceheader.h"
#include "Common/mtx.h"
#include "Common/shared_particleinstance.h"
#include "Game/builddirectionmatrix.h"
#include "Weapons/pitch_translation_and_spin_actions.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Ai/Player/player_startplayeranimation.h"
#include "Ai/player_alternate_fire.h"
#include "Gsky/sky_posttargetedscreenmessage.h"
#include "Particle/particle_releaseownerlistoneeffects.h"
#include "Weapon/weapon.h"
#include "Weaponai/weaponai_drawredmarkerquad__weaponai.h"
#include "World/playerprofile.h"
#include "Render/weapon_initializechargeandstartupcues_data.h"
#include "Ai/weapon_updatealternatefire__weaponai.h"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Common/shared_worldfunc.h"
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "World/playerai_respawnfragtagplayer.h"
#endif
#include "Graphu64/graphu64_buildlookatmatrix.h"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Menu/Pak/menu_createmenufromtemplate.h"
#endif
#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "Common/Lone/weapon_locked_notice_text.h"
#endif
#include "Ai/ai_shared_symbols.h"
#include "Ai/weaponai.h"
#include "Ai/ai_functions.h"
#include "Ai/ai_address_labels.h"
#include "Ai/Weapon/weapon.h"

void Weapon_SpawnTargetPlayerFireEffect(void *aiTarget, s32 behaviorFlags, s32 effect) {
    AiTarget *target = aiTarget;
    Playerai_DispatchWeaponFireEffect(target->player, effect);
}

/** Return the value pointed to by the indexed pointer table entry. */
int Weapon_GetIndexedTableValue(int tableIndex) {
    return *g_weaponIndexedValueTable[tableIndex];
}

s32 Weapon_IsPrimarySwitchGroup(s32 weaponType) {
    if (weaponType < 7) {
        if (weaponType >= 3) {
            return 1;
        }
    }
    return 0;
}

/** Return whether the encoded type belongs to this caller's accepted set. */
s32 Weapon_IsSecondarySwitchGroup(s32 weaponType) {
    {
        weaponType -= 2;
        if ((unsigned int)weaponType >= 14) {
            goto case_default;
        }
        switch (weaponType) {
        case 0: goto case_2;
        case 1: goto case_default;
        case 2: goto case_default;
        case 3: goto case_default;
        case 4: goto case_default;
        case 5: goto case_2;
        case 6: goto case_2;
        case 7: goto case_2;
        case 8: goto case_default;
        case 9: goto case_default;
        case 10: goto case_default;
        case 11: goto case_2;
        case 12: goto case_2;
        case 13: goto case_2;
        }
    }
case_2:
case_7:
case_8:
case_9:
case_13:
case_14:
case_15:
    return 1;
case_default:
    return 0;
}

s32 Weapon_IsSpecialSwitchGroup(s32 weaponType) {
    if (weaponType < 13) {
        if (weaponType >= 10) {
            return 1;
        }
    }
    return 0;
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)


s32 Weapon_CheckProfileFirePermission(WeaponPlayerPermissionView *pThis) {
    s32 result;
    Shared_Game *settings;
    if (pThis->shield > 0.0f) {
        return 0;
    }
    if (pThis->isBot != 0) {
        return 1;
    }
    settings = &g_playerViewRenderContext.game;
    if (settings->controllerMode != 1) {
        return 1;
    }
    result = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[pThis->character], pThis->weapon);
    if (result == 0) {
        SoundElement_PlayFlatSound(3405);
        if (pThis->hud != 0) {
            s32 player = Player_GetPlayerIndex(&g_playerViewRenderContext, pThis);
            Gsky_PostTargetedScreenMessage(&g_playerViewRenderContext.object, pThis->hud,

#if defined(VERSION_EU_X)
                            g_weaponLockedNoticeTextEuX[settings->language],
#else
                            g_weaponLockedNoticeTextEu[settings->language],
#endif
                            player, g_weaponPermissionNoticeDuration);
        }
    }
    return result;
}
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)

void Weapon_ApplySwitchAndRequestIdle(void *actor, void *fireState) {
    Weaponai_ApplyWeaponSwitch(actor, fireState);
    Actor_RequestActorState(actor, fireState, 0);
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/** Check whether a human player in mode 1 may select a weapon; when refused play the refusal sound and post a notice. */



int Weapon_CheckSinglePlayerFirePermission(WeaponPlayerPermissionView *player) {
    Shared_Game *game;
    int result;

    if (player->shield > 0.0f) {
        return 0;
    }
    if (player->isBot != 0) {
        return 1;
    }
    game = &g_playerViewRenderContext.game;
    if (game->controllerMode != 1) {
        return 1;
    }
    result = Player_GetProfileAchievementFlag((char *)&g_localPlayerProfiles[player->character], player->weapon);
    if (result == 0) {
        SoundElement_PlayFlatSound(3405);
        if (player->hud != 0) {
            Gsky_PostTargetedScreenMessage((char *)&g_playerViewRenderContext.object,
                player->hud, g_weaponLockedNoticeText,
                          Player_GetPlayerIndex((char *)&g_playerViewRenderContext, player), g_weaponPermissionNoticeDuration);
        }
    }
    return result;
}
#endif

/* 80231F5C_7.CPP */
extern void Playerai_StartSecondaryAttachedSound(Player *actor, s32 soundId);

void Weapon_InitializeChargeAndLoopSound(Player *actorView, WeaponFireState *fireState) {
    Player *weaponOwner;
    s16 idx;

    weaponOwner = actorView->actorParts[0].controller;
    idx = weaponOwner->selectedAction;
    fireState->charge = ((WeaponInfo *)g_weaponInfoByType[idx])->chargeRate * g_heldFireWeaponChargeRateScale;
    if ((weaponOwner->selectedAction == 5) && (weaponOwner->secondHandle == 0)) {
        Playerai_StartSecondaryAttachedSound(weaponOwner, 1130);
    }
}


void Weapon_DrawWeaponLookupModel(void *actorStorage, Dest *weaponState, Lookup *lookup) {
    void *actor;
    void *resource;
    s32 result;
    s32 one;
    s16 state;

    actor = ((LevelActor *)actorStorage)->controller;
    resource = ((Player *)actor)->camera;
    result = -1;
    if (resource == 0) {
        return;
    }
    if (g_gameSettings.local != 0) {
        if (Menu_CountLiveNodes((char *)&((GameplayCamera *)resource)->messageList) != 0) {
            return;
        }
    }
    state = ((Player *)actor)->selectedAction;
    one = 1;
    if ((state == one) && (weaponState->fireEnabled == 0)) {
        return;
    }
    if ((state >= 18) && (Playerai_GetWeaponAmmo(actor, state) <= 0)) {
        return;
    }
    state = ((Player *)actor)->selectedAction;
    if ((state == 14) || (state == one) || (state == 0)) {
        result = ((Player *)actor)->fireFrame;
    }
    Geometry_DrawModelResource(lookup->value,
                  ((LevelActor *)actorStorage)->animationMatrices, 1,
                  (char *)(char *)&((LevelActor *)actorStorage)->lighting[g_lightingBufferIndex], 0, result);
}


void Weapon_InitializeFireStateCallbacks(void *actor, void *fireState) {
    f32 initialCharge = g_weaponFireInitialValue;

    ((Dest *)fireState)->table = &g_weaponFireStateCallbackTable;
    ((Dest *)fireState)->enter = &Weapon_FireStateEnterCallbackEntry;
    ((Dest *)fireState)->draw = &Weapon_FireStateDrawCallbackEntry;
    ((Dest *)fireState)->definitionHealth = 0;
    ((Dest *)fireState)->charge = 0;
    ((Dest *)fireState)->reserved130 = 0;
    ((Dest *)fireState)->fireCounter = 0;
    ((Dest *)fireState)->fireMode = 1;
    ((Dest *)fireState)->initialCharge = initialCharge;
    ((LevelActor *)actor)->team = 0;
    ((Dest *)fireState)->reserved148 = 0;
    ((Dest *)fireState)->fireEnabled = 1;
    ((Dest *)fireState)->reserved14C = 0;
    ((Dest *)fireState)->reserved150 = 0;

#if defined(VERSION_EU) || defined(VERSION_EU_X)
Weapon_ApplySwitchAndRequestIdle
#else
Weaponai_InitializeSwitchAndRequestIdle
#endif
(actor, fireState);
}


s32 Weapon_PickRandomArmedWeapon(void *player) {
    s32 weapon;
    s32 remainingArmedSteps;

    weapon = ((Player *)player)->selectedAction;
    remainingArmedSteps = Graphu64_NextRandom() % 22;
    if (remainingArmedSteps >= 0) {
        do {
            weapon += 1;
            if (weapon >= 16) {
                weapon = 0;
            }
            if (Playerai_PlayerHasAmmoForWeapon(player, weapon) != 0) {
                remainingArmedSteps -= 1;
            }
        } while (remainingArmedSteps >= 0);
    }
    return weapon;
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
void Weapon_ApplySwitchAndSetSingleRound(void *part, WeaponSwitchActionView *body) {
    Weaponai_ApplyWeaponSwitch(part, body);
    body->singleRoundFlag = 1;
    body->singleRoundFlagSecondary = 1;
}
#endif


void Weapon_ResetControllerAndSpin(LevelActor *actor, WeaponFireState *fireState) {
    void *controller;

    controller = actor->controller;
    ((Player *)controller)->controllerMode = 1;
    ((Player *)controller)->controllerOwner = 0;
    ((Player *)controller)->controllerTimer = 0;
    fireState->spinStep = 0;
    fireState->spin = 0;
    if ((fireState->triggerMode != 0) && (Weaponai_TryRequestFiringState(actor, fireState) == 0)) {
        Actor_RequestActorState(actor, fireState, 2);
    }
}

s32 Weapon_IsTriggerReleasedOrBlocked(LevelActor *actor, void *unusedFireState, Player *actorView) {
    s32 wasActionReady;
    void *owner;

    {
        f32 field = actorView->cooldown;
        if (g_weaponTriggerStunThreshold < field) {
            return 1;
        }
    }
    if ((actor->flags & 0x300000) && (actorView->computer != 0)) {
        owner = actorView->controller;
        wasActionReady = ((LevelActor *)owner)->actionReady;
        ((LevelActor *)owner)->actionReady = 0;
        return wasActionReady == 0;
    }
    if (actorView->inputFlags & 0x2000) {
        if (actorView->locked != 0) {
            return 1;
        }
        return Player_HasAmmoForMode(actorView, actorView->selectedAction) == 0;
    }
    return 1;
}

void Weapon_ReleaseLinkedActorHandles(void *weaponActor) {
    Player_ReleaseObjectHandles((s32) ((LevelActor *) weaponActor)->controller);
}

void Weapon_InitializeChargeForWeaponEight(Player *actorView, WeaponFireState *fireState) {
    void *weaponOwner;
    s16 idx;

    weaponOwner = actorView->actorParts[0].controller;
    idx = ((Player *)weaponOwner)->selectedAction;
    fireState->charge = ((WeaponInfo *)g_weaponInfoByType[idx])->chargeRate * g_spinWeaponChargeRateScale;
    if ((((Player *)weaponOwner)->selectedAction == 8) && (((Player *)weaponOwner)->secondHandle == 0)) {
        Playerai_StartSecondaryAttachedSound(weaponOwner, 2620);
    }
}

void Weapon_UpdateTriggerReleaseState(void *actor, void *attack) {
    Player *state;

    state = ((Shared_Actor *)actor)->entity;
    if (((WeaponFireState *)attack)->triggerMode != 0) {
        if (Weaponai_TryRequestFiringState(actor, attack) != 0) {
            ((WeaponFireState *)attack)->triggerMode = 0;
            ((WeaponFireState *)attack)->queuedAction = -1;
        } else {
            switch (state->selectedAction) {
            case 8:
                SoundElement_PlaySoundAtPosition(2622, state->pos,
                              (intptr_t)&state->pos, -1);
            case 0:
            case 14:
                Playerai_StopSecondaryAttachedSound(state);
                Actor_RequestActorState(actor, attack, 2);
                break;
            default:
                Actor_RequestActorState(actor, attack, 2);
                break;
            }
        }
        state->controllerMode = 1;
        state->controllerTimer = 0;
    } else if ((state->selectedAction == 12) &&
               ((state->inputFlags & 0x4000) != 0)) {
        Player_ReleasePlayerParticleEmitters((s32)state);
    }
}


/* Applies the negated, scaled speed of the event's source (float, scaled by g_weaponSideYawSpeedScale) to an
   object through YawMatrixLocal when the event side matches the mode: side 2 in mode 1, side 0
   otherwise. */



void Weapon_ReleaseHandlesAndExitState39(void *weaponActor) {
    s32 weaponOwner;
    weaponOwner = (s32) ((LevelActor *) weaponActor)->controller;
    Player_ReleaseObjectHandles(weaponOwner);
    if ((((struct PlayerWeaponStateView *) weaponOwner)->action) == 39) {
        Player_SetPlayerState((void *) weaponOwner, (void *) weaponOwner, 2);
    }
}

void Weapon_PlayStartupCue9E2(void *weaponActor) {
    void *weaponOwner;
    weaponOwner = (((struct LevelActor *) ((s8 *) weaponActor))->controller);
    if ((((struct PlayerStartupSoundView *) ((s8 *) weaponOwner))->startupSoundNode) == 0) {
        Playerai_StartSecondaryAttachedSound(weaponOwner, 2530);
    }
}

void Weapon_AdvanceSpinAndTriggerMode(struct WeaponActorStateView *actor, void *attack) {
    f32 spinStep;
    f32 feedbackSpinStep;
    void *value;
    void *controller;

    value = actor->value;
    ((struct WeaponChargeAccumulatorView *)(attack))->value += (((struct WeaponOriginScalarView *)(attack))->value * g_frameElapsedTime) * 2.0f;
    spinStep = ((struct WeaponOriginScalarView *)(attack))->value;
    controller = ((struct PlayerHeldWeaponView *)(value))->value;
    if (!(spinStep < 0.0f
              ? g_weaponSpinNegativeFeedbackLimit < (-spinStep * *(&g_spinWeaponChargeRateScale + 1))
              : g_weaponSpinFeedbackConstants[0] < (spinStep * g_weaponSpinPositiveFeedbackScale))) {
        feedbackSpinStep = ((struct WeaponOriginScalarView *)(attack))->value;
        if (feedbackSpinStep < 0.0f) {
            ((struct WeaponSpinRateView *)(controller))->value = (f32) (-feedbackSpinStep * g_weaponSpinFeedbackConstants[1]);
        } else {
            ((struct WeaponSpinRateView *)(controller))->value = (f32) (feedbackSpinStep * g_weaponSpinPositiveOutputScale);
        }
    } else {
        ((struct WeaponSpinRateView *)(controller))->value = (f32) g_weaponSpinClampedFeedback;
    }

    if (((struct WeaponFireLatchView *)(attack))->value != 0) {
        ((struct WeaponAttackPhaseView *)(attack))->value = 2;
        if (Weaponai_TryRequestFiringState(actor, attack) != 0) {
            ((struct WeaponAttackPhaseView *)(attack))->value = 1;
            Playerai_StopSecondaryAttachedSound(value);
        }
    }
}

void Weapon_ApplyScaledSideYaw(void *obj, Event *event) {
    float v = event->source->speed * g_weaponSideYawSpeedScale;

    if (g_playerWeaponClassMode == 1) {
        if (event->side == 2) {
            YawMatrixLocal(obj, -v);
        }
    } else if (event->side == 0) {
        YawMatrixLocal(obj, -v);
    }
}

void Weapon_UpdateNormalFireAction(void *actor, WeaponNormalFireActionView *attack) {
    char *weaponActorView = (char *) actor;
    void *weaponOwner;
    s16 idx;
    s32 action;

    weaponOwner = (void *)((Player *)actor)->actorParts[0].controller;
    idx = ((Player *)weaponOwner)->pose;
    action = g_weaponActionRecords[idx].action;

    if (Player_HasAmmoForMode(weaponOwner, ((Player *)weaponOwner)->selectedAction) == 0) {
        ((Player *)weaponOwner)->weapon = Weaponai_FindNextUsableWeapon(weaponOwner);
    } else {
        attack->fireRequestFlag = 1;
        if (Weaponai_TryRequestFiringState(actor, attack) == 0 && !(((Player *)actor)->weaponFlags & 0x400)) {
            Actor_RequestActorState(actor, attack, action);
        }
    }
}

void Weapon_InitializeChargeAndStartupCues(Player *actorView, WeaponFireState *fireState) {
    Player *cueOwner;
    Player *weaponOwner;
    s16 index;

    cueOwner = actorView->actorParts[0].controller;
    fireState->cueTimer = 0;
    if ((cueOwner->computer == 0) &&
        (g_playerWeaponClassMode == 1)) {
        Playerai_DispatchWeaponFireEffect(actorView->actorParts[0].controller, 1017);
    } else {
        Playerai_DispatchWeaponFireEffect(actorView->actorParts[0].controller, 1227);
    }
    Playerai_StartPrimaryAttachedSound(cueOwner, 1930);
    Playerai_StartSecondaryAttachedSound(cueOwner, 1920);

    weaponOwner = actorView->actorParts[0].controller;
    index = weaponOwner->selectedAction;
    fireState->charge =
        ((WeaponInfo *)g_weaponInfoByType[index])->chargeRate *
        g_weaponStartupChargeRateScale;
    if ((weaponOwner->selectedAction == 8) &&
        (weaponOwner->secondHandle == 0)) {
        Playerai_StartSecondaryAttachedSound(weaponOwner, 2620);
    }
}

void Weapon_ApplySideDependentYaw(void *object, Event *event) {
    f32 speed;
    s32 mode;

    speed = event->source->speed;
    mode = g_playerWeaponClassMode;
    if (mode == 1) {
        switch (event->side) {
        case 1:
            YawMatrixLocal(object, -speed);
            break;
        case 2:
            YawMatrixLocal(object, speed * 2.0f);
            break;
        }
    } else if (event->side == 0) {
        YawMatrixLocal(object, -speed * 2.0f);
    }
}


void Weapon_EnterChargeStateWithCues(Player *actor, WeaponFireState *fireState) {
    void *player;
    void *weaponOwner;
    s16 index;

    player = actor->actorParts[0].controller;
    if (fireState->mode == 2) {
        Player_SetPlayerState(player, player, 2);
    } else {
        fireState->cueTimer = g_weaponChargeEntryCueAndRate[0];
        if ((((Player *)player)->computer == 0) &&
            (g_playerWeaponClassMode == 1)) {
            Playerai_DispatchWeaponFireEffect(actor->actorParts[0].controller, 1019);
        } else {
            Playerai_DispatchWeaponFireEffect(actor->actorParts[0].controller, 1229);
        }
        Actor_RequestActorState(actor, fireState, 4);
        Playerai_StartPrimaryAttachedSound(player, 2423);
        Playerai_StartSecondaryAttachedSound(player, 2420);

        weaponOwner = actor->actorParts[0].controller;
        index = ((Player *)weaponOwner)->selectedAction;
        fireState->charge =
            ((WeaponInfo *)g_weaponInfoByType[index])->chargeRate *
            g_weaponChargeEntryCueAndRate[1];
        if ((((Player *)weaponOwner)->selectedAction == 8) &&
            (((Player *)weaponOwner)->secondHandle == 0)) {
            Playerai_StartSecondaryAttachedSound(weaponOwner, 2620);
        }
    }
}

void Weapon_EmptyChargeStateHook(void) {
}

void Weapon_SetDelayAndRequestAlternateFireState(void *actor, struct Shared_Particle *particle) {
    particle->lifetime = g_weaponDelayStateLifetime;
    Actor_RequestActorState(actor, particle, 8);
}

/** Perform the no-op callback. */
void Weapon_EmptyAlternateFireHook(void) {
}

void Weapon_UpdateHeldAlternateFire(void *weaponActor, void *attack) {
    void *actor;

    actor = ((LevelActor *)weaponActor)->controller;
    ((WeaponFireState *)attack)->mode = 2;
    if (Player_HasAmmoForMode(actor, ((Player *)actor)->selectedAction) == 0) {
        ((Player *)actor)->weapon = Weaponai_FindNextUsableWeapon(actor);
        return;
    }

    if (((LevelActor *)weaponActor)->animationTime >= g_weaponAlternateFireAnimationThreshold) {
        if (Playerai_IsAlternateFireHeld(actor) == 0) {
            Playerai_BeginHeldAlternateFire(actor);
        }
    }

    if (!((((Player *)actor)->inputFlags & 0x4000) &&
          (((Player *)actor)->health != 0))) {
        Actor_RequestActorState(weaponActor, attack, 2);
        Playerai_EndHeldAlternateFire(actor);
        ((WeaponFireState *)attack)->mode = 1;
    }

    if (Weaponai_TryRequestFiringState(weaponActor, attack) != 0) {
        Playerai_EndHeldAlternateFire(actor);
    }
}

void Weapon_UpdateSpecialFireAndAmmo(void *weaponActor, void *attack) {
    void *actor;
    s16 idx;
    s32 value;

    actor = ((ActorAnimationResourceView *)weaponActor)->owner;
    idx = ((WeaponSpecialFirePlayerView *)(actor))->weaponActionIndex;
    value = g_weaponActionRecords[idx].action;

    if (((WeaponSpecialFirePlayerView *)(actor))->delay <= 0.0f) {
        if ((((struct Ctrl *) ((WeaponSpecialFirePlayerView *) actor)->controller)->flag == 0 ||
             g_gameSettings.counters.m_bFragTagOn == 0) &&
            (((WeaponSpecialFirePlayerView *)(actor))->actionFlags & 0x4000)) {
            Player_ReleasePlayerParticleEmitters(actor);
        }
    }

    if (Player_HasAmmoForMode(actor, ((WeaponSpecialFirePlayerView *)(actor))->ammoMode) == 0) {
        if (Particle_CountOwnerListOneEffects(&g_actorParticleEffectSystem[0], actor) == 0) {
            ((WeaponSpecialFirePlayerView *)(actor))->nextUsableWeapon = Weaponai_FindNextUsableWeapon(actor);
        }
    } else if (Weaponai_TryRequestFiringState(weaponActor, attack) == 0 &&
               !(((ActorAnimationResourceView *)weaponActor)->flags & 0x400)) {
        Actor_RequestActorState(weaponActor, attack, value);
    }
}

void Weapon_RequestReleaseOnEnabledEvent(void *actor, struct WeaponEventSource *eventSource) {
    if (eventSource->eventEnabled != 0) {
        Actor_RequestActorState(actor, eventSource, 2);
    }
}

void Weapon_PlayStartupCue80C(void *weaponActor) {
    void *weaponOwner;
    weaponOwner = (((struct LevelActor *) ((s8 *) weaponActor))->controller);
    if ((((struct PlayerStartupSoundView *) ((s8 *) weaponOwner))->startupSoundNode) == 0) {
        Playerai_StartSecondaryAttachedSound(weaponOwner, 2060);
    }
}

void Weapon_UpdateAlternateTriggerCompletion(LevelActor *actor, WeaponFireState *fireState) {
    void *controller;

    controller = actor->controller;
    if (fireState->triggerMode != 0) {
        fireState->mode = 2;
        if (Weaponai_TryRequestFiringState(actor, fireState) != 0) {
            fireState->mode = 1;
            Playerai_StopSecondaryAttachedSound(controller);
        }
    }
}

void Weapon_EaseSpinAndUpdateFeedback(struct WeaponActorStateView *actor, void *fireState) {
    f32 spinStep;
    f32 feedbackSpinStep;
    void *value;
    void *controller;

    value = actor->value;
    if (((struct WeaponModeByteView *)(fireState))->value == 5) {
        Graphu64_EaseValueToward(&((WeaponFireState *)fireState)->spin, (f32) g_weaponEasedSpinSpinTarget * g_weaponEasedSpinSpinTargetScale, 0.4f);
    } else {
        Graphu64_EaseValueToward(&((WeaponFireState *)fireState)->spin, 0.0f, 0.4f);
    }
    spinStep = ((struct WeaponOriginScalarView *)(fireState))->value;
    controller = ((struct PlayerHeldWeaponView *)(value))->value;
    if (!(spinStep < 0.0f
              ? g_weaponEasedSpinNegativeFeedbackLimit < (-spinStep * g_weaponEasedSpinNegativeFeedbackScale)
              : g_weaponEasedSpinFeedbackConstants[0] < (spinStep * g_weaponEasedSpinPositiveFeedbackScale))) {
        feedbackSpinStep = ((struct WeaponOriginScalarView *)(fireState))->value;
        if (feedbackSpinStep < 0.0f) {
            ((struct WeaponSpinRateView *)(controller))->value = (f32) (-feedbackSpinStep * g_weaponEasedSpinFeedbackConstants[1]);
            return;
        }
        ((struct WeaponSpinRateView *)(controller))->value = (f32) (feedbackSpinStep * g_weaponEasedSpinPositiveOutputScale);
        return;
    }
    ((struct WeaponSpinRateView *)(controller))->value = (f32) g_weaponEasedSpinClampedFeedback;
}

void Weapon_ApproachSpinPhaseAndRelease(void *actor, struct WeaponFireState *fireState) {
    f32 nextSpinStep;
    f32 target;

    target = g_weaponReleaseSpinTarget;
    nextSpinStep = Graphu64_ApproachValue(fireState->spinStep, target, g_weaponReleaseSpinApproachRate);
    fireState->spinStep = nextSpinStep;
    if (target <= nextSpinStep) {
        Actor_RequestActorState(actor, fireState, 2);
    }
}

void Weapon_TranslateEventSixByPitch(void *matrix, void *eventStorage) {
    ActorEffectEventView *event = eventStorage;
    if (event->eventIndex == 6) {
        LevelActor *actor = event->actor;
        TranslateMatrixLocal(matrix, 0.0f, actor->pitch, 0.0f);
    }
}

#if !(defined(VERSION_US_REV1))
const float g_weaponPermissionNoticeDuration_StorageWords[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_Weapon_CheckSinglePlayerFirePermissionConstantWords[1] = {
    1.0f,
};
#endif

#if !(defined(VERSION_US_REV1))
const float g_heldFireWeaponChargeRateScale_StorageWords[1] = {
    15.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_heldFireWeaponChargeRateScaleWords[1] = {
    15.0f,
};
#endif

#if !(defined(VERSION_US_REV1))
const float g_weaponFireInitialValue_StorageWords[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_Weapon_InitializeFireStateCallbacksConstantWords[1] = {
    1.0f,
};
#endif

const float g_weaponTriggerStunThreshold_StorageWords[1] = {
    0.1f,
};

#if !(defined(VERSION_US_REV1))
const float g_spinWeaponChargeRateScale_StorageWords[1] = {
    15.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_WeaponData[1] = {
    15.0f,
};
#endif

const float g_spinWeaponSpinFeedbackScales[7] = {
    1.7904929f, 1.0f, 1.7904929f, 1.0f,
    1.7904929f, 1.7904929f, 1.0f,
};

const float g_weaponSideYawSpeedScale_StorageWords[1] = {
    1.5f,
};

#if !(defined(VERSION_US_REV1))
const float g_weaponStartupChargeRateScale_StorageWords[1] = {
    15.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_Weapon_InitializeChargeAndStartupCuesConstantWords[1] = {
    15.0f,
};
#endif

const float g_weaponChargeEntryCueAndRate_StorageWords[2] = {
    2.5f, 15.0f,
};

const float g_weaponDelayStateLifetime_StorageWords[1] = {
    3e+02f,
};

const float g_weaponAlternateFireAnimationThreshold_StorageWords[1] = {
    4.0f,
};

const float g_weaponEasedSpinSpinTargetScale_StorageWords[8] = {
    0.017453294f, 1.7904929f, 1.0f, 1.7904929f,
    1.0f, 1.7904929f, 1.7904929f, 1.0f,
};

const float g_weaponReleaseSpinTarget_StorageWords[1] = {
    6e+02f,
};

#if defined(VERSION_US)
extern unsigned int k_weaponPackedHalfwords[1];
#endif

#if defined(VERSION_EU)
extern unsigned int k_weaponRegisterMoveInstruction[1];
#endif

#if defined(VERSION_DE)
unsigned int k_weaponScaleFloat[1] = {
    0x40C00000,
};
#endif

#if defined(VERSION_EU)
#if defined(VERSION_EU)
extern struct {
    f32 targetFacingEaseRate;
    f32 reactionReserveApproachRate;
    f32 aimRates[3];
    s16 weaponAnimationDurationPairs[30];
    s32 handMirrorAxesAndFlags[5];
    f32 weaponRestOffset;
    void * nextTable;
    u32 stateTableHeaderReserved[7];
    s32 state0Id;
    RomCallbackWord state0Enter;
    RomCallbackWord state0Update;
    u32 state0Reserved;
    s32 state0Animation;
    f32 state0Rate;
    s32 state0Threshold;
    u32 state0Flags;
    s32 state1Id;
    RomCallbackWord state1Enter;
    RomCallbackWord state1Update;
    u32 state1Reserved;
    s32 state1Animation;
    f32 state1Rate;
    s32 state1Threshold;
    u32 state1Flags;
    s32 state2Id;
    RomCallbackWord state2Enter;
    RomCallbackWord state2Update;
    u32 state2Reserved;
    s32 state2Animation;
    f32 state2Rate;
    s32 state2Threshold;
    u32 state2Flags;
    s32 state3Id;
    RomCallbackWord state3Enter;
    RomCallbackWord state3Update;
    u32 state3Reserved;
    s32 state3Animation;
    f32 state3Rate;
    s32 state3Threshold;
    u32 state3Flags;
    s32 state4Id;
    RomCallbackWord state4Enter;
    RomCallbackWord state4Update;
    u32 state4Reserved;
    void * state4AnimationList;
    f32 state4Rate;
    s32 state4Threshold;
    u32 state4Flags;
    s32 state5Id;
    RomCallbackWord state5Enter;
    RomCallbackWord state5Update;
    u32 state5Reserved;
    void * state5AnimationList;
    f32 state5Rate;
    s32 state5Threshold;
    u32 state5Flags;
    s32 state6Id;
    RomCallbackWord state6Enter;
    RomCallbackWord state6Update;
    u32 state6Reserved;
    s32 state6Animation;
    f32 state6Rate;
    s32 state6Threshold;
    u32 state6Flags;
    s32 state7Id;
    RomCallbackWord state7Enter;
    RomCallbackWord state7Update;
    u32 state7Reserved;
    s32 state7Animation;
    f32 state7Rate;
    s32 state7Threshold;
    u32 state7Flags;
    void * table8Next;
    u32 table8HeaderReserved[7];
    s32 state9Id;
    RomCallbackWord state9Enter;
    RomCallbackWord state9Update;
    u32 state9Reserved;
    s32 state9Animation;
    f32 state9Rate;
    s32 state9Threshold;
    u32 state9Flags;
    s32 state10Id;
    RomCallbackWord state10Enter;
    RomCallbackWord state10Update;
    u32 state10Reserved;
    s32 state10Animation;
    f32 state10Rate;
    s32 state10Threshold;
    u32 state10Flags;
    s32 state11Id;
    RomCallbackWord state11Enter;
    RomCallbackWord state11Update;
    u32 state11Reserved;
    s32 state11Animation;
    f32 state11Rate;
    s32 state11Threshold;
    u32 state11Flags;
    s32 state12Id;
    RomCallbackWord state12Enter;
    RomCallbackWord state12Update;
    u32 state12Reserved;
    s32 state12Animation;
    f32 state12Rate;
    s32 state12Threshold;
    u32 state12Flags;
    void * table13Next;
    u32 table13HeaderReserved[7];
    s32 state14Id;
    RomCallbackWord state14Enter;
    RomCallbackWord state14Update;
    u32 state14Reserved;
    s32 state14Animation;
    f32 state14Rate;
    s32 state14Threshold;
    u32 state14Flags;
    s32 state15Id;
    RomCallbackWord state15Enter;
    RomCallbackWord state15Update;
    u32 state15Reserved;
    s32 state15Animation;
    f32 state15Rate;
    s32 state15Threshold;
    u32 state15Flags;
    s32 state16Id;
    RomCallbackWord state16Enter;
    RomCallbackWord state16Update;
    u32 state16Reserved;
    s32 state16Animation;
    f32 state16Rate;
    s32 state16Threshold;
    u32 state16Flags;
    s32 state17Id;
    RomCallbackWord state17Enter;
    RomCallbackWord state17Update;
    u32 state17Reserved;
    s32 state17Animation;
    f32 state17Rate;
    s32 state17Threshold;
    u32 state17Flags;
    s32 state18Id;
    RomCallbackWord state18Enter;
    RomCallbackWord state18Update;
    u32 state18Reserved;
    s32 state18Animation;
    f32 state18Rate;
    s32 state18Threshold;
    u32 state18Flags;
} k_PlayeraiInitializeplayerhealthData __attribute__((aligned(4)));
typedef char k_PlayeraiInitializeplayerhealthDataSizeCheck[(sizeof(k_PlayeraiInitializeplayerhealthData) == 744) ? 1 : -1];
#endif
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
extern struct {
    f32 targetFacingEaseRate;
    f32 reactionReserveApproachRate;
    f32 aimRates[3];
    s16 weaponAnimationDurationPairs[30];
    s32 handMirrorAxesAndFlags[5];
    f32 weaponRestOffset;
    void * nextTable;
    u32 stateTableHeaderReserved[7];
    s32 state0Id;
    RomCallbackWord state0Enter;
    RomCallbackWord state0Update;
    u32 state0Reserved;
    s32 state0Animation;
    f32 state0Rate;
    s32 state0Threshold;
    u32 state0Flags;
    s32 state1Id;
    RomCallbackWord state1Enter;
    RomCallbackWord state1Update;
    u32 state1Reserved;
    s32 state1Animation;
    f32 state1Rate;
    s32 state1Threshold;
    u32 state1Flags;
    s32 state2Id;
    RomCallbackWord state2Enter;
    RomCallbackWord state2Update;
    u32 state2Reserved;
    s32 state2Animation;
    f32 state2Rate;
    s32 state2Threshold;
    u32 state2Flags;
    s32 state3Id;
    RomCallbackWord state3Enter;
    RomCallbackWord state3Update;
    u32 state3Reserved;
    s32 state3Animation;
    f32 state3Rate;
    s32 state3Threshold;
    u32 state3Flags;
    s32 state4Id;
    RomCallbackWord state4Enter;
    RomCallbackWord state4Update;
    u32 state4Reserved;
    void * state4AnimationList;
    f32 state4Rate;
    s32 state4Threshold;
    u32 state4Flags;
    s32 state5Id;
    RomCallbackWord state5Enter;
    RomCallbackWord state5Update;
    u32 state5Reserved;
    void * state5AnimationList;
    f32 state5Rate;
    s32 state5Threshold;
    u32 state5Flags;
    s32 state6Id;
    RomCallbackWord state6Enter;
    RomCallbackWord state6Update;
    u32 state6Reserved;
    s32 state6Animation;
    f32 state6Rate;
    s32 state6Threshold;
    u32 state6Flags;
    s32 state7Id;
    RomCallbackWord state7Enter;
    RomCallbackWord state7Update;
    u32 state7Reserved;
    s32 state7Animation;
    f32 state7Rate;
    s32 state7Threshold;
    u32 state7Flags;
    void * table8Next;
    u32 table8HeaderReserved[7];
    s32 state9Id;
    RomCallbackWord state9Enter;
    RomCallbackWord state9Update;
    u32 state9Reserved;
    s32 state9Animation;
    f32 state9Rate;
    s32 state9Threshold;
    u32 state9Flags;
    s32 state10Id;
    RomCallbackWord state10Enter;
    RomCallbackWord state10Update;
    u32 state10Reserved;
    s32 state10Animation;
    f32 state10Rate;
    s32 state10Threshold;
    u32 state10Flags;
    s32 state11Id;
    RomCallbackWord state11Enter;
    RomCallbackWord state11Update;
    u32 state11Reserved;
    s32 state11Animation;
    f32 state11Rate;
    s32 state11Threshold;
    u32 state11Flags;
    s32 state12Id;
    RomCallbackWord state12Enter;
    RomCallbackWord state12Update;
    u32 state12Reserved;
    s32 state12Animation;
    f32 state12Rate;
    s32 state12Threshold;
    u32 state12Flags;
    void * table13Next;
    u32 table13HeaderReserved[7];
    s32 state14Id;
    RomCallbackWord state14Enter;
    RomCallbackWord state14Update;
    u32 state14Reserved;
    s32 state14Animation;
    f32 state14Rate;
    s32 state14Threshold;
    u32 state14Flags;
    s32 state15Id;
    RomCallbackWord state15Enter;
    RomCallbackWord state15Update;
    u32 state15Reserved;
    s32 state15Animation;
    f32 state15Rate;
    s32 state15Threshold;
    u32 state15Flags;
    s32 state16Id;
    RomCallbackWord state16Enter;
    RomCallbackWord state16Update;
    u32 state16Reserved;
    s32 state16Animation;
    f32 state16Rate;
    s32 state16Threshold;
    u32 state16Flags;
    s32 state17Id;
    RomCallbackWord state17Enter;
    RomCallbackWord state17Update;
    u32 state17Reserved;
    s32 state17Animation;
    f32 state17Rate;
    s32 state17Threshold;
    u32 state17Flags;
    s32 state18Id;
    RomCallbackWord state18Enter;
    RomCallbackWord state18Update;
    u32 state18Reserved;
    s32 state18Animation;
    f32 state18Rate;
    s32 state18Threshold;
    u32 state18Flags;
} g_weaponSwitchStateWordsUs __attribute__((aligned(4)));
typedef char g_weaponSwitchStateWordsUsSizeCheck[(sizeof(g_weaponSwitchStateWordsUs) == 744) ? 1 : -1];
#endif
#endif
