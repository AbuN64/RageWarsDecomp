#ifndef AI_DEVICES_ACTIONHIT_ACTIONHIT_H
#define AI_DEVICES_ACTIONHIT_ACTIONHIT_H
#include "types.h"
#include "Common/small_records.h"

struct BreakableDamageScaleView;
struct BreakableDamageScaleView {
    unsigned char padding_0[29];
    s8 damageScale;
};
typedef struct BreakableDamageScaleView BreakableDamageScaleView;

struct ActorMotionState;
struct BreakableHitContext;
struct BreakableHitStateView;
extern void Action_UpdateBreakableHit(struct BreakableHitContext *ctx, struct ActorMotionState *hit);
extern void Action_ResolveBreakableHit(void *breakableHitContext, struct BreakableHitStateView *hitState);
extern void Action_ToggleActorState(void *actor, void *requestContext);
extern void Action_DeactivateBreakable(struct BreakableHitContext *breakableHitContext);
extern void Action_RequestInactiveState(void *a, void *b);
extern void Action_RequestActiveState(void *a, void *b);
#endif
