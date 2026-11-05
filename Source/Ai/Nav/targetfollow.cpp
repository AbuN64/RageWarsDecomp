#include "Common/level_actor.h"
#include "Ai/source.h"
#include "Common/ai_behaviour_types.h"
#include "Ai/Nav/targetfollow.h"
#include "include_asm.h"
#include "Common/vector4f.h"
#include "Common/aiprofile.h"
#include "types.h"
#include "Behaviour/behaviour.h"
#include "Frontend/player.h"
#if defined(VERSION_DE)
#include "Common/self.h"
#endif

#if !(defined(VERSION_DE) || defined(VERSION_EU))
void Nav_InitTargetFollowing(struct LevelActor *actor) {
    AiController *brain = (AiController *)((Player *)actor->controller)->controller;

    brain->handlerIndex = 0;
    Scaled_ResetBehaviorState(brain);
    brain->behaviorResetFlag = 0;
}
#endif

#if defined(VERSION_DE)

void Nav_ResetTargetFollowStateDe(void *object) {
    CloseAttackActor *actor = object;
    CloseAttackBrain *brain = actor->self->brain;
    brain->state = 0;
    Scaled_ResetBehaviorState(brain);
    brain->reset2FC = 0;
}
#endif

#if !(defined(VERSION_EU))
struct AiController;

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


#if defined(VERSION_EU)

void Nav_ResetTargetFollowStateEu(AiTarget *pThis) {
    AiController *controller = pThis->player->controller;
    controller->handlerIndex = 0;
    Scaled_ResetBehaviorState(controller);
    controller->behaviorResetFlag = 0;
}
#endif

#if defined(VERSION_EU)

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
