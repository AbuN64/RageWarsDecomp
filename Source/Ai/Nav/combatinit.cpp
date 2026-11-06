#include "include_asm.h"
#include "Common/self.h"
#include "Common/vector4f.h"
#include "types.h"
#include "Ai/Nav/combatinit.h"
#include "Rsp/random_direction_and_affine_math.h"

#if defined(VERSION_DE)

void Nav_InitPursuitStrafe(CloseAttackActor *actor) {
    CloseAttackBrain *brain = actor->self->brain;
    brain->state = 0;
    Scaled_ResetBehaviorState(brain);
    brain->timer = Graphu64_NextRandom() % 4 + 12;
    brain->pattern = Graphu64_NextRandom() % 2;
}
#endif

#if defined(VERSION_DE)
void Nav_InitRangedCombat(CloseAttackActor *actor) {
    CloseAttackBrain *brain = actor->self->brain;
    brain->state = 0;
    Scaled_ResetBehaviorState(brain);
    brain->timer = Graphu64_NextRandom() % 4 + 12;
    brain->pattern = Graphu64_NextRandom() % 2;
    brain->distance = Graphu64_NextRandom() % 250000 + 360000;
    brain->fireTimer = -1;
    brain->frames = 0;
    brain->visible = 0;
}
#endif

#if defined(VERSION_DE)
void Nav_InitCloseCombat(CloseAttackActor *actor) {
    CloseAttackBrain *brain = actor->self->brain;
    brain->state = 0;
    brain->timer = Graphu64_NextRandom() % 4 + 2;
    brain->pattern = Graphu64_NextRandom() % 2;
    brain->distance = Graphu64_NextRandom() % 32400 + 10000;
    Scaled_ResetBehaviorState(brain);
    brain->frames = 0;
    brain->visible = 0;
    brain->fireTimer = -1;
}
#endif

#if defined(VERSION_DE)
void Nav_InitVisiblePursuit(CloseAttackActor *actor) {
    CloseAttackActor *level1 = actor->self;
    CloseAttackBrain *inner = level1->brain;
    s32 r1, r2;

    inner->state = 0;
    Scaled_ResetBehaviorState(inner);

    r1 = Graphu64_NextRandom();
    inner->timer = r1 % 4 + 12;

    r2 = Graphu64_NextRandom();
    inner->pattern = r2 % 2;
}
#endif
