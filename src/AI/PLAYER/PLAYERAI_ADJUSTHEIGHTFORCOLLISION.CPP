#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "include_asm.h"
#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/GAMEPLAY_MOVEMENT.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/PLAYER_ACTION_AND_POSE_VIEWS.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/RESOURCELOADSTATE.H"

/* Eases a player's crouch depth at 0x718: the target is g_playerCrouchDepthAndMinimumFall[0] while input bits 0xC0000 are
   held or crouching is forced at 0x71C (which also enters state 4 unless already in it) and zero
   otherwise; the depth moves a quarter of the way through Graphu64_EaseValueToward, steps smaller than
   g_playerCrouchDepthAndMinimumFall[1] downward or g_playerCrouchMinimumRiseAndBaseClearance[0] upward are dropped, and bit 0x80 of the flags is set while
   g_playerCrouchMinimumRiseAndBaseClearance[1] less the depth lies within g_playerCrouchClearanceBounds to (&g_playerCrouchClearanceBounds)[1], cleared otherwise. */






extern f32 InstHdr_GetActorReach(void *object);



struct CCollisionInfo2_t;
extern s32 Unicol_SweepActorMotion(void *actor, CVector3 startPosition, CVector3 endPosition, struct CCollisionInfo2_t *collisionInfo,
                         f32 reach, f32 radius, f32 height, f32 baseOffset);

extern char g_collisionCurrentActor[];

/* Updates a player's charge effect: cancels the charge and moves its effect to state 3 when the
   current weapon's entry in g_weaponInfoByType has no ammunition, the charge is off, or g_resultExitPending is set with
   the player's controller flag at 0x8F; while the button at 0x5E4 is held and charging it targets
   g_playerWeaponChargeBlendTarget, then runs the effect through Playerai_EmptyWeaponEffectHook, eases the level toward the target by half
   through Graphu64_EaseValueToward and clears a level below g_playerWeaponChargeBlendCutoff once the target is zero. */



extern void Playerai_EmptyWeaponEffectHook(void *, void *);


/* Returns whether the entry Scene_GetModelRecordByIndexPointer finds in g_world_AchieveUpdateresultsscreen for an object's key at 0x14 exists
   and has bit 6 of its flags at 0x52 set. */





extern struct EntryPlayerHasLinkedWorldFlagSix *Scene_GetModelRecordByIndexPointer(Shared_World *, s32);

/* Returns the constant after g_playerForceMarkerBasisScale less the cube of its difference from the argument. */






f32 Playerai_EvaluateCubicComplement(f32 curveInput) {
    f32 inputComplement = g_playerCubicComplementUnit - curveInput;
    return g_playerCubicComplementUnit - (inputComplement * inputComplement * inputComplement);
}

void Playerai_InitializeStateBlendTarget(Player *player) {
    float initialBlendValue = player->state708;
    float k = g_playerStateBlendTarget;
    player->state714 = 0;
    player->state70C = initialBlendValue;
    player->state710 = k;
}

void Playerai_InitializeStateBlendToZero(Player *player) {
    float initialBlendValue = player->state708;
    player->state710 = 0;
    player->state714 = 0;
    player->state70C = initialBlendValue;
}

/** Perform the no-op hook at VRAM 0x8022DC04. */
void Playerai_EmptyHandlerAfterInitializeStateBlendToZero_de(void) {
}

/* Reports whether the object's float at 0x718 is above the constant after g_playerStateBlendTarget. */








s32 Playerai_IsSpeedAboveThreshold(Shared_ActorView *actor) {
    f32 field = actor->speed;
    f32 konst = g_playerSpeedThreshold;
    s32 result = 1;
    if (!(konst < field)) {
        result = 0;
    }
    return result;
}

