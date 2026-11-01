#ifndef FX_TARGET_H
#define FX_TARGET_H
#include "TYPES.H"

struct AiController;

s32 Target_UpdateTargetSelection(void *object);
s32 Target_IsPreferredTargetAccepted(struct AiController *controller);
s32 Target_CountAcceptedTargets(struct AiController *controller);
s32 Target_FindNearestFlaggedTarget(struct AiController *controller);

#endif
