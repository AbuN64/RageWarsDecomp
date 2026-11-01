#include "AI/SOURCE.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "AI/NAV/TARGETFOLLOW.H"
#include "include_asm.h"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "TYPES.H"

/* 80212C90_3.CPP */
#if !(defined(VERSION_DE) || defined(VERSION_EU))
void Nav_InitTargetFollowing(struct TargetFollowingActorView *actor) {
    NavigationBrainView *brain = actor->player->brain;

    brain->state = 0;
    Scaled_ResetBehaviorState(brain);
    brain->postRouteInitReset = 0;
}
#endif

#if defined(VERSION_DE)
#include "COMMON/SELF.H"

void Nav_ResetTargetFollowStateDe(void *object) {
    CloseAttackActor *actor = object;
    CloseAttackBrain *brain = actor->self->brain;
    brain->state = 0;
    Scaled_ResetBehaviorState(brain);
    brain->reset2FC = 0;
}
#endif

#if !(defined(VERSION_EU))
extern void Nav_RunBehaviorHandler(void *);
extern void Nav_SteerAlongRoute(void *);
extern void Nav_UpdatePlayerSteering(void *controller);

void Nav_UpdateTargetRouteFollow(void *actorObject)
{
    AiTarget *actor = actorObject;
    AiController *state;
    AiTarget *peer;
    AiController *peer_state;
    s32 value;

    state = actor->player->controller;
    peer = state->target;
    if (peer == 0) {
        Nav_RunBehaviorHandler(state);
        return;
    }
    peer_state = peer->player->controller;
    value = peer_state->current;
    if (value != state->fallback) {
        state->fallback = value;
    }
    Nav_SteerAlongRoute(state);
    Nav_RunBehaviorHandler(state);
    Nav_UpdatePlayerSteering(state);
}
#endif



/* 80212C90_4.CPP */
#if defined(VERSION_EU)
#include "COMMON/SHAREDCALLBACK5.H"

void Nav_ResetTargetFollowStateEu(AiTarget *pThis) {
    AiController *controller = pThis->player->controller;
    controller->handlerIndex = 0;
    Scaled_ResetBehaviorState(controller);
    controller->behaviorResetFlag = 0;
}
#endif

#if defined(VERSION_EU)
extern void Nav_RunBehaviorHandler(AiController *);
extern void Nav_SteerAlongRoute(AiController *);
extern void Nav_UpdatePlayerSteering(AiController *);

void Nav_UpdateTargetRouteFollowEu(AiTarget *pThis) {
    AiController *controller = pThis->player->controller;
    s32 current;
    if (controller->target == 0) {
        Nav_RunBehaviorHandler(controller);
    } else {
        current = controller->target->player->controller->current;
        if (current != controller->fallback) {
            controller->fallback = current;
        }
        Nav_SteerAlongRoute(controller);
        Nav_RunBehaviorHandler(controller);
        Nav_UpdatePlayerSteering(controller);
    }
}
#endif