void Playerai_UpdateCrouchClearance(Player *player, LevelActor *actor, s32 unused, s32 *flags) {
    s32 held;
    s32 crouch;
    f32 target;
    f32 depth;
    f32 step;
    f32 clearance;
    f32 moved;
    f32 lo;

    held = actor->motionState & 0xC0000;
    crouch = held != 0;
    if (player->forceCrouch != 0) {
        crouch = 1;
        if (player->pose != 4) {
            Player_SetPlayerState(player, actor, 4);
        }
    }
    target = 0.0f;
    if (crouch) {
        target = g_playerCrouchDepthAndMinimumFall[0];
    }
    depth = player->crouchDepth;
    Graphu64_EaseValueToward(&depth, target, 0.25f);
    do {
        step = depth - player->crouchDepth;
        if (step < 0.0f) {
            if (-step < g_playerCrouchDepthAndMinimumFall[1]) {
                goto still;
            }
        } else if (step < g_playerCrouchMinimumRiseAndBaseClearance[0]) {
        still:
            step = 0.0f;
        }
        moved = player->crouchDepth + step;
        clearance = g_playerCrouchMinimumRiseAndBaseClearance[1] - moved;
        lo = g_playerCrouchClearanceBounds;
    } while (0);
    player->crouchDepth = moved;
    if (lo <= clearance && clearance <= (&g_playerCrouchClearanceBounds)[1]) {
        *flags |= 0x80;
    } else {
        *flags &= ~0x80;
    }
}

void Playerai_UpdateActionTransitionBlend(Shared_ActorView *actor) {
    f32 easedBlend;
    f32 targetBlend;
    f32 blendStep;

    targetBlend = 0.0f;
    if ((u32)((u16)actor->action - 9) < 4U) {
        targetBlend = g_playerActionBlendTargetAndMinimumStep[0];
    }
    easedBlend = actor->transitionBlend;
    Graphu64_EaseValueToward(&easedBlend, targetBlend, 0.25f);
    blendStep = easedBlend - actor->transitionBlend;
    if (blendStep < 0.0f) {
        if (-blendStep < g_playerActionBlendTargetAndMinimumStep[1]) {
            goto clamp;
        }
    } else if (blendStep < g_playerActionBlendMinimumRise) {
clamp:
        blendStep = 0.0f;
    }
    actor->transitionBlend = actor->transitionBlend + blendStep;
}

void Playerai_AdjustHeightForCollision(Player *player, LevelActor *actor) {
    CVector3 next;
    f32 actorBaseOffset;
    f32 collisionHeight;
    f32 actorHeight;
    f32 actorRadius;
    f32 actorReach;
    f32 heightAdjustment;

    heightAdjustment = (((((ModelBlend *)(player->definition))->height -
                    player->cameraOffset) -
                   player->crouchDepth) -
                  player->eyeOffset) -
                 player->heightDelta;
    if (heightAdjustment > 0.0f) {
        actorReach = InstHdr_GetActorReach(actor);
        actorRadius = Gobjinst_GetActorRadius(actor);
        actorHeight = Gobjinst_GetActorHeight(actor);
        actorBaseOffset = InstHdr_GetActorBaseOffset(actor);
        next.x = actor->position0.x;
        next.y = actor->position0.y + heightAdjustment;
        next.z = actor->position0.z;
        if (Unicol_SweepActorMotion(actor, actor->position0, next,
                           &g_playerCollisionProbe, actorReach, actorRadius, actorHeight,
                           actorBaseOffset) != 0) {
            collisionHeight = ((Shared_Floor *)(*(void **)g_collisionCurrentActor))->y -
                      actor->position0.y;
            player->previousPosition.y -= heightAdjustment - collisionHeight;
            heightAdjustment = collisionHeight;
        }
    }
    player->heightDelta += heightAdjustment;
}

