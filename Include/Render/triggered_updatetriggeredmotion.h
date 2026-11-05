#ifndef RENDER_TRIGGERED_UPDATETRIGGEREDMOTION_H
#define RENDER_TRIGGERED_UPDATETRIGGEREDMOTION_H
#include "Common/rec.h"

extern void Triggered_SetPairedDefinitionBytes(struct LevelActor *actor, int unusedContext, struct Trigger *triggerRecord);
extern void Triggered_DisableTriggeredActorState(struct Trigger *trigger);
extern void Triggered_EnableTriggeredActorState(struct Trigger *trigger);

extern void Triggered_InitializeMotionState(void *object, void *state);
s32 Triggered_SelectMotionSound(void *context, struct TriggeredMotionSoundOption *option);
struct MovingPlatformActorView;
struct MovingPlatformMotionStateView;
void Triggered_UpdateTriggeredMotion(struct MovingPlatformActorView *actor, struct MovingPlatformMotionStateView *motion);
extern void Triggered_PathMotionNoOp(void);

#endif
