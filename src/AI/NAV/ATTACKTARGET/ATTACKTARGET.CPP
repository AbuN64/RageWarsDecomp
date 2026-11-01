#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"

#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "COMMON/MATH_HELPERS.H"

typedef struct Team {
    char pad0[0x92];
    u8 id;
} Team;

typedef struct Racer {
    char pad0[0x8];
    f32 pos[3];
    char pad14[0x5D8 - 0x14];
    Team *team;
    char pad5DC[0x5E4 - 0x5DC];
    s32 stateBits;
} Racer;

#include "GAME/PLAYER_RULES.H"

typedef struct MatchWorld {
    char pad0[0x1860];
    Rules rules;
} MatchWorld;

typedef struct Chaser {
    Racer *self;
    char pad4[0x34];
    s32 count;
    Racer *target[12];
    s32 cost[10];
    s32 dist[10];
} Chaser;

Racer *Playerai_GetPlayerByIndex(MatchWorld *world, u32 playerIndex);
f32 Graphu64_GetPointDistance(void *firstPoint, void *secondPoint);
s32 Nav_EvaluateAttackTarget(AiController *brain, s32 index);

s32 Nav_CollectEnemyTargets(Chaser *self) {
    s32 i;
    s32 count;
    Racer *other;
    MatchWorld *world;
    Rules *rules;

    for (i = 0; i < 10; i++) {
        self->target[i] = NULL;
        self->cost[i] = 0;
        self->dist[i] = -1;
    }
    count = 0;
    i = count;
    world = (MatchWorld *)&g_playerViewRenderContext;
    rules = &world->rules;
    for (; i < 8; i++) {
        other = Playerai_GetPlayerByIndex(world, i);
        if (other != NULL && other != self->self
            && (rules->teams == 0 || other->team->id != self->self->team->id)
            && (other->stateBits >> 8) > 0) {
            self->target[count] = other;
            self->dist[count] = Graphu64_GetPointDistance(&self->self->pos, &other->pos);
            self->cost[count] = Nav_EvaluateAttackTarget((AiController *)self, count);
            count++;
        }
    }
    self->count = count;
    return 1;
}


extern CNavData g_navigationGraph;
extern f32 Scaled_GetScaledAttackRange(AiController *controller);
extern f32 Scaled_GetScaledAggression(AiController *controller);
extern f32 Barrel_GetSignedAngleToPoint(void *actor, struct CVector3_t point);
extern s32 Route_GetRouteRelation(void *table, s32 from, s32 to);

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

