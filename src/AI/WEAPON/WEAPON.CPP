#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "include_asm.h"
#include "WEAPONS/PLAYERRECAT1450V1.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "COMMON/PLAYERPROFILES.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "COMMON/MODEL_RENDER.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/SELF.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "RENDER/PLAYERAI_TOGGLEFORCEMARKER.H"
#include "WEAPONS/CHARGE_AND_LINKED_ACTOR_HANDLES.H"
#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "WEAPONS/MEASUREDRECAT1D8V2.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "WEAPONS/STARTUP_CUES_AND_SIDE_YAW.H"
#include "COMMON/OBJB.H"
#include "WEAPONS/MEASUREDRECAT1D8V3.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/OBJ.H"
#include "COMMON/STATERECAT10.H"
#include "COMMON/ACTORRESOURCEHEADER.H"
#include "COMMON/MTX.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "WEAPONS/PITCH_TRANSLATION_AND_SPIN_ACTIONS.H"

extern void Player_ReleaseObjectHandles(void *);
extern struct WeaponGlobalRuntimeView g_playerWeaponClassMode;

/* 80231F5C_5.CPP */
void Weapon_SpawnTargetPlayerFireEffect(void *aiTarget, s32 unused1, s32 effect) {
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
#include "COMMON/SHARED_WORLDFUNC.H"
extern u8 *g_weaponLockedNoticeTextEu[];
extern u8 *g_weaponLockedNoticeTextEuX[];
extern s32 Player_GetProfileAchievementFlag(Profile *, s32);
extern s32 Player_GetPlayerIndex(Shared_MenuData *, WeaponPlayerPermissionView *);
extern void Gsky_PostTargetedScreenMessage(Shared_MenuObject *, void *, char *, s32, f32);

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

/* 80231F5C_6.CPP */
#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/** Check whether a human player in mode 1 may select a weapon; when refused play the refusal sound and post a notice. */

extern int g_weaponLockedNoticeText;
extern int Player_GetProfileAchievementFlag(char *, int);
extern int Player_GetPlayerIndex(void *, WeaponPlayerPermissionView *);
extern void Gsky_PostTargetedScreenMessage(void *, void *, int, int, float);

int Weapon_CheckSinglePlayerFirePermission(WeaponPlayerPermissionView *player) {
    SettingsE *rules;
    int result;

    if (player->shield > 0.0f) {
        return 0;
    }
    if (player->isBot != 0) {
        return 1;
    }
    rules = &g_gameSettings;
    if (rules->players != 1) {
        return 1;
    }
    result = Player_GetProfileAchievementFlag((char *)&g_localPlayerProfiles[player->character], player->weapon);
    if (result == 0) {
        SoundElement_PlayFlatSound(3405);
        if (player->hud != 0) {
            Gsky_PostTargetedScreenMessage((char *)rules - (((char *)&((Shared_MenuData *)0)->game - (char *)0) - ((char *)&((Shared_MenuData *)0)->object - (char *)0)), player->hud, g_weaponLockedNoticeText,
                          Player_GetPlayerIndex((char *)rules - ((char *)&((Shared_MenuData *)0)->game - (char *)0), player), g_weaponPermissionNoticeDuration);
        }
    }
    return result;
}
#endif

/* 80231F5C_7.CPP */
extern void Playerai_StartSecondaryAttachedSound(Shared_ActorView *actor, s32 soundId);

void Weapon_InitializeChargeForWeaponFive(Shared_ActorView *actorView, WeaponFireState *fireState) {
    Shared_ActorView *weaponOwner;
    s16 idx;

    weaponOwner = actorView->self;
    idx = weaponOwner->selectedAction;
    fireState->charge = ((WeaponInfo *)g_weaponInfoByType[idx])->chargeRate * g_weaponFiveChargeRateScale;
    if ((weaponOwner->selectedAction == 5) && (weaponOwner->weaponLoopSoundHandle == 0)) {
        Playerai_StartSecondaryAttachedSound(weaponOwner, 1130);
    }
}

/* 80231F5C_8.CPP */
extern int Menu_CountLiveNodes(struct CMenu_t **head);
extern s32 Playerai_GetWeaponAmmo(void *actor, s16 weaponId);

void Weapon_DrawWeaponLookupModel(void *actorStorage, Dest *weaponState, Lookup *lookup) {
    void *actor;
    void *resource;
    s32 result;
    s32 one;
    s16 state;

    actor = ((LevelActor *)actorStorage)->controller;
    resource = ((Shared_ActorView *)actor)->message;
    result = -1;
    if (resource == 0) {
        return;
    }
    if (g_gameSettings.local != 0) {
        if (Menu_CountLiveNodes((char *)&((GameplayCamera *)resource)->messageList) != 0) {
            return;
        }
    }
    state = ((Shared_ActorView *)actor)->selectedAction;
    one = 1;
    if ((state == one) && (weaponState->fireEnabled == 0)) {
        return;
    }
    if ((state >= 18) && (Playerai_GetWeaponAmmo(actor, state) <= 0)) {
        return;
    }
    state = ((Shared_ActorView *)actor)->selectedAction;
    if ((state == 14) || (state == one) || (state == 0)) {
        result = ((Shared_ActorView *)actor)->unk_0x11F8;
    }
    Geometry_DrawModelResource(lookup->value,
                  ((LevelActor *)actorStorage)->animationMatrices, 1,
                  (char *)(char *)&((LevelActor *)actorStorage)->lighting[g_lightingBufferIndex], 0, result);
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern void Weapon_ApplySwitchAndRequestIdle(void *actor, void *fireState);
#else
#endif

void Weapon_InitializeFireStateCallbacks(void *actor, void *fireState) {
    f32 k = g_weaponFireInitialValue;

    ((Dest *)fireState)->table = &g_weaponFireStateCallbackTable;
    ((Dest *)fireState)->enter = &Weapon_FireStateEnterCallbackEntry;
    ((Dest *)fireState)->draw = &Weapon_FireStateDrawCallbackEntry;
    ((Dest *)fireState)->definitionHealth = 0;
    ((Dest *)fireState)->charge = 0;
    ((Dest *)fireState)->reserved130 = 0;
    ((Dest *)fireState)->fireCounter = 0;
    ((Dest *)fireState)->fireMode = 1;
    ((Dest *)fireState)->initialCharge = k;
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

extern s32 Playerai_PlayerHasAmmoForWeapon(void *player, s32 requestedWeaponType);

s32 Weapon_PickRandomArmedWeapon(void *player) {
    s32 weapon;
    s32 remainingArmedSteps;

    weapon = ((Shared_ActorView *)player)->selectedAction;
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

/* 80231F5C_9.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
void Weapon_ApplySwitchAndSetSingleRound(void *part, WeaponSwitchActionView *body) {
    Weaponai_ApplyWeaponSwitch(part, body);
    body->singleRoundFlag = 1;
    body->singleRoundFlagSecondary = 1;
}
#endif

/* 80231F5C_10.CPP */
extern s32 Weaponai_TryRequestFiringState(void *, void *);

void Weapon_ResetControllerAndSpin(LevelActor *actor, WeaponFireState *fireState) {
    void *controller;

    controller = actor->controller;
    ((Shared_ActorView *)controller)->controllerMode = 1;
    ((Shared_ActorView *)controller)->controllerOwner = 0;
    ((Player *)controller)->controllerTimer = 0;
    fireState->spinStep = 0;
    fireState->spin = 0;
    if ((fireState->triggerMode != 0) && (Weaponai_TryRequestFiringState(actor, fireState) == 0)) {
        Actor_RequestActorState(actor, fireState, 2);
    }
}

s32 Weapon_IsTriggerReleasedOrBlocked(LevelActor *actor, void *unusedFireState, Shared_ActorView *actorView) {
    s32 wasActionReady;
    void *owner;

    {
        f32 field = actorView->stun;
        if (g_weaponTriggerStunThreshold < field) {
            return 1;
        }
    }
    if ((actor->flags & 0x300000) && (actorView->remote != 0)) {
        owner = actorView->owner;
        wasActionReady = ((LevelActor *)owner)->actionReady;
        ((LevelActor *)owner)->actionReady = 0;
        return wasActionReady == 0;
    }
    if (actorView->actionFlags & 0x2000) {
        if (actorView->actionState != 0) {
            return 1;
        }
        return Player_HasAmmoForMode(actorView, actorView->selectedAction) == 0;
    }
    return 1;
}

void Weapon_ReleaseLinkedActorHandles(void *weaponActor) {
    Player_ReleaseObjectHandles((((struct ActorLinkedControllerView *) ((s8 *) weaponActor))->link));
}

void Weapon_InitializeChargeForWeaponEight(Shared_ActorView *actorView, WeaponFireState *fireState) {
    void *weaponOwner;
    s16 idx;

    weaponOwner = actorView->self;
    idx = ((Shared_ActorView *)weaponOwner)->selectedAction;
    fireState->charge = ((WeaponInfo *)g_weaponInfoByType[idx])->chargeRate * g_weaponEightChargeRateScale;
    if ((((Shared_ActorView *)weaponOwner)->selectedAction == 8) && (((Shared_ActorView *)weaponOwner)->weaponLoopSoundHandle == 0)) {
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
                              (s32)&state->pos, -1);
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

/* 80231F5C_11.CPP */

/* Applies the negated, scaled speed of the event's source (float at 0x294, scaled by g_weaponSideYawSpeedScale) to an
   object through YawMatrixLocal when the event side at 0x4 matches the mode: side 2 in mode 1, side 0
   otherwise. */

extern s16 Weaponai_FindNextUsableWeapon(void *player);

extern WeaponActionRecord g_weaponActionRecords[];

void Weapon_ReleaseHandlesAndExitState39(void *weaponActor) {
    s32 weaponOwner;
    weaponOwner = (((struct ActorLinkedControllerView *) ((s8 *) weaponActor))->link);
    Player_ReleaseObjectHandles(weaponOwner);
    if ((((struct PlayerWeaponStateView *) ((s8 *) weaponOwner))->action) == 39) {
        Player_SetPlayerState((void *) weaponOwner, (void *) weaponOwner, 2);
    }
}

void Weapon_PlayStartupCue9E2(void *weaponActor) {
    void *weaponOwner;
    weaponOwner = (((struct ActorPlayerControllerView *) ((s8 *) weaponActor))->player);
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
              ? g_weaponSpinNegativeFeedbackLimit < (-spinStep * *(&g_weaponEightChargeRateScale + 1))
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

    if (g_playerWeaponClassMode.classMode == 1) {
        if (event->side == 2) {
            YawMatrixLocal(obj, -v);
        }
    } else if (event->side == 0) {
        YawMatrixLocal(obj, -v);
    }
}

void Weapon_UpdateNormalFireAction(void *actor, WeaponNormalFireActionView *attack) {
    char *o = (char *) actor;
    void *weaponOwner;
    s16 idx;
    s32 action;

    weaponOwner = (void *)((Shared_ActorView *)o)->self;
    idx = ((Shared_ActorView *)weaponOwner)->action;
    action = g_weaponActionRecords[idx].action;

    if (Player_HasAmmoForMode(weaponOwner, ((Shared_ActorView *)weaponOwner)->selectedAction) == 0) {
        ((Shared_ActorView *)weaponOwner)->nextWeapon = Weaponai_FindNextUsableWeapon(weaponOwner);
    } else {
        attack->fireRequestFlag = 1;
        if (Weaponai_TryRequestFiringState(actor, attack) == 0 && !(((Shared_ActorView *)o)->flags & 0x400)) {
            Actor_RequestActorState(actor, attack, action);
        }
    }
}

void Weapon_InitializeChargeAndStartupCues(Shared_ActorView *actorView, WeaponFireState *fireState) {
    Shared_ActorView *cueOwner;
    Shared_ActorView *weaponOwner;
    s16 index;

    cueOwner = actorView->self;
    fireState->cueTimer = 0;
    if ((cueOwner->remote == 0) &&
        (g_playerWeaponClassMode.classMode == 1)) {
        Playerai_DispatchWeaponFireEffect(actorView->self, 1017);
    } else {
        Playerai_DispatchWeaponFireEffect(actorView->self, 1227);
    }
    Playerai_StartPrimaryAttachedSound(cueOwner, 1930);
    Playerai_StartSecondaryAttachedSound(cueOwner, 1920);

    weaponOwner = actorView->self;
    index = weaponOwner->selectedAction;
    fireState->charge =
        ((WeaponInfo *)g_weaponInfoByType[index])->chargeRate *
        g_weaponStartupChargeRateScale;
    if ((weaponOwner->selectedAction == 8) &&
        (weaponOwner->weaponLoopSoundHandle == 0)) {
        Playerai_StartSecondaryAttachedSound(weaponOwner, 2620);
    }
}

void Weapon_ApplySideDependentYaw(void *object, Event *event) {
    f32 speed;
    s32 mode;

    speed = event->source->speed;
    mode = g_playerWeaponClassMode.classMode;
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

/* 80231F5C_12.CPP */

extern s32 Playerai_IsAlternateFireHeld(void *object);

extern void Playerai_BeginHeldAlternateFire(void *actor);

extern s32 Particle_CountOwnerListOneEffects(void *, s32);

extern char g_actorParticleEffectSystem;

extern f32 Graphu64_ApproachValue(f32, f32, s32);

void Weapon_EnterChargeStateWithCues(Shared_ActorView *actor, WeaponFireState *fireState) {
    void *player;
    void *weaponOwner;
    s16 index;

    player = actor->self;
    if (fireState->mode == 2) {
        Player_SetPlayerState(player, player, 2);
    } else {
        fireState->cueTimer = g_weaponChargeEntryCueAndRate[0];
        if ((((Shared_ActorView *)player)->remote == 0) &&
            (g_playerWeaponClassMode.classMode == 1)) {
            Playerai_DispatchWeaponFireEffect(actor->self, 1019);
        } else {
            Playerai_DispatchWeaponFireEffect(actor->self, 1229);
        }
        Actor_RequestActorState(actor, fireState, 4);
        Playerai_StartPrimaryAttachedSound(player, 2423);
        Playerai_StartSecondaryAttachedSound(player, 2420);

        weaponOwner = actor->self;
        index = ((Shared_ActorView *)weaponOwner)->selectedAction;
        fireState->charge =
            ((WeaponInfo *)g_weaponInfoByType[index])->chargeRate *
            g_weaponChargeEntryCueAndRate[1];
        if ((((Shared_ActorView *)weaponOwner)->selectedAction == 8) &&
            (((Shared_ActorView *)weaponOwner)->weaponLoopSoundHandle == 0)) {
            Playerai_StartSecondaryAttachedSound(weaponOwner, 2620);
        }
    }
}

void Weapon_EmptyChargeStateHook(void) {
}

void Weapon_SetDelayAndRequestStateEight(void *actor, struct Shared_Particle *particle) {
    particle->lifetime = g_weaponStateEightDelay;
    Actor_RequestActorState(actor, particle, 8);
}

/** Perform the no-op callback at VRAM 0x80233334. */
void Weapon_EmptyAlternateFireHook(void) {
}

void Weapon_UpdateHeldAlternateFire(void *weaponActor, void *attack) {
    void *actor;

    actor = ((LevelActor *)weaponActor)->controller;
    ((WeaponFireState *)attack)->mode = 2;
    if (Player_HasAmmoForMode(actor, ((Shared_ActorView *)actor)->selectedAction) == 0) {
        ((Shared_ActorView *)actor)->nextWeapon = Weaponai_FindNextUsableWeapon(actor);
        return;
    }

    if (((LevelActor *)weaponActor)->animationTime >= g_weaponAlternateFireAnimationThreshold) {
        if (Playerai_IsAlternateFireHeld(actor) == 0) {
            Playerai_BeginHeldAlternateFire(actor);
        }
    }

    if (!((((Shared_ActorView *)actor)->actionFlags & 0x4000) &&
          (((Shared_ActorView *)actor)->health != 0))) {
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
        if (Particle_CountOwnerListOneEffects(&g_actorParticleEffectSystem, actor) == 0) {
            ((WeaponSpecialFirePlayerView *)(actor))->nextUsableWeapon = Weaponai_FindNextUsableWeapon(actor);
        }
    } else if (Weaponai_TryRequestFiringState(weaponActor, attack) == 0 &&
               !(((ActorAnimationResourceView *)weaponActor)->flags & 0x400)) {
        Actor_RequestActorState(weaponActor, attack, value);
    }
}

void Weapon_RequestReleaseOnEnabledEvent(void *a, struct WeaponEventSource *b) {
    if (b->eventEnabled != 0) {
        Actor_RequestActorState(a, b, 2);
    }
}

void Weapon_PlayStartupCue80C(void *weaponActor) {
    void *weaponOwner;
    weaponOwner = (((struct ActorPlayerControllerView *) ((s8 *) weaponActor))->player);
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

void Weapon_EaseSpinForActionFive(struct WeaponActorStateView *actor, void *fireState) {
    f32 spinStep;
    f32 feedbackSpinStep;
    void *value;
    void *controller;

    value = actor->value;
    if (((struct WeaponModeByteView *)(fireState))->value == 5) {
        Graphu64_EaseValueToward(&((WeaponFireState *)fireState)->spin, (f32) g_weaponActionFiveSpinTarget * g_weaponActionFiveSpinTargetScale, 0.4f);
    } else {
        Graphu64_EaseValueToward(&((WeaponFireState *)fireState)->spin, 0.0f, 0.4f);
    }
    spinStep = ((struct WeaponOriginScalarView *)(fireState))->value;
    controller = ((struct PlayerHeldWeaponView *)(value))->value;
    if (!(spinStep < 0.0f
              ? g_weaponActionFiveNegativeFeedbackLimit < (-spinStep * g_weaponActionFiveNegativeFeedbackScale)
              : g_weaponActionFiveFeedbackConstants[0] < (spinStep * g_weaponActionFivePositiveFeedbackScale))) {
        feedbackSpinStep = ((struct WeaponOriginScalarView *)(fireState))->value;
        if (feedbackSpinStep < 0.0f) {
            ((struct WeaponSpinRateView *)(controller))->value = (f32) (-feedbackSpinStep * g_weaponActionFiveFeedbackConstants[1]);
            return;
        }
        ((struct WeaponSpinRateView *)(controller))->value = (f32) (feedbackSpinStep * g_weaponActionFivePositiveOutputScale);
        return;
    }
    ((struct WeaponSpinRateView *)(controller))->value = (f32) g_weaponActionFiveClampedFeedback;
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

/* 800C8100.CPP */
#if !(defined(VERSION_US_REV1))
const float g_weaponPermissionNoticeDuration_StorageWords[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_weaponPermissionNoticeDuration_StorageWords_us_rev1.c */
const float g_Weapon_CheckSinglePlayerFirePermissionConstantWords[1] = {
    1.0f,
};
#endif

/* 800C8104.CPP */
#if !(defined(VERSION_US_REV1))
const float g_weaponFiveChargeRateScale_StorageWords[1] = {
    15.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_weaponFiveChargeRateScale_StorageWords_us_rev1.c */
const float g_Weapon_InitializeChargeForWeaponFiveConstantWords[1] = {
    15.0f,
};
#endif

/* 800C8108.CPP */
#if !(defined(VERSION_US_REV1))
const float g_weaponFireInitialValue_StorageWords[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_weaponFireInitialValue_StorageWords_us_rev1.c */
const float g_Weapon_InitializeFireStateCallbacksConstantWords[1] = {
    1.0f,
};
#endif

/* 800C810C.CPP */
/* ROM-grounded data: src/g_weaponTriggerStunThreshold_StorageWords_us_rev1.c */
const float g_weaponTriggerStunThreshold_StorageWords[1] = {
    0.1f,
};

/* 800C8110.CPP */
#if !(defined(VERSION_US_REV1))
const float g_weaponEightChargeRateScale_StorageWords[1] = {
    15.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_weaponEightChargeRateScale_StorageWords_us_rev1.c */
const float k_WeaponEncodedWords[1] = {
    15.0f,
};
#endif

/* 800C8114.CPP */
const float g_Weapon_InitializeChargeForWeaponEightConstantWords[7] = {
    1.7904929f, 1.0f, 1.7904929f, 1.0f,
    1.7904929f, 1.7904929f, 1.0f,
};

/* 800C8130.CPP */
/* ROM-grounded data: src/g_weaponSideYawSpeedScale_StorageWords_us_rev1.c */
const float g_weaponSideYawSpeedScale_StorageWords[1] = {
    1.5f,
};

/* 800C8134.CPP */
#if !(defined(VERSION_US_REV1))
const float g_weaponStartupChargeRateScale_StorageWords[1] = {
    15.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_weaponStartupChargeRateScale_StorageWords_us_rev1.c */
const float g_Weapon_InitializeChargeAndStartupCuesConstantWords[1] = {
    15.0f,
};
#endif

/* 800C8138.CPP */
/* ROM-grounded data: src/g_weaponChargeEntryCueAndRate_StorageWords_us_rev1.c */
const float g_weaponChargeEntryCueAndRate_StorageWords[2] = {
    2.5f, 15.0f,
};

/* 800C8140.CPP */
/* ROM-grounded data: src/g_weaponStateEightDelay_StorageWords_us_rev1.c */
const float g_weaponStateEightDelay_StorageWords[1] = {
    3e+02f,
};

/* 800C8144.CPP */
/* ROM-grounded data: src/g_weaponAlternateFireAnimationThreshold_StorageWords_us_rev1.c */
const float g_weaponAlternateFireAnimationThreshold_StorageWords[1] = {
    4.0f,
};

/* 800C8148.CPP */
const float g_weaponActionFiveSpinTargetScale_StorageWords[8] = {
    0.017453294f, 1.7904929f, 1.0f, 1.7904929f,
    1.0f, 1.7904929f, 1.7904929f, 1.0f,
};

/* 800C8168.CPP */
/* ROM-grounded data: src/g_weaponReleaseSpinTarget_StorageWords_us_rev1.c */
const float g_weaponReleaseSpinTarget_StorageWords[1] = {
    6e+02f,
};

#if defined(VERSION_US)
unsigned int k_WeaponEncodedWordsBlock1[1] = {
    0x000B0000,
};
#endif

#if defined(VERSION_EU)
unsigned int k_WeaponEncodedWordsBlock3[1] = {
    0x02603821,
};
#endif

#if defined(VERSION_DE)
unsigned int k_WeaponEncodedWordsBlock2[1] = {
    0x40C00000,
};
#endif
