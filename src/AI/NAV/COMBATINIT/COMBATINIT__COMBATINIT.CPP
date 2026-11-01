#include "include_asm.h"
#include "COMMON/SELF.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "AI/NAV/COMBATINIT.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"

/* 802106E0_15.CPP */
#if !(defined(VERSION_DE))


#endif

#if defined(VERSION_US)
#endif


/* 802106E0_9.CPP */
#if defined(VERSION_DE)
#include "COMMON/SELF.H"

void Nav_InitPursuitStrafeDe(CloseAttackActor *actor) {
    CloseAttackBrain *brain = actor->self->brain;
    brain->state = 0;
    Scaled_ResetBehaviorState(brain);
    brain->timer = Graphu64_NextRandom() % 4 + 12;
    brain->pattern = Graphu64_NextRandom() % 2;
}
#endif

#if defined(VERSION_DE)
void Nav_InitRangedCombatDe(CloseAttackActor *actor) {
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
void Nav_InitCloseCombatDe(CloseAttackActor *actor) {
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
void Nav_InitVisiblePursuitDe(CloseAttackActor *actor) {
    CloseAttackBrain *brain = actor->self->brain;
    brain->state = 0;
    Scaled_ResetBehaviorState(brain);
    brain->timer = Graphu64_NextRandom() % 4 + 12;
    brain->pattern = Graphu64_NextRandom() % 2;
}
#endif

