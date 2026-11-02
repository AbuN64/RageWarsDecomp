#include "include_asm.h"
#include "COMMON/LONE/PARTICLE_COLLISION_PROBE_RESULT.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/INTEGERSTATE2C.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"

extern void Player_GetPlayerViewTranslation(void *, f32 *);

extern void Nav_ResetPlayerState(s32 *state);

f32 Graphu64_GetPointDistance(f32 *, f32 *);

extern void *Portal_GetGraphPoint(void *, s32);

extern CNavData g_navigationGraph;


extern void **g_collisionCurrentActor;

extern s32 CCollision_SweepPoint(void *actorStorage, CVector3 startPosition, CVector3 desired, void *motionSettings);

/* Revives a player whose down timer at 0x1340 has run past its limit (30 ticks, or 900 in
   control modes 12 and 15 while g_selectedProfileHealthOptionEnabled asks): clears the timer and calls Player_PlacePlayerForRound
   unless the session at 0x98 is running and the player's team membership at 0x94 and control
   mode disagree, or it is teamless and active outside session mode 3. */









extern void Player_PlacePlayerForRound(SharedPlayer *);

void Scaled_UpdateTargetPitch(Brain *object) {
    void *memory = object;
    PitchBrain *brain = memory;
    CVector3 origin, delta;
    f32 ownHeight, targetHeight, correction, vertical, horizontal, zero;
    PitchPlayer *target;
    if (brain->target) {
        origin = brain->player->position;
        Player_GetPlayerViewTranslation(brain->player, &delta.x);
        ownHeight = delta.y - brain->player->position.y;
        target = brain->target->player;
        if (target->transformed) {
            Player_GetPlayerViewTranslation(target, &delta.x);
            targetHeight = delta.y - target->position.y;
        } else targetHeight = target->model->height - target->position.y;
        targetHeight *= g_targetPitchHeightScale;
        if (g_gameSettings.counters.m_bFragTagOn && target->profile->scaled) targetHeight *= g_fragTagTargetHeightScale;
        delta = brain->targetPosition;
        delta.x -= origin.x;
        delta.y -= origin.y;
        delta.z -= origin.z;
        correction = targetHeight - ownHeight;
        brain->distance = Gu_Sqrtf(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
        vertical = delta.y;
        delta.y = 0.0f;
        vertical += correction;
        zero = delta.y;
        horizontal = Gu_Sqrtf(delta.x*delta.x + delta.z*delta.z);
        if (horizontal == zero) {
            if (vertical < zero) brain->angle = g_targetPitchDownAngle;
            else brain->angle = g_targetPitchUpAngle;
        } else brain->angle = XMath_EvaluateArcTangentTwo(vertical, horizontal) * g_targetPitchRadiansToDegrees;
    } else brain->angle = 0.0f;
    brain->previousAngle = brain->angle;
}

/* Stores the player, then resets its AI state using the same pointer. */
void Scaled_InitPlayerState(int *state, int player) {
    *state = player;
    Nav_ResetPlayerState(state);
}

void Scaled_ClearNodeQueue(AiController *controller)
{
    s32 i;
    s32 empty;
    empty = -1;
    i = 3;
    do {
        controller->queue[i] = empty;
        i -= 1;
    } while (i >= 0);
}

/* Pops the front of a four-entry queue at offset 0x14 of a record: shifts the entries down one,
   marks the last empty with -1 and returns whether an entry remains at the front. */

s32 Scaled_AdvanceNodeQueue(AiController *queue) {
    s32 i;

    for (i = 1; i < 4; i++) {
        queue->queue[i - 1] = queue->queue[i];
    }
    queue->queue[3] = -1;
    return queue->queue[0] != -1;
}

/** Store the second argument at byte offset 0x214 in the first argument. */
void Scaled_SetBehaviorTable(AiController *object, AiBehaviourTable *value) {
    object->table = value;
}

s32 Scaled_SetBehaviourState(AiController *controller, s32 behaviourId) {
    AiBehaviourTable *node;
    AiBehaviourEntry *entry;
    AiBehaviourEntry *found;
    void (*callback)(Player *, s32);

    node = controller->table;
    found = 0;
    controller->state = behaviourId;
    while (node != 0) {
        entry = node->entries;
        if (entry->id != -1) {
            while (entry->id != -1) {
                if (entry->id == behaviourId) {
                    found = entry;
                    node = 0;
                    break;
                }
                entry++;
            }
        }
        if (node != 0) node = node->next;
    }
    if (found == 0) return 0;
    controller->behaviour = found;
    callback = found->enter;
    if (callback != 0) callback(controller->player, 0);
    return 1;
}

void Scaled_SetPitchFromAngle(AiController *controller, float amount) {
    float result = amount * g_difficultyAimAmountScale;
    if (controller != 0) {
        controller->player->pitch = -result;
    }
}

CVector3 *Scaled_GetControllerPosition(AiController *controller) {
    return &controller->player->pos;
}

f32 Scaled_DistanceToNode(AiController *controller, s32 nodeId) {
    return Graphu64_GetPointDistance(&controller->player->pos.x, Portal_GetGraphPoint(&g_navigationGraph, nodeId));
}

/** Reset three state words and set the final state to one. */
void Scaled_ResetBehaviorState(void *object) {
    AiController *controller = object;
    controller->behaviorStateWordA = 0;
    controller->behaviorStateWordB = 0;
    controller->behaviorResetFlag = 1;
}

/** Clear five consecutive object words beginning at offset 0x300. */
void Scaled_ClearAuxiliaryBehaviorState(AiController *controller) {
    controller->routeComplete = 0;
    controller->airPitchNode = 0;
    controller->jumpLinkActive = 0;
    controller->kindFourLinkActive = 0;
    controller->holdMovement = 0;
}

s32 Scaled_HasLineOfSight(Player **fromRef, Player *target) {
    CVector3 first;
    CVector3 second;

    if (fromRef == 0 || target == 0) {
        return 0;
    }

    first = (*fromRef)->pos;
    second = target->pos;
    first.y += g_difficultyAimHeightOffset;
    second.y += g_difficultyAimHeightOffset;
    if (CCollision_SweepPoint(*fromRef, first, second, &g_particleCollisionProbeResult) != 0) {
        return *g_collisionCurrentActor == target;
    }
    return 1;
}

s32 Scaled_MatchesBehaviorStateFilter(AiController *controller) {
    s32 state;

    state = controller->state;
    if (state >= 8) {
        goto ge_8;
    }
    if (state >= 3) {
        goto ret1;
    }
    if (state == 1) {
        goto ret1;
    }
    goto ret0;
ge_8:
    if (state != 13) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

/** Report whether the state word at offset 0x21C equals eight. */
int Scaled_IsBehaviorStateEight(AiController *object) {
    return object->state == 8;
}

f32 Scaled_GetDifficultyEngagementAdjustment(AiController *controller)
{
  Player *object;
    AiCharacterDefinition *definition;
  u8 state;
  f32 difficultyMultiplier;
  f32 engagementAdjustment;
  object = controller->player;
    definition = object->definition;
  state = object->profile->difficulty;
  engagementAdjustment = definition->engagement;
  engagementAdjustment = engagementAdjustment * g_difficultyEngagementScale;
  switch (state)
  {
    case 1:
      goto done;

    default:
      controller->player->profile->difficulty = 0;

    case 0:
      difficultyMultiplier = g_difficultyEngagementFirstMultiplier;
      break;

    case 2:
      difficultyMultiplier = g_difficultyEngagementOtherMultiplier;
      break;

  }

  engagementAdjustment *= difficultyMultiplier;
  done:
  return engagementAdjustment;

}

f32 Scaled_GetScaledAggression(AiController *controller) {
    f32 value;
    u8 difficulty;
    Player *player;
    AiCharacterDefinition *definition;

    player = controller->player;
    definition = player->definition;
    difficulty = player->profile->difficulty;
    value = definition->aggression;
    value *= g_aiAggressionBaseScale;
    switch (difficulty) {
    case 1:
        break;
    default:
        controller->player->profile->difficulty = 0;
    case 0:
        value *= g_aiAggressionEasyScale;
        break;
    case 2:
        value *= g_aiAggressionHardScale;
        break;
    }
    return value;
}

f32 Scaled_ScaleCharacterSettingByDifficulty(AiController *controller) {
    f32 difficultyScale;
    f32 value;
    u8 difficulty;
    Player *player;
    AiCharacterDefinition *definition;

    player = controller->player;
    definition = player->definition;
    difficulty = player->profile->difficulty;
    value = definition->characterSetting;
    value *= g_aiCharacterSettingBaseScale;
    switch (difficulty) {
    case 1:
        goto done;
    default:
        controller->player->profile->difficulty = 0;
    case 0:
        difficultyScale = g_aiCharacterSettingEasyScale;
        goto multiply;
    case 2:
        difficultyScale = g_aiCharacterSettingHardScale;
    }
multiply:
    value *= difficultyScale;
done:
    return value;
}

f32 Scaled_GetScaledAttackRange(AiController *controller) {
    f32 difficultyScale;
    f32 value;
    u8 difficulty;
    Player *player;
    AiCharacterDefinition *definition;

    player = controller->player;
    definition = player->definition;
    difficulty = player->profile->difficulty;
    value = definition->attackRange;
    value *= g_aiAttackRangeBaseScale;
    switch (difficulty) {
    case 1:
        break;
    default:
        controller->player->profile->difficulty = 0;
    case 0:
        difficultyScale = g_aiAttackRangeEasyScale;
        goto multiply;
    case 2:
        difficultyScale = g_aiAttackRangeHardScale;
multiply:
        value *= difficultyScale;
        break;
    }
    return value;
}

void Scaled_HandlePlayerTimeout(SharedPlayer **brain) {
    s32 limit;
    Controls *controls;
    CGameStatus *session;
    s8 mode;

    if (g_gameSettings.counters.enabled != 0) {
        mode = (*brain)->views5D8.view5D8_2.controls->mode;
        if (mode == 12 || mode == 15) {
            limit = 900;
        } else {
            limit = 30;
        }
    } else {
        limit = 30;
    }
    if (limit < (*brain)->views1340.view1340_2.timer) {
        session = &g_gameSettings.counters;
        do {
            (*brain)->views1340.view1340_2.timer = 0;
        } while (0);
        if (session->enabled != 0) {
            controls = (*brain)->views5D8.view5D8_2.controls;
            if (controls->team == 0) {
                if (controls->active == 0 || session->m_nTalsetLives == 3) {
                    Player_PlacePlayerForRound(*brain);
                }
            } else {
                mode = controls->mode;
                if (mode == 12 || mode == 15) {
                    Player_PlacePlayerForRound(*brain);
                }
            }
        } else {
            Player_PlacePlayerForRound(*brain);
        }
    }
}

f32 Scaled_UpdateDifficultyAimJitter(void *aiController) {
    AiController *brain = aiController;
    f32 aim;
    f32 aimLimit;
    u8 difficulty;

    difficulty = brain->player->profile->difficulty;
    switch (difficulty) {
    default:
        brain->player->profile->difficulty = 0;
    case 0:
        aimLimit = (1.2217305898666382f);
        break;
    case 1:
        aimLimit = (0.8726646900177002f);
        break;
    case 2:
        aimLimit = (0.523598849773407f);
        break;
    }
    aim = brain->aim;
    if (aim < Graphu64_RandomBetween(-aimLimit, aimLimit)) {
        aim += g_difficultyAimPositiveJitter;
    } else {
        aim -= g_difficultyAimNegativeJitter;
    }
    brain->aim = aim;
    return aim;
}

#if defined(VERSION_US)
unsigned int k_ScaledUpdatetargetpitchEncodedWords[1] = {
    0x0B000000,
};
#endif
