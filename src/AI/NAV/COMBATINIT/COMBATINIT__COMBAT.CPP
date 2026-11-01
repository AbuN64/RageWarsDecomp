#include "include_asm.h"
#include "COMMON/SELF.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "AI/NAV/COMBATINIT.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"

/* 802106E0_15.CPP */
#if !(defined(VERSION_DE))
void Nav_InitRangedCombat(CloseAttackActor *actor) {
    CloseAttackActor *level1 = actor->self;
    CloseAttackBrain *inner = level1->brain;
    s32 r1, r2, r3;

    inner->state = 0;
    Scaled_ResetBehaviorState(inner);

    r1 = Graphu64_NextRandom();
    inner->timer = r1 % 4 + 12;

    r2 = Graphu64_NextRandom();
    inner->pattern = r2 % 2;

    r3 = Graphu64_NextRandom();
    inner->fireTimer = -1;
    inner->frames = 0;
    inner->visible = 0;
    inner->distance = r3 % 250000 + 360000;
}

void Nav_InitCloseCombat(CloseAttackActor *actor) {
    CloseAttackActor *level1 = actor->self;
    CloseAttackBrain *inner = level1->brain;
    s32 r1, r2, r3;

    inner->state = 0;

    r1 = Graphu64_NextRandom();
    inner->timer = r1 % 4 + 2;

    r2 = Graphu64_NextRandom();
    inner->pattern = r2 % 2;

    r3 = Graphu64_NextRandom();
    inner->distance = r3 % 32400 + 10000;

    Scaled_ResetBehaviorState(inner);

    inner->frames = 0;
    inner->visible = 0;
    inner->fireTimer = -1;
}

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

#if defined(VERSION_US)
unsigned int g_CombatInitTrailingPad[1] = {
    0x00000000,
};
#endif


/* 802106E0_9.CPP */
#if defined(VERSION_DE)
#include "COMMON/SELF.H"

#endif

#if defined(VERSION_DE)
#endif

#if defined(VERSION_DE)
#endif

#if defined(VERSION_DE)
#endif