void Playerai_UpdateWeaponEffectBlend(void *player) {
    f32 target;
    char *effect;
    s32 state;

    target = 0.0f;
    effect = &((PlayerWeaponChargeEffectView *)(player))->effect;
    if (((struct WeaponChargeAmmunitionView *)(g_weaponInfoByType[((PlayerWeaponChargeEffectView *)(player))->weaponType]))->ammunition <= 0
        || ((PlayerWeaponChargeEffectView *)(player))->chargeEnabled == 0
        || (g_gameSettings.counters.m_bFragTagOn != 0 && ((struct FragTagProfileFlagView *) ((PlayerWeaponChargeEffectView *) player)->profile)->fragTagEnabled != 0)) {
        do {
            ((PlayerWeaponChargeEffectView *)(player))->chargeEnabled = 0;
            state = ((Shared_Effect *)(effect))->state;
        } while (0);
        if (state != 0 && state != 3) {
            ((Shared_Effect *)(effect))->state = 3;
        }
    }
    if (((PlayerWeaponChargeEffectView *)(player))->chargeRequested != 0 && ((PlayerWeaponChargeEffectView *)(player))->chargeEnabled != 0) {
        target = g_playerWeaponChargeBlendTarget;
        ((PlayerWeaponChargeEffectView *)(player))->chargeEnabled = 1;
    }
    ((PlayerWeaponChargeEffectView *)(player))->chargeBlendTarget = target;
    Playerai_EmptyWeaponEffectHook(&((PlayerWeaponChargeEffectView *)(player))->effect, player);
    Graphu64_EaseValueToward(&((PlayerWeaponChargeEffectView *)(player))->chargeBlend, target, 0.5f);
    if (target == 0.0f && ((PlayerWeaponChargeEffectView *)(player))->chargeBlend < g_playerWeaponChargeBlendCutoff) {
        ((PlayerWeaponChargeEffectView *)(player))->chargeBlend = 0.0f;
    }
}

void Playerai_ApplyRangedPitchToMatrix(void *matrix, void *poseEvent) {
    PlayerRangedPitchLimits *range;
    PlayerRangedPitchStateView *actor;
    s32 value;
    f32 amount;

    PlayerRangedPitchEventView *event = poseEvent;
    ActorPlayerControllerView *object;

    range = event->pitchLimits;
    value = event->eventIndex;
    if (value < range->firstEventIndex) {
        return;
    }
    if (range->lastEventIndex < value) {
        return;
    }

    object = event->actor;
    actor = object->player;
    amount = -actor->rangedPitch;
    if (actor->action == 15) {
        amount += g_playerStateFifteenPitchOffset;
    }
    PitchMatrix(matrix, amount / (f32)range->pitchDivisor);
}

s32 Playerai_HasLinkedWorldFlagSix(struct LinkedWorldFlagsView *object) {
    struct EntryPlayerHasLinkedWorldFlagSix *entry;

    if (object->flags != 0) {
        entry = Scene_GetModelRecordByIndexPointer(&g_world, object->flags);
        if (entry != 0 && (entry->flags & 0x40)) {
            return 1;
        }
    }
    return 0;
}

#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SESSIONHANDLERROW.H"

void Playerai_UpdateTeamScore(TargetSelectionObj *a, TargetSelectionObj *b, s32 mode) {
    CGameStatus *c = &g_gameSettings.counters;
    s32 teamA;
    s32 teamB;
    s32 *win;
    s32 *loss;
    s32 off;
    s32 *wins;
    s32 *losses;

    if (c->teams != 0) {
        teamA = a->slot->team;
        teamB = b->slot->team;
        if (teamA >= 0) {
          if (teamA < 5) {
            off = teamA * 4;
            wins = c->scores;
            win = &wins[teamA];
            losses = c->counts;
            loss = &losses[teamA];
            switch (mode) {
            case 0:
                if (c->m_bCTFOn == 0 && c->m_bFragTagOn == 0) {
                    *win -= 1;
                }
                break;
            case 1:
                if (teamB != teamA) {
                    *win += 1;
                }
                break;
            case 3:
                *loss += 1;
                break;
            case 2:
                if (teamB != teamA) {
                    *win += 1;
                    break;
                }
                *win -= 1;
                break;
            }
          }
        }
    }
}
