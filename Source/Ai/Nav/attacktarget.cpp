#include "Ai/Player/player_getammocapacity.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Ai/ai_functions.h"
#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include <platform_sdk.h>
#include "types.h"
#include "Common/shared_worldfunc.h"
#include "Common/ai_behaviour_types.h"
#include "Common/navigation_graph.h"
#include "Common/math_helpers.h"
#include "Game/player_rules.h"
#include "Ai/Player/scaled_updatetargetpitch.h"
#include "Ai/Nav/Route/route.h"
#include "Ai/Cbarrel/barrel_getsignedangletopoint.h"
#include "Ai/shared_pickupgoalnode.h"

s32 Nav_EvaluateAttackTarget(AiController *brain, s32 index);

/* Fills the brain's candidate list with every other living player that is an enemy (any player when teams are off,
   else one on a different team), with its distance and attack cost. */
s32 Nav_CollectEnemyTargets(AiController *brain) {
    s32 i;
    s32 count;
    Player *other;
    Shared_MenuData *world;
    Rules *rules;

    for (i = 0; i < 10; i++) {
        brain->candidates[i] = NULL;
        brain->candidateAccepted[i] = 0;
        brain->candidateDistances[i] = -1;
    }
    count = 0;
    i = count;
    world = &g_playerViewRenderContext;
    rules = (Rules *)&world->game.counters;
    for (; i < 8; i++) {
        other = Playerai_GetPlayerByIndex(world, i);
        if (other != NULL && other != (Player *)brain->player
            && (rules->teams == 0 || other->profile->team != ((Player *)brain->player)->profile->team)
            && (other->health >> 8) > 0) {
            brain->candidates[count] = (AiTarget *)other;
            brain->candidateDistances[count] = Graphu64_GetPointDistance(&((Player *)brain->player)->pos, &other->pos);
            brain->candidateAccepted[count] = Nav_EvaluateAttackTarget(brain, count);
            count++;
        }
    }
    brain->candidateCount = count;
    return 1;
}




/* Scores one attack candidate of a computer player. Its weighted distance (candidateDistances) is compared
   with a near, middle or far cutoff picked by the angle off the heading (cutoffs scale with the difficulty
   attack range); an accepted candidate is weighted by the bonus and human-target factors and kept when a
   route links the two. A candidate that hit this player in the last 50 frames is accepted again, its
   distance weighted by the angle band and the aggression. */
s32 Nav_EvaluateAttackTarget(AiController *brain, s32 index) {
    Player *target = brain->candidates[index]->player;
    s32 accept = 0;
    s32 nearLimit, middleLimit, farLimit;
    s32 range;
    f32 speed, angle, scale;

    if (target->reactionFlags & 0x20) return 0;
    speed = Scaled_GetScaledAttackRange(brain);
    nearLimit = speed * 1536.0f;
    middleLimit = speed * 921.6f;
    farLimit = speed * 512.0f;
    angle = RW_ABS(Barrel_GetSignedAngleToPoint(brain->player, target->pos));
    if (angle <= RW_PI_F6 / 4) {
        if (brain->candidateDistances[index] < nearLimit) accept = 1;
        range = 0;
    } else if (RW_PI_F6 / 4 < angle && angle <= RW_PI_F6 * 3 / 4) {
        if (brain->candidateDistances[index] < middleLimit) {
            brain->candidateDistances[index] = brain->candidateDistances[index] * 1.1f;
            accept = 1;
        }
        range = 1;
    } else {
        if (brain->candidateDistances[index] < farLimit) {
            brain->candidateDistances[index] = brain->candidateDistances[index] * 1.2f;
            accept = 1;
        }
        range = 2;
    }
    if (g_gameSettings.counters.enabled && brain->player->profile->enabled && brain->player->profile->character == 12) accept = 1;
    if (accept) {
        if (g_gameSettings.counters.m_bFragTagOn && target->profile->bonus)
            brain->candidateDistances[index] = brain->candidateDistances[index] * 0.8f;
        if (target->computer == 0)
            brain->candidateDistances[index] = brain->candidateDistances[index] * 0.8f;
        if (Route_GetRouteRelation(&g_navigationGraph, brain->current, target->controller->current)) return 1;
    }
    if (brain->lastAttacker != target || brain->attackedTimer < 451) return 0;
    if (brain->candidateDistances[index] < nearLimit * 2) {
        accept = 1;
        switch (range) {
        case 0:
            break;
        case 1:
            scale = 1.1f;
            brain->candidateDistances[index] = brain->candidateDistances[index] * scale;
            break;
        case 2:
            scale = 1.2f;
            brain->candidateDistances[index] = brain->candidateDistances[index] * scale;
            break;
        }
        brain->candidateDistances[index] = brain->candidateDistances[index] * ((1.0f - Scaled_GetScaledAggression(brain)) * 0.5f + 0.5f);
        return 1;
    }
    return 0;
}
