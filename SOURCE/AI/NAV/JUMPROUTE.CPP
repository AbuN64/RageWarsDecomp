#include "AI/SOURCE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/SELF.H"
#include "AI/NAV/JUMPROUTE.H"
#include "include_asm.h"

/* JUMPROUTE.CPP */
/* 80212C90_10.CPP */
void Nav_InitTimedJumpRoute(JumpRouteActorView *actor) {
    JumpRouteControllerView *inner;

    inner = actor->player->controller;
    inner->behaviorState = 0;
    Scaled_ResetBehaviorState(inner);
    inner->jumpTimer = -1;
    inner->resetFlag = 0;
}

extern void Scaled_SetBehaviourState(void *controller, s32 behaviourId);
extern void Nav_RunBehaviorHandler(void *aiController);
extern f32 Scaled_DistanceToNode(void *controller, s32 nodeId);
extern void Nav_SteerAlongRoute(void *);
extern void Nav_UpdatePlayerSteering(void *controller);

void Nav_UpdateTransientJumpRoute(JumpRouteActorView *actor)
{
    void *state;
    s32 random;
    s32 actor_state;
    u32 flags;

    state = actor->player->controller;
    if (((Shared_ControlView *)((NavigationBrainView *)state)->player->controls)->transientFlag == 0) {
        Scaled_SetBehaviourState(state, 2);
        return;
    }

    Nav_RunBehaviorHandler(state);
    if (--((NavigationBrainView *)state)->jumpTimer == 0) {
        actor_state = ((NavigationBrainView *)state)->player->action;
        flags = ((NavigationBrainView *)state)->player->unk_0x0038;
        actor_state ^= 15;
        flags = (flags & 0x3000) != 0;
        if (actor_state != 0 && !flags) {
            ((NavigationBrainView *)state)->player->unk_0x06B0 |= 0x10;
        }
    }

    if (((NavigationBrainView *)state)->jumpTimer < 0) {
        random = Graphu64_NextRandom();
        ((NavigationBrainView *)state)->jumpTimer = ((random % 5) + 3) * 15;
    }

    if (Scaled_DistanceToNode(state, ((NavigationBrainView *)state)->nextNode) < g_timedJumpRouteArrivalDistance) {
        ((NavigationBrainView *)state)->player->unk_0x06B0 |= 0x10;
    }
    Nav_SteerAlongRoute(state);
    Nav_UpdatePlayerSteering(state);
}

/* 800C6E84_21.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Nav_UpdateTransientJumpRouteConstantWords_Jumproute.c */
const float g_Nav_UpdateTransientJumpRouteConstantWords[1] = {
    102.399994f,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_JumprouteEncodedWordsBlock2[3] = {
    0x00000000, 0x41F00000, 0x00000000,
};
#endif

#if defined(VERSION_EU)
unsigned int k_JumprouteEncodedWordsBlock1[3] = {
    0x216BFFFF, 0x40021000, 0x04010002,
};
#endif

#if defined(VERSION_DE)
unsigned int k_JumprouteEncodedWords[3] = {
    0x43000000, 0x41F00000, 0x00000000,
};
#endif

/* G_OVERLAYSONECONSTANTSFLOATCONSTANTWORDSBLOCK4.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C71E4 */
#if defined(VERSION_US_REV1)
f32 g_overlaysOneConstantsFloatConstantWordsBlock4[3] = {
    0.0f, 30.0f, 0.0f
};
#endif
#endif
